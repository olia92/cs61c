#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "network.h"
#include "volume.h"

// Place where test data is stored on instructional machines.
const char *DATA_FOLDER = "../cifar-10-batches-bin";
const int DEFAULT_BENCHMARK_SIZE = 1200;
const int PARTEST_SIZE = 1000;

// Function to dump the content of a volume for comparison.
void dump_volume(volume_t* v) {
    printf("%d,%d,%d", v->width, v->height, v->depth);
    for (int x = 0; x < v->width; x++) {
        for (int y = 0; y < v->height; y++) {
            for (int z = 0; z < v->depth; z++) {
                printf(",%.20lf", volume_get(v, x, y, z));
            }
        }
    }
    printf("\n");
}

// Load the snapshot of the CNN we are going to run.
network_t *load_cnn_snapshot() {
    network_t *net = make_network();
    conv_load(net->l0, "./snapshot/layer1_conv.txt");
    conv_load(net->l3, "./snapshot/layer4_conv.txt");
    conv_load(net->l6, "./snapshot/layer7_conv.txt");
    fc_load(net->l9, "./snapshot/layer10_fc.txt");
    return net;
}

// Load an image from the cifar10 data set.
void load_sample(volume_t *v, int sample_num) {
    printf("Loading input sample %d...\n", sample_num);

    int batch = sample_num / 10000;
    int ix = sample_num % 10000;

    char file_name[1024];
    sprintf(file_name, "%s/data_batch_%d.bin", DATA_FOLDER, batch+1);

    FILE *fin = fopen(file_name, "rb");
    assert(fin != NULL);

    fseek(fin, ix * 3073, SEEK_SET);

    uint8_t data[3073];
    assert(fread(data, 1, 3073, fin) == 3073);

    int outp = 1;
    for (int d = 0; d < 3; d++) {
        for (int y = 0; y < 32; y++) {
            for (int x = 0; x < 32; x++) {
                volume_set(v, x, y, d, ((double)data[outp++])/255.0-0.5);
            }
        }
    }

    fclose(fin);
}

// Load an entire batch of images from the cifar10 data set (which is divided
// into 5 batches with 10,000 images each).
batch_t load_batch(int batch) {
    printf("Loading input batch %d...\n", batch);

    char file_name[1024];
    sprintf(file_name, "%s/data_batch_%d.bin", DATA_FOLDER, batch+1);

    FILE *fin = fopen(file_name, "rb");
    assert(fin != NULL);
    batch_t batchdata = malloc(sizeof(volume_t *) * 10000);

    for (int i = 0; i < 10000; i++) {
        batchdata[i] = make_volume(32, 32, 3, 0.0);

        uint8_t data[3073];
        assert(fread(data, 1, 3073, fin) == 3073);

        int outp = 1;
        for (int d = 0; d < 3; d++) {
            for (int y = 0; y < 32; y++) {
                for (int x = 0; x < 32; x++) {
                    volume_set(batchdata[i], x, y, d, ((double)data[outp++])/255.0-0.5);
                }
            }
        }
    }

    fclose(fin);

    return batchdata;
}

// Computes the accuracy of our neural network by comparing our predicted values
// with the actual labels.
double get_accuracy(int *samples, int *predictions, int n) {
    int num_correct = 0;

    char file_name[1024];

    // Open all data batch files.
    FILE *batch_files[5];
    for (int i = 0; i < 5; i++) {
        sprintf(file_name, "%s/data_batch_%d.bin", DATA_FOLDER, i + 1);
        batch_files[i] = fopen(file_name, "rb");
    }

    for (int i = 0; i < n; i++) {
        int batch = samples[i] / 10000;
        int index = samples[i] % 10000;
        fseek(batch_files[batch], index * 3073, SEEK_SET);
        char label;
        fread(&label, 1, 1, batch_files[batch]);
        if (label == predictions[i]) {
            num_correct += 1;
        }
    }

    // Close all data batch files.
    for (int i = 0; i < 5; i++) {
        fclose(batch_files[i]);
    }

    return ((double) num_correct) / n;
}

// Perform the classification (this calls into the functions from network.c)
void run_classification(int *samples, int n, double ***keep_likelihoods) {
    printf("Making network...\n");
    network_t *net = load_cnn_snapshot();
    //TEST: 1-->
    /*
    printf("TEST:1\n");
//Layers[0] Copy to Device, change on Device WORKS!
    fdump_volume(net->layers[0],"./output/layers0_1.txt");
    change_volume_acc(net->layers[0],3.0);
    size_t we=net->layers[0]->height*net->layers[0]->width*net->layers[0]->depth;
    #pragma acc update self(net->layers[0]->weights[0:we])
    fdump_volume(net->layers[0],"./output/layers0_2.txt");
//Layers[9] Copy to Device, change on Device WORKS!
    fdump_volume(net->layers[9],"./output/layers9_1.txt");
    change_volume_acc(net->layers[9],3.0);
    we=net->layers[9]->height*net->layers[9]->width*net->layers[9]->depth;
    #pragma acc update self(net->layers[9]->weights[0:we])
    fdump_volume(net->layers[9],"./output/layers9_2.txt");
//Conv Layers
printf("Conv(l0_h) (%d,%d,%d)->(%d,%d,%d)\n",--net->l0->input_width,--net->l0->input_height,--net->l0->input_depth,--net->l0->output_width,--net->l0->output_height,--net->l0->output_depth);
#pragma acc update self(net->l0->input_width,net->l0->input_height,net->l0->input_depth,net->l0->output_width,net->l0->output_height,net->l0->output_depth)
printf("Conv(l0_d) (%d,%d,%d)->(%d,%d,%d)\n",
    net->l0->input_width,net->l0->input_height,net->l0->input_depth,net->l0->output_width,
    net->l0->output_height,net->l0->output_depth);
    conv_fprint(net->l0,"./output/l0_1.txt");
    change_volume_acc(net->l0->biases,0.28);
    for (size_t i = 0; i < net->l0->output_depth; i++){
        change_volume_acc(net->l0->filters[i],(i+1.0)*0.01);
    }
    we=net->l0->filter_width*net->l0->filter_height*net->l0->input_depth;
    for (size_t i = 0; i < net->l0->output_depth; i++){
#pragma acc update self(net->l0->filters[i]->weights[0:we])
    }
    we=1*1*net->l0->output_depth;
#pragma acc update self(net->l0->biases->weights[0:we])
    conv_fprint(net->l0,"./output/l0_2.txt");


    printf("Conv(l3_h) (%d,%d,%d)->(%d,%d,%d)\n",--net->l3->input_width,--net->l3->input_height,--net->l3->input_depth,--net->l3->output_width,--net->l3->output_height,--net->l3->output_depth);
#pragma acc update self(net->l3->input_width,net->l3->input_height,net->l3->input_depth,net->l3->output_width,net->l3->output_height,net->l3->output_depth)
printf("Conv(l3_d) (%d,%d,%d)->(%d,%d,%d)\n",
    net->l3->input_width,net->l3->input_height,net->l3->input_depth,net->l3->output_width,
    net->l3->output_height,net->l3->output_depth);
    conv_fprint(net->l3,"./output/l3_1.txt");
    change_volume_acc(net->l3->biases,0.28);
    for (size_t i = 0; i < net->l3->output_depth; i++){
        change_volume_acc(net->l3->filters[i],(i+1.0)*0.01);
    }
    we=net->l3->filter_width*net->l3->filter_height*net->l3->input_depth;
    for (size_t i = 0; i < net->l3->output_depth; i++){
#pragma acc update self(net->l3->filters[i]->weights[0:we])
    }
    we=1*1*net->l3->output_depth;
#pragma acc update self(net->l3->biases->weights[0:we])
    conv_fprint(net->l3,"./output/l3_2.txt");

printf("Conv(l6_h) (%d,%d,%d)->(%d,%d,%d)\n",--net->l6->input_width,--net->l6->input_height,--net->l6->input_depth,--net->l6->output_width,--net->l6->output_height,--net->l6->output_depth);
#pragma acc update self(net->l6->input_width,net->l6->input_height,net->l6->input_depth,net->l6->output_width,net->l6->output_height,net->l6->output_depth)
printf("Conv(l6_d) (%d,%d,%d)->(%d,%d,%d)\n",
    net->l6->input_width,net->l6->input_height,net->l6->input_depth,net->l6->output_width,
    net->l6->output_height,net->l6->output_depth);
    conv_fprint(net->l6,"./output/l6_1.txt");
    change_volume_acc(net->l6->biases,0.28);
    for (size_t i = 0; i < net->l6->output_depth; i++){
        change_volume_acc(net->l6->filters[i],(i+1.0)*0.01);
    }
    we=net->l6->filter_width*net->l6->filter_height*net->l6->input_depth;
    for (size_t i = 0; i < net->l6->output_depth; i++){
#pragma acc update self(net->l6->filters[i]->weights[0:we])
    }
    we=1*1*net->l6->output_depth;
#pragma acc update self(net->l6->biases->weights[0:we])
    conv_fprint(net->l6,"./output/l6_2.txt");

//RELU
change_relu_layer(net->l1);
printf("Relu(l1_h) (%d,%d,%d)->(%d,%d,%d)\n",net->l1->input_width,net->l1->input_height,net->l1->input_depth,net->l1->output_width,net->l1->output_height,net->l1->output_depth);
#pragma acc update self(net->l1->input_width,net->l1->input_height,net->l1->input_depth,net->l1->output_width,net->l1->output_height,net->l1->output_depth)
printf("Relu(l1_d) (%d,%d,%d)->(%d,%d,%d)\n",
    net->l1->input_width,net->l1->input_height,net->l1->input_depth,net->l1->output_width,net->l1->output_height,net->l1->output_depth);
change_relu_layer(net->l4);
printf("Relu(l4_h) (%d,%d,%d)->(%d,%d,%d)\n",net->l4->input_width,net->l4->input_height,net->l4->input_depth,net->l4->output_width,net->l4->output_height,net->l4->output_depth);
#pragma acc update self(net->l4->input_width,net->l4->input_height,net->l4->input_depth,net->l4->output_width,net->l4->output_height,net->l4->output_depth)
printf("Relu(l4_d) (%d,%d,%d)->(%d,%d,%d)\n",
    net->l4->input_width,net->l4->input_height,net->l4->input_depth,net->l4->output_width,net->l4->output_height,net->l4->output_depth);
change_relu_layer(net->l7);
printf("Relu(l7_h) (%d,%d,%d)->(%d,%d,%d)\n",net->l7->input_width,net->l7->input_height,net->l7->input_depth,net->l7->output_width,net->l7->output_height,net->l7->output_depth);
#pragma acc update self(net->l7->input_width,net->l7->input_height,net->l7->input_depth,net->l7->output_width,net->l7->output_height,net->l7->output_depth)
printf("Relu(l7_d) (%d,%d,%d)->(%d,%d,%d)\n",
    net->l7->input_width,net->l7->input_height,net->l7->input_depth,net->l7->output_width,net->l7->output_height,net->l7->output_depth);

//Pool
printf("Pool(l2_h) (%d,%d,%d)->(%d,%d,%d)\n",net->l2->input_depth,net->l2->input_width,net->l2->input_height,net->l2->output_depth,net->l2->output_width,net->l2->output_height);
printf("           (%d,%d), s:%d p:%d\n",net->l2->pool_width,net->l2->pool_height,net->l2->stride,net->l2->pad);
change_pool_layer(net->l2);
#pragma acc update self(net->l2->input_depth,net->l2->input_width,net->l2->input_height,net->l2->output_depth,net->l2->output_width,net->l2->output_height)
#pragma acc update self(net->l2->pool_width,net->l2->pool_height,net->l2->stride,net->l2->pad)
printf("Pool(l2_d) (%d,%d,%d)->(%d,%d,%d)\n",net->l2->input_depth,net->l2->input_width,net->l2->input_height,net->l2->output_depth,net->l2->output_width,net->l2->output_height);
printf("           (%d,%d), s:%d p:%d\n",net->l2->pool_width,net->l2->pool_height,net->l2->stride,net->l2->pad);
    
printf("Pool(l5_h) (%d,%d,%d)->(%d,%d,%d)\n",net->l5->input_depth,net->l5->input_width,net->l5->input_height,net->l5->output_depth,net->l5->output_width,net->l5->output_height);
printf("           (%d,%d), s:%d p:%d\n",net->l5->pool_width,net->l5->pool_height,net->l5->stride,net->l5->pad);
change_pool_layer(net->l5);
#pragma acc update self(net->l5->input_depth,net->l5->input_width,net->l5->input_height,net->l5->output_depth,net->l5->output_width,net->l5->output_height)
#pragma acc update self(net->l5->pool_width,net->l5->pool_height,net->l5->stride,net->l5->pad)
printf("Pool(l5_d) (%d,%d,%d)->(%d,%d,%d)\n",net->l5->input_depth,net->l5->input_width,net->l5->input_height,net->l5->output_depth,net->l5->output_width,net->l5->output_height);
printf("           (%d,%d), s:%d p:%d\n",net->l5->pool_width,net->l5->pool_height,net->l5->stride,net->l5->pad);

printf("Pool(l8_h) (%d,%d,%d)->(%d,%d,%d)\n",net->l8->input_depth,net->l8->input_width,net->l8->input_height,net->l8->output_depth,net->l8->output_width,net->l8->output_height);
printf("           (%d,%d), s:%d p:%d\n",net->l8->pool_width,net->l8->pool_height,net->l8->stride,net->l8->pad);
change_pool_layer(net->l8);
#pragma acc update self(net->l8->input_depth,net->l8->input_width,net->l8->input_height,net->l8->output_depth,net->l8->output_width,net->l8->output_height)
#pragma acc update self(net->l8->pool_width,net->l8->pool_height,net->l8->stride,net->l8->pad)
printf("Pool(l8_d) (%d,%d,%d)->(%d,%d,%d)\n",net->l8->input_depth,net->l8->input_width,net->l8->input_height,net->l8->output_depth,net->l8->output_width,net->l8->output_height);
printf("           (%d,%d), s:%d p:%d\n",net->l8->pool_width,net->l8->pool_height,net->l8->stride,net->l8->pad);
//FULLY CONNECTED
printf("fc(l9_h) (%d,%d,%d)->(%d,%d,%d)\n",--net->l9->input_width,--net->l9->input_height,--net->l9->input_depth,--net->l9->output_width,--net->l9->output_height,--net->l9->output_depth);
#pragma acc update self(net->l9->input_width,net->l9->input_height,net->l9->input_depth,net->l9->output_width,net->l9->output_height,net->l9->output_depth)
printf("fc(l9_d) (%d,%d,%d)->(%d,%d,%d)\n",
    net->l9->input_width,net->l9->input_height,net->l9->input_depth,net->l9->output_width,
    net->l9->output_height,net->l9->output_depth);
    fc_fprint(net->l9,"./output/l9_1.txt");
    change_volume_acc(net->l9->biases,0.28);
    for (size_t i = 0; i < net->l9->output_depth; i++){
        change_volume_acc(net->l9->filters[i],(i+1.0)*0.01);
    }

    for (size_t i = 0; i < net->l9->output_depth; i++){
#pragma acc update self(net->l9->filters[i]->weights[0:net->l9->num_inputs])
    }
#pragma acc update self(net->l9->biases->weights[0:net->l9->output_depth])
    fc_fprint(net->l9,"./output/l9_2.txt");

//SOFTMAX
    putchar('\n');
    printf("softmax(l10_h) (%d,%d,%d)->(%d,%d,%d)\n",--net->l10->input_width,--net->l10->input_height,--net->l10->input_depth,--net->l10->output_width,--net->l10->output_height,--net->l10->output_depth);
#pragma acc update self(net->l10->input_width,net->l10->input_height,net->l10->input_depth,net->l10->output_width,net->l10->output_height,net->l10->output_depth)
    printf("softmax(l10_d) (%d,%d,%d)->(%d,%d,%d)\n",
        net->l10->input_width,net->l10->input_height,net->l10->input_depth,net->l10->output_width,
        net->l10->output_height,net->l10->output_depth);
    for (size_t i = 0; i < net->l10->output_depth; i++){
        net->l10->likelihoods[i]=(double)rand()/RAND_MAX;
    }
    printf("likelihoods_h:\n");
    for (size_t i = 0; i < net->l10->output_depth; i++){
        printf("%2.1f, ",net->l10->likelihoods[i]);
    }
    putchar('\n');
    // change_softmax_layer(net->l10);

// //present(net,net->l0,net->l10->output_depth,net->l10->likelihoods)
//-->WORKS!!!!!!!!
#pragma acc parallel loop present(net->l10)
// #pragma acc parallel loop present(net,net->l10,net->l10->likelihoods)
// #pragma acc parallel loop present(net) //!!! DOESN'T WORK
    for (size_t i = 0; i < net->l10->output_depth; i++){
        net->l10->likelihoods[i]=10.0;
    }
#pragma acc update self(net->l10->likelihoods[0:net->l10->output_depth])
printf("likelihoods_d:\n");
    for (size_t i = 0; i < net->l10->output_depth; i++){
        printf("%2.1f, ",net->l10->likelihoods[i]);
    }
    putchar('\n');
    */
   //TEST: 1^

    batch_t batches[50];
    for (int i = 0; i < 50; i++) {
        batches[i] = NULL;
    }

    printf("Loading batches...\n");
    for (int i = 0; i < n; i++) {
        int batch = samples[i] / 10000;
        if (batches[batch] == NULL) {
            batches[batch] = load_batch(batch);
        }
    }

    volume_t **input = (volume_t **) malloc(sizeof(volume_t*)*n);
#pragma acc enter data create(input[0:n][0:1])
    for (int i = 0; i < n; i++) {
        input[i] = batches[samples[i] / 10000][samples[i] % 10000];
    int we = input[i]->width*input[i]->height*input[i]->depth;
#pragma acc enter data copyin(input[i][0:1],input[i]->weights[0:we])
    }
//TEST: 2-->
// int N=3;
/*
printf("TEST:2\n");
fdump_volume(input[N],"./output/input0.txt");
#pragma acc parallel loop collapse(3) present(input)
for(int x=0;x<input[N]->width; x++){
    for(int y=0;y<input[N]->height; y++){
        for(int d=0;d<input[N]->depth; d++){
            volume_set(input[N],x,y,d,8.0);
    }}}
    int we = input[N]->width*input[N]->height*input[N]->depth;

    #pragma acc update self(input[N]->weights[0:32*32*3])
fdump_volume(input[N],"./output/input0_2.txt");
*/
//TEST:2^

    double **likelihoods = (double **) malloc(sizeof(double *) * n);
        // #pragma acc enter data create(likelihoods[0:n][0:1])

    for (int c = 0; c < n; c++) {
        likelihoods[c] = (double *) malloc(sizeof(double) * NUM_CLASSES);
            // #pragma acc enter data create(likelihoods[c][0:NUM_CLASSES])

    }
    #pragma acc enter data copyin(likelihoods[0:n][0:NUM_CLASSES])
    //TEST:3-->
    /*
    printf("TEST:3\n");
    for(int x=0;x<NUM_CLASSES; x++){
    likelihoods[N][x]=0.0;
    }
    for(int i=0;i<NUM_CLASSES;i++){
        printf("%3.2lf ",likelihoods[N][i]);
    }
    putchar('\n');
#pragma acc parallel loop present(likelihoods)
for(int x=0;x<NUM_CLASSES; x++){
    likelihoods[N][x]=30.0;
    }
#pragma acc update self(likelihoods[N][0:NUM_CLASSES])
for(int i=0;i<NUM_CLASSES;i++){
        printf("%3.2lf ",likelihoods[N][i]);
    }
    putchar('\n');
    */
    //TEST:3^

    printf("Running classification...\n");
    net_classify(net, input, likelihoods, n);

    //TEST:4-->
    /*
    printf("TEST:4\n");
for(int x=0;x<NUM_CLASSES; x++){
    likelihoods[N][x]=0.1;
    }
printf("likelihoods_h[%d]:\n",N);
    for(int i=0;i<NUM_CLASSES;i++){
        printf("%3.2lf ",likelihoods[N][i]);
    }
    putchar('\n');

#pragma acc update self(likelihoods[0:n][0:NUM_CLASSES])
printf("likelihoods_d:\n");
for(int j=0;j<n;j++){
    for(int i=0;i<NUM_CLASSES;i++){
        printf("%3.2lf ",likelihoods[j][i]);
    }putchar('\n');}
    putchar('\n');
    */
    //TEST:4^
    int predictions[n];
    for (int i = 0; i < n; i++) {
        int best_class = -1;
        double max_likelihood = -INFINITY;
        for (int c = 0; c < NUM_CLASSES; c++) {
            if (max_likelihood < likelihoods[i][c]) {
                max_likelihood = likelihoods[i][c];
                best_class = c;
            }
        }
        predictions[i] = best_class;
    }

    printf("%lf%% accuracy\n", 100 * get_accuracy(samples, predictions, n));

    free_network(net);
#pragma acc exit data delete(input)
    free(input);

    for (int i = 0; i < 50; i++) {
        if (batches[i] != NULL) {
            for (int j = 0; j < 10000; j++) {
                free_volume(batches[i][j]);
            }
    #pragma acc exit data delete(batches[i])
            free(batches[i]);
        }
    }

    if (keep_likelihoods == NULL) {
        for (int i = 0; i < n; i++) {
    #pragma acc exit data delete(likelihoods[i])
            free(likelihoods[i]);
        }
#pragma acc exit data delete(likelihoods)
        free(likelihoods);
    } else {
        *keep_likelihoods = likelihoods;
    }
}

// Run benchmark on a specified number samples (if there is none, then
// DEFAULT_BENCHMARK_SIZE). Returns the number of seconds taken to perform the
// benchmark.
void do_benchmark(int argc, char **argv) {
    int num_samples = DEFAULT_BENCHMARK_SIZE;
    if (argc > 0)
        num_samples = atoi(argv[0]);

    printf("RUNNING BENCHMARK ON %d PICTURES...\n", num_samples);

    // Pick DEFAULT_BENCHMARK_SIZE random samples, it doesn't matter which.
    int *samples = (int *) malloc(sizeof(int)*num_samples);
    for (int i = 0; i < num_samples; i++) {
        samples[i] = i;
    }

    struct timeval tv;
    gettimeofday(&tv, NULL);
    uint64_t start = 1000000L * tv.tv_sec + tv.tv_usec;

    run_classification(samples, num_samples, NULL);

    gettimeofday(&tv,NULL);
    uint64_t end = 1000000L * tv.tv_sec + tv.tv_usec;
    printf("%ld microseconds\n", end - start);

    free(samples);
}

// Run test of classifying individual samples and check the content of every layer
// against reference output produced by convnet.js.
void do_layers_test(int argc, char **argv) {
    int sample_num = 0;

    if (argc > 0)
        sample_num = atoi(argv[0]);

    assert(sample_num >= 0 && sample_num < 50000);

    printf("Making network...\n");
    network_t* net = load_cnn_snapshot();

    batch_t* batch = make_batch(net, 1);
    load_sample(batch[0][0], sample_num);

    net_forward(net, batch, 0, 0);

    for (int i = 0; i < NUM_LAYERS + 1; i++) {
        printf("LAYER%d,", i);
        dump_volume(batch[i][0]);
    }

    free_network(net);
    free_batch(batch, 1);
}

// Run a large-scale test to catch parallelism errors that do not occur when testing
// on individual examples.
void do_parallel_test(int argc, char **argv) {
    int test_size = PARTEST_SIZE;

    if (argc > 0)
        test_size = atoi(argv[0]);

    srand(1234);

    int *samples = (int *) malloc(sizeof(int)*test_size);
    for (int i = 0; i < test_size; i++) {
        samples[i] = (int) ((double)rand() / ((double)RAND_MAX + 1) * 50000);
    }

    double **kept_output;
    run_classification(samples, test_size, &kept_output);

    for (int i = 0; i < test_size; i++) {
        printf("PAR%d,", i);
        for (int c = 0; c < NUM_CLASSES - 1; c++) {
            printf("%lf,", kept_output[i][c]);
        }
        printf("%lf\n", kept_output[i][NUM_CLASSES - 1]);
    }

    free(samples);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: ./benchmark <benchmark|test|partest> [args]\n");
        return 2;
    }

    if (!strcmp(argv[1], "benchmark")) {
        do_benchmark(argc-2, argv+2);
        return 0;
    }

    if (!strcmp(argv[1], "test")) {
        do_layers_test(argc-2, argv+2);
        return 0;
    }

    if (!strcmp(argv[1], "partest")) {
        do_parallel_test(argc-2, argv+2);
        return 0;
    }

    printf("ERROR: Unknown command\n");

    return 2;
}
