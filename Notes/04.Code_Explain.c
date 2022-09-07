Volumes are used to represent the activations (i.e., state) between the different layers of the CNN. They all have three dimensions. The inter- pretation of their content depends on the layer that produced them. Before the first iteration, the Volume holds the data of the image we want to classify (the depth are the three color dimensions). After the last stage of the CNN, the Volume holds the probabilities that an image is part of a specific category.

typedef struct volume {
    int width;
    int height;
    int depth;
    double *weights;
} volume_t;

The weights are represented as a 1-d array with length width * height * depth. 

---

Defines the specific network architecture that we use for this project. Layer elements in the struct are in the same order as they are in the network itself.

typedef struct network {
    volume_t *layers[NUM_LAYERS + 1];
    conv_layer_t *l0;
    relu_layer_t *l1;
    pool_layer_t *l2;
    conv_layer_t *l3;
    relu_layer_t *l4;
    pool_layer_t *l5;
    conv_layer_t *l6;
    relu_layer_t *l7;
    pool_layer_t *l8;
    fc_layer_t *l9;
    softmax_layer_t *l10;
} network_t;

What follows are the different layers of the CNN. Each layer has the following operations:

make_*    : Creates a new instance of the layer.
*_forward : During this operation, the layer takes a set of input volumes and transforms them into a set of output volumes (one output for each input).
*_load    : Loads the layer's weights from an file (if applicable).
