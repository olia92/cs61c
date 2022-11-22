#include <stdlib.h>
#include <stdio.h>

// Include SSE intrinsics
#if defined(_MSC_VER)
#include <intrin.h>
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
#include <immintrin.h>
#include <x86intrin.h>
#endif

// Include OpenMP
#include <omp.h>
#include <openacc.h>

#include "layers.h"
#include "network.h"
#include "volume.h"

network_t *make_network() {
    network_t *net = (network_t *) malloc(sizeof(network_t));
#pragma acc enter data create (net[0:1])
    net->layers[0] = make_volume(32, 32, 3, 0.0);
    net->l0 = make_conv_layer(32, 32, 3, 5, 16, 1, 2);

    net->layers[1] = make_volume(net->l0->output_width, net->l0->output_height, net->l0->output_depth, 0.0);
    net->l1 = make_relu_layer(net->layers[1]->width, net->layers[1]->height, net->layers[1]->depth);

    net->layers[2] = make_volume(net->l1->output_width, net->l1->output_height, net->l1->output_depth, 0.0);
    net->l2 = make_pool_layer(net->layers[2]->width, net->layers[2]->height, net->layers[2]->depth, 2, 2);

    net->layers[3] = make_volume(net->l2->output_width, net->l2->output_height, net->l2->output_depth, 0.0);
    net->l3 = make_conv_layer(net->layers[3]->width, net->layers[3]->height, net->layers[3]->depth, 5, 20, 1, 2);

    net->layers[4] = make_volume(net->l3->output_width, net->l3->output_height, net->l3->output_depth, 0.0);
    net->l4 = make_relu_layer(net->layers[4]->width, net->layers[4]->height, net->layers[4]->depth);

    net->layers[5] = make_volume(net->l4->output_width, net->l4->output_height, net->l4->output_depth, 0.0);
    net->l5 = make_pool_layer(net->layers[5]->width, net->layers[5]->height, net->layers[5]->depth, 2, 2);

    net->layers[6] = make_volume(net->l5->output_width, net->l5->output_height, net->l5->output_depth, 0.0);
    net->l6 = make_conv_layer(net->layers[6]->width, net->layers[6]->height, net->layers[6]->depth, 5, 20, 1, 2);

    net->layers[7] = make_volume(net->l6->output_width, net->l6->output_height, net->l6->output_depth, 0.0);
    net->l7 = make_relu_layer(net->layers[7]->width, net->layers[7]->height, net->layers[7]->depth);

    net->layers[8] = make_volume(net->l7->output_width, net->l7->output_height, net->l7->output_depth, 0.0);
    net->l8 = make_pool_layer(net->layers[8]->width, net->layers[8]->height, net->layers[8]->depth, 2, 2);

    net->layers[9] = make_volume(net->l8->output_width, net->l8->output_height, net->l8->output_depth, 0.0);
    net->l9 = make_fc_layer(net->layers[9]->width, net->layers[9]->height, net->layers[9]->depth, 10);

    net->layers[10] = make_volume(net->l9->output_width, net->l9->output_height, net->l9->output_depth, 0.0);
    net->l10 = make_softmax_layer(net->layers[10]->width, net->layers[10]->height, net->layers[10]->depth);

    net->layers[11] = make_volume(net->l10->output_width, net->l10->output_height, net->l10->output_depth, 0.0);
    return net;
}

void free_network(network_t *net) {
    for (int i = 0; i < NUM_LAYERS + 1; i++)
        free_volume(net->layers[i]);

    // Free each conv layer's filters and biases
    for (int f = 0; f < net->l0->output_depth; f++) {
        free_volume(net->l0->filters[f]);
    }
#pragma acc exit data delete(net->l0->filters)
    free(net->l0->filters);
    free_volume(net->l0->biases);

    for (int f = 0; f < net->l3->output_depth; f++) {
        free_volume(net->l3->filters[f]);
    }
#pragma acc exit data delete(net->l3->filters)
    free(net->l3->filters);
    free_volume(net->l3->biases);

    for (int f = 0; f < net->l6->output_depth; f++) {
        free_volume(net->l6->filters[f]);
    }
#pragma acc exit data delete(net->l6->filters)
    free(net->l6->filters);
    free_volume(net->l6->biases);

    // Free FC layer filters and biases
    for (int f = 0; f < net->l9->output_depth; f++) {
        free_volume(net->l9->filters[f]);
    }
#pragma acc exit data delete(net->l9->filters)
    free(net->l9->filters);
    free_volume(net->l9->biases);

    // Free softmax layer likelihoods
#pragma acc exit data delete(net->l10->likelihoods)
    free(net->l10->likelihoods);

#pragma acc exit data delete(net->l0,net->l1,net->l2,net->l3,net->l4,net->l5,net->l6,net->l7,net->l8,net->l9,net->l10)
    free(net->l0);
    free(net->l1);
    free(net->l2);
    free(net->l3);
    free(net->l4);
    free(net->l5);
    free(net->l6);
    free(net->l7);
    free(net->l8);
    free(net->l9);
    free(net->l10);
#pragma acc exit data delete(net)
    free(net);
}

batch_t *make_batch(network_t *net, int size) {
    batch_t *out = (batch_t*) malloc(sizeof(volume_t **) * (NUM_LAYERS + 1));
#pragma acc enter data create(out[0:NUM_LAYERS + 1])
    for (int i = 0; i < NUM_LAYERS + 1; i++) {
        out[i] = (volume_t **) malloc(sizeof(volume_t *)*size);
#pragma acc enter data create(out[i][0:size])
        for (int j = 0; j < size; j++) {
            out[i][j] = make_volume(net->layers[i]->width, net->layers[i]->height, net->layers[i]->depth, 3.0);//TEST: value=3.0
        }
    }
printf("Set batch: out[][]->weights=3.0 (HOST+DEVICE)\n");
//TEST:-->
   char buffer[50];
    int we;
    sprintf(buffer,"./output/out_h_%d_%d.txt",0,0);
    fdump_volume(out[0][0],buffer);
    printf("%s =3.0\n",buffer);
// #pragma acc data  present(out)
// #pragma acc parallel loop collapse(2)

    for(int i=0; i<NUM_LAYERS+1;i++){
        for(int j=0;j<size;j++){
           int we=out[i][j]->depth*out[i][j]->width*out[i][j]->height;
    // #pragma acc loop
            for(int k=0;k<we;k++){
                out[i][j]->weights[k]=1.2;
        }}}
    printf("Set batch: out[][]-->weights=1.2 (HOST)\n");

    // out[0][0]->depth=99;
    // #pragma acc update self(out[0][0]->depth)
    //    printf("out[0][0]->depth=%d\n",out[0][0]->depth);

    // for(int i=0; i<NUM_LAYERS+1;i++){
    //     for(int j=0;j<size;j++){
    //         we=out[i][j]->depth*out[i][j]->width*out[i][j]->height;
    // #pragma acc update self(out[i][j]->weights[0:we])
    // }}
   we=out[0][0]->depth*out[0][0]->height*out[0][0]->width;
#pragma acc update self(out[0][0]->weights[0:we])
    printf("Copy out[][] Device to Host\n");
    
    sprintf(buffer,"./output/out_d_%d_%d.txt",0,0);
    fdump_volume(out[0][0],buffer);
    printf("if Copy Device to Host Succesful %s =3.0\n",buffer);

    
    //TEST:^
    return out;
}

void free_batch(batch_t *b, int size) {
    for (int i = 0; i < NUM_LAYERS + 1; i++) {
        for (int j = 0; j < size; j++) {
            free_volume(b[i][j]);
        }
        free(b[i]);
    }
    free(b);
}

void net_forward(network_t *net, batch_t *b, int start, int end) {
    conv_forward(net->l0, b[0], b[1], start, end);
    relu_forward(net->l1, b[1], b[2], start, end);
    pool_forward(net->l2, b[2], b[3], start, end);
    conv_forward(net->l3, b[3], b[4], start, end);
    relu_forward(net->l4, b[4], b[5], start, end);
    pool_forward(net->l5, b[5], b[6], start, end);
    conv_forward(net->l6, b[6], b[7], start, end);
    relu_forward(net->l7, b[7], b[8], start, end);
    pool_forward(net->l8, b[8], b[9], start, end);
    fc_forward(net->l9, b[9], b[10], start, end);
    softmax_forward(net->l10, b[10], b[11], start, end);
}

void net_classify(network_t *net, volume_t **input, double **likelihoods, int n) {
    batch_t *b = make_batch(net, 1);
 //TEST:-->
        char buffer[50];
        sprintf(buffer,"./output/b_%d_%d_1.txt",0,0);
        fdump_volume(b[0][0],buffer);

        copy_volume_host(b[0][0], input[0]);
        printf("Copy b[0][0] contains 1st image (HOST)\n");
    // for (int k = 0; k < NUM_LAYERS + 1; k++) {
    //     for (int j = 0; j < 1; j++) {
    //         sprintf(buffer,"./output/input_%d.txt",0);
    //         fdump_volume(input[0],buffer);
            int temp=b[0][0]->depth*b[0][0]->height*b[0][0]->width;
            sprintf(buffer,"./output/b_%d_%d_2.txt",0,0);
    #pragma acc data update self(b[:12][0:1],b[0][0]->weights[0:temp])
        printf("Copy batch b[0][0] from DEVICE\n");
            fdump_volume(b[0][0],buffer);
            printf("if Copy Succesful %s = 3.0 \n",buffer);
    //     }
    // }
    
    //TEST:^

    for (int i = 0; i < n; i++) {
        copy_volume(b[0][0], input[i]);
        net_forward(net, b, 0, 0);
        for (int j = 0; j < NUM_CLASSES; j++) {
            likelihoods[i][j] = b[11][0]->weights[j];
        }
    }

     //TEST:-->
     /*
    for (int k = 0; k < NUM_LAYERS + 1; k++) {
        for (int j = 0; j < 1; j++) {
            char buffer[50];
            sprintf(buffer,"./output/out_%d_%d.txt",n-1,k);
            fdump_volume(b[k][j],buffer);
        }
    }
    */
    //TEST:^
#pragma acc update device(likelihoods[0:n][0:NUM_CLASSES])
    free_batch(b, 1);
}
