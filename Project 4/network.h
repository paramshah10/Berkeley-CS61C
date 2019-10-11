#ifndef NETWORK_H
#define NETWORK_H

#include "layers.h"
#include "volume.h"

#define NUM_LAYERS 11
#define NUM_CLASSES 10

// Defines the specific network architecture that we use for this project. Layer
// elements in the struct are in the same order as they are in the network
// itself.
typedef struct network {
  volume_t* layers[NUM_LAYERS + 1];
  conv_layer_t* l0;
  relu_layer_t* l1;
  pool_layer_t* l2;
  conv_layer_t* l3;
  relu_layer_t* l4;
  pool_layer_t* l5;
  conv_layer_t* l6;
  relu_layer_t* l7;
  pool_layer_t* l8;
  fc_layer_t* l9;
  softmax_layer_t* l10;
} network_t;

// Creates a new instance of our network
network_t* make_network();

// Frees our network
void free_network(network_t* net);

// We organize data as "batches" of volumes. Each batch consists of a number of
// samples, each of which contains a volume for every intermediate layer. Say we
// have L layers and a set of N input images. Then batch[l][n] contains the
// volume at layer l for input image n.
//
// By using batches, we can process multiple images at once in each run of the
// forward functions of the different layers.
typedef volume_t** batch_t;

// Allocates a new batch for the network old_net with size images
batch_t* make_batch(network_t* net, int size);

// Frees a previously allocated batch
void free_batch(batch_t* v, int size);

// Apply our network to a specific batch of inputs. The batch has to be given
// as input to v and start/end are the first and the last image in that batch
// to process (start and end are inclusive).
void net_forward(network_t* net, batch_t* b, int start, int end);

// Putting everything together: Take a set of n input images as 3-dimensional
// Volumes and process them using the CNN in batches of 1. It saves the
// likelihood of each label into the likelihoods array.
void net_classify(network_t* net, volume_t** input, double** likelihoods, int n);

#endif

