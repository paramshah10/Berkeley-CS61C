#ifndef LAYERS_H
#define LAYERS_H

#include <stddef.h>

#include "volume.h"

// What follows are the different layers of the CNN. You will not have to
// understand what these layers are actually doing. In general, each layer has
// the following operations:
//
// make_*    : Creates a new instance of the layer.
// *_forward : During this operation, the layer takes a set of input volumes
//             and transforms them into a set of output volumes (one output for
//             each input).
// *_load    : Loads the layer's weights from an file (if applicable).
//
// NOTE: You will only have to make changes to the *_forward functions for each
// layer.

// Convolutional Layer Parameters
typedef struct conv_layer {
  // Required
  int input_depth;
  int input_width;
  int input_height;
  int filter_width;
  int filter_height;
  int stride;
  int pad;
  int output_depth;

  // Computed
  int output_width;
  int output_height;
  double bias;
  volume_t* biases;
  volume_t** filters;
} conv_layer_t;

// Creates a convolutional layer with the following parameters.
conv_layer_t* make_conv_layer(int input_width, int input_height, int input_depth, int filter_width, int num_filters,
                              int stride, int pad);

// Computes the forward pass for a convolutional layer on the relevant inputs
// and stores the result into the relevant outputs.
void conv_forward(conv_layer_t* l, volume_t** inputs, volume_t** outputs, int start, int end);

// Loads the convolutional layer weights from a file.
void conv_load(conv_layer_t* l, const char* file_name);

// ReLU Layer Parameters
typedef struct relu_layer {
  // Required
  int input_depth;
  int input_width;
  int input_height;

  // Computed
  int output_depth;
  int output_width;
  int output_height;
} relu_layer_t;

// Creates a ReLU layer with the following parameters.
relu_layer_t* make_relu_layer(int input_width, int input_height, int input_depth);

// Computes the forward pass for a ReLU layer (for the relevant inputs) and
// stores the result into the relevant outputs.
void relu_forward(relu_layer_t* l, volume_t** inputs, volume_t** outputs, int start, int end);

// Pool Layer Parameters
typedef struct pool_layer {
  // Required
  int pool_width;
  int input_depth;
  int input_width;
  int input_height;

  // Computed
  int pool_height;
  int stride;
  int pad;
  int output_depth;
  int output_width;
  int output_height;
} pool_layer_t;

// Creates a max pool layer with the following parameters.
pool_layer_t* make_pool_layer(int input_width, int input_height, int input_depth, int pool_width,
                              int stride);

// Computes the forward pass for a max pool layer on the relevant inputs and
// stores the result into the relevant outputs.
void pool_forward(pool_layer_t* l, volume_t** inputs, volume_t** outputs, int start, int end);

// FC Layer Parameters
typedef struct fc_layer {
  // Required
  int output_depth;
  int input_depth;
  int input_width;
  int input_height;

  // Computed
  int output_width;
  int output_height;
  int num_inputs;
  double bias;
  volume_t* biases;
  volume_t** filters;
} fc_layer_t;

// Creates a fully-connected layer with the following parameters.
fc_layer_t* make_fc_layer(int input_width, int input_height, int input_depth, int num_neurons);

// Computes the forward pass for a fully-connected layer on the relevant inputs
// and stores the result into the relevant outputs.
void fc_forward(fc_layer_t* l, volume_t** inputs, volume_t** outputs, int start, int end);

// Loads the fully-connected layer weights from a file.
void fc_load(fc_layer_t* l, const char* filename);

// Softmax Layer Parameters
typedef struct softmax_layer {
  // Required
  int input_depth;
  int input_width;
  int input_height;
  double* likelihoods;

  // Computed
  int output_depth;
  int output_width;
  int output_height;
} softmax_layer_t;

// Creates a softmax layer with the following parameters.
softmax_layer_t* make_softmax_layer(int input_width, int input_height, int input_depth);

// Computes the forward pass for a softmax layer on the relevant inputs and
// stores the result into the relevant outputs.
void softmax_forward(softmax_layer_t* l, volume_t** inputs, volume_t** outputs, int start, int end);

#endif

