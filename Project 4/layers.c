#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Include SSE intrinsics
#if defined(_MSC_VER)
#include <intrin.h>
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
#include <immintrin.h>
#include <x86intrin.h>
#endif

// Include OpenMP
#include <omp.h>

#include "layers.h"
#include "volume.h"

conv_layer_t* make_conv_layer(int input_width, int input_height, int input_depth, int filter_width, int num_filters, int stride, int pad)
{
  conv_layer_t* l = (conv_layer_t*)malloc(sizeof(conv_layer_t));

  l->output_depth = num_filters;
  l->filter_width = filter_width;
  l->input_depth  = input_depth;
  l->input_width  = input_width;
  l->input_height = input_height;

  l->filter_height = l->filter_width;
  l->stride        = stride;
  l->pad = pad;

  l->output_width = (l->input_width + l->pad * 2 - l->filter_width) / l->stride + 1;
  l->output_height = (l->input_height + l->pad * 2 - l->filter_height) / l->stride + 1;

  l->filters = malloc(sizeof(volume_t*) * num_filters);
  for (int i = 0; i < num_filters; i++) {
    l->filters[i] = make_volume(l->filter_width, l->filter_height,
                                l->input_depth, 0.0);
  }

  l->bias   = 0.0;
  l->biases = make_volume(1, 1, l->output_depth, l->bias);

  return l;
}

// Performs the forward pass for a convolutional layer by convolving each one
// of the filters with a particular input, and placing the result in the output
// array.
//
// One way to think about convolution in this case is that we have one of the
// layer's filters (a 3D array) that is superimposed on one of the layer's
// inputs (a second 3D array) that has been implicitly padded with zeros. Since
// convolution is a sum of products (described below), we don't actually have
// to add any zeros to the input volume since those terms will not contribute
// to the convolution. Instead, for each position in the filter, we just make
// sure that we are in bounds for the input volume.
//
// Essentially, the filter is "sliding" across the input, in both the x and y
// directions, where we increment our position in each direction by using the
// stride parameter.
//
// At each position, we compute the sum of the elementwise product of the filter
// and the part of the array it's covering. For instance, let's consider a 2D
// case, where the filter (on the left) is superimposed on some part of the
// input (on the right).
//
//   Filter             Input
//  -1  0  1           1  2  3
//  -1  0  1           4  5  6
//  -1  0  1           7  8  9
//
// Here, the sum of the elementwise product is:
//    Filter[0][0] * Input[0][0] + Filter[0][1] * Input[0][1] + ...
//    = -1 * 1 + 0 * 2 + ... + 0 * 8 + 1 * 9
//    = 6
//
// The 3D case is essentially the same, we just have to sum over the other
// dimension as well. Also, since volumes are internally represented as 1D
// arrays, we must use the volume_get and volume_set commands to access elements
// at a coordinate (x, y, d). Finally, we add the corresponding bias for the
// filter to the sum before putting it into the output volume.
void conv_forward(conv_layer_t* l, volume_t** inputs, volume_t** outputs, int start, int end)
{
  int stride = l->stride;                     //create these variables before hand so that they don't have to be calculated each time
  int depth = l->output_depth;
  int height = l->output_height;
  int width = l->output_width;


    volume_t* in  = inputs[0];
    volume_t* out = outputs[0];
    int in_width = in->width;                 //don't need to be evaluated each time the loop runs
    int in_height = in->height;
    for (int f = 0; f < depth; f++)             ///put this here Instead because to preseve spatial locality
    {
      volume_t* filter = l->filters[f];
      int filter_height = filter->height;     //don't need to be evaluated each time the loop runs
      int filter_width = filter->width;
      int filter_depth = filter->depth;

      int y = -l->pad;
      for (int out_y = 0; out_y < height; y += stride, out_y++)
      {
        int x = -l->pad;
        for (int out_x = 0; out_x < width; x += stride, out_x++)
        {
          // Take sum of element-wise product
          double sum = 0.0;
          int fy;
          if (y < 0.0)
          {
            fy = -1*y;
          }
          else
          {
            fy = 0;
          }
          for (; fy < filter_height; fy++)
          {
            int in_y = y + fy;
            int fx;
            if (x < 0.0)
            {
              fx = -1*x;
            }
            else
            {
              fx = 0;
            }
            for (; fx < filter_width; fx++)
            {
              int in_x = x + fx;

              if (in_y >= 0 && in_y < in_height && in_x >= 0 && in_x < in_width)
              {
                if (filter_depth == 3)
                {
                  sum += filter->weights[((filter->width * fy) + fx) * filter->depth] * in->weights[((in->width * in_y) + in_x) * in->depth];
                  sum += filter->weights[((filter->width * fy) + fx) * filter->depth + 1] * in->weights[((in->width * in_y) + in_x) * in->depth + 1];
                  sum += filter->weights[((filter->width * fy) + fx) * filter->depth + 2] * in->weights[((in->width * in_y) + in_x) * in->depth + 2];
                }
                else if (filter_depth == 16)
                {
                  __m256d simdSum = _mm256_set1_pd(0.0);
                  __m256d temp1 = _mm256_loadu_pd (&filter->weights[((filter->width * fy) + fx) * filter->depth]);
                  __m256d temp2 = _mm256_loadu_pd (&in->weights[((in->width * in_y) + in_x) * in->depth]);
                  temp1 = _mm256_mul_pd (temp2, temp1);
                  simdSum = _mm256_add_pd (simdSum, temp1);

                  temp1 = _mm256_loadu_pd (&filter->weights[((filter->width * fy) + fx) * filter->depth + 4]);
                  temp2 = _mm256_loadu_pd (&in->weights[((in->width * in_y) + in_x) * in->depth + 4]);
                  temp1 = _mm256_mul_pd (temp2, temp1);
                  simdSum = _mm256_add_pd (simdSum, temp1);

                  temp1 = _mm256_loadu_pd (&filter->weights[((filter->width * fy) + fx) * filter->depth + 8]);
                  temp2 = _mm256_loadu_pd (&in->weights[((in->width * in_y) + in_x) * in->depth + 8]);
                  temp1 = _mm256_mul_pd (temp2, temp1);
                  simdSum = _mm256_add_pd (simdSum, temp1);

                  temp1 = _mm256_loadu_pd (&filter->weights[((filter->width * fy) + fx) * filter->depth + 12]);
                  temp2 = _mm256_loadu_pd (&in->weights[((in->width * in_y) + in_x) * in->depth + 12]);
                  temp1 = _mm256_mul_pd (temp2, temp1);
                  simdSum = _mm256_add_pd (simdSum, temp1);

                  double p[4];
                  _mm256_storeu_pd(p, simdSum);

                  sum = (sum + p[0] + p[1] + p[2] + p[3]);
                }

                else
                {
                  __m256d simdSum = _mm256_set1_pd(0.0);
                  __m256d temp1 = _mm256_loadu_pd (&filter->weights[((filter->width * fy) + fx) * filter->depth]);
                  __m256d temp2 = _mm256_loadu_pd (&in->weights[((in->width * in_y) + in_x) * in->depth]);
                  temp1 = _mm256_mul_pd (temp2, temp1);
                  simdSum = _mm256_add_pd (simdSum, temp1);

                  temp1 = _mm256_loadu_pd (&filter->weights[((filter->width * fy) + fx) * filter->depth + 4]);
                  temp2 = _mm256_loadu_pd (&in->weights[((in->width * in_y) + in_x) * in->depth + 4]);
                  temp1 = _mm256_mul_pd (temp2, temp1);
                  simdSum = _mm256_add_pd (simdSum, temp1);

                  temp1 = _mm256_loadu_pd (&filter->weights[((filter->width * fy) + fx) * filter->depth + 8]);
                  temp2 = _mm256_loadu_pd (&in->weights[((in->width * in_y) + in_x) * in->depth + 8]);
                  temp1 = _mm256_mul_pd (temp2, temp1);
                  simdSum = _mm256_add_pd (simdSum, temp1);

                  temp1 = _mm256_loadu_pd (&filter->weights[((filter->width * fy) + fx) * filter->depth + 12]);
                  temp2 = _mm256_loadu_pd (&in->weights[((in->width * in_y) + in_x) * in->depth + 12]);
                  temp1 = _mm256_mul_pd (temp2, temp1);
                  simdSum = _mm256_add_pd (simdSum, temp1);

                  temp1 = _mm256_loadu_pd (&filter->weights[((filter->width * fy) + fx) * filter->depth + 16]);
                  temp2 = _mm256_loadu_pd (&in->weights[((in->width * in_y) + in_x) * in->depth + 16]);
                  temp1 = _mm256_mul_pd (temp2, temp1);
                  simdSum = _mm256_add_pd (simdSum, temp1);

                  double p[4];
                  _mm256_storeu_pd(p, simdSum);

                  sum = (sum + p[0] + p[1] + p[2] + p[3]);
                }
              }
            }
          }
          sum += l->biases->weights[f];
          //volume_set(out, out_x, out_y, f, sum);
          out->weights[((out->width * out_y) + out_x) * out->depth + f] = sum;
        }
      }
    }

}

void conv_load(conv_layer_t* l, const char* file_name)
{
  int filter_width;
  int filter_height;
  int depth;
  int filters;

  FILE* fin = fopen(file_name, "r");

  fscanf(fin, "%d %d %d %d", &filter_width, &filter_height, &depth, &filters);
  assert(filter_width == l->filter_width);
  assert(filter_height == l->filter_height);
  assert(depth == l->input_depth);
  assert(filters == l->output_depth);

  for (int f = 0; f < filters; f++)                      //loop reordering doesnt work here. Ask why (messes up the accuracy)
  {
    for (int x = 0; x < filter_width; x++)
    {
      for (int y = 0; y < filter_height; y++)
      {
        for (int d = 0; d < depth; d++)
        {
          double val;
          fscanf(fin, "%lf", &val);
          //volume_set(l->filters[f], x, y, d, val);
          l->filters[f]->weights[((l->filters[f]->width * y) + x) * l->filters[f]->depth + d] = val;
        }
      }
    }
  }

  for (int d = 0; d < l->output_depth; d++)
  {
    double val;
    fscanf(fin, "%lf", &val);
    //volume_set(l->biases, 0, 0, d, val);
    l->biases->weights[((l->biases->width * 0) + 0) * l->biases->depth + d] = val;
  }

  fclose(fin);
}

relu_layer_t* make_relu_layer(int input_width, int input_height, int input_depth)
{
  relu_layer_t* l = (relu_layer_t*)malloc(sizeof(relu_layer_t));

  l->input_depth  = input_depth;
  l->input_width  = input_width;
  l->input_height = input_height;

  l->output_width  = l->input_width;
  l->output_height = l->input_height;
  l->output_depth  = l->input_depth;

  return l;
}

// Applies the Rectifier Linear Unit (ReLU) function to the input, which sets
// output(x, y, d) to max(0.0, input(x, y, d)).
void relu_forward(relu_layer_t* l, volume_t** inputs, volume_t** outputs, int start, int end)
{
  int input_width = l->input_width;
  int input_height = l->input_height;
  int input_depth = l->input_depth;

//  printf("relu_load depth is: %d ", input_depth);

    for (int x = 0; x < input_width; x++)                   //loop ordering somehow does not work here
    {
      for (int y = 0; y < input_height; y++)
      {
        for (int d = 0; d < input_depth; d++)
        {
          //double value = (volume_get(inputs[i], x, y, d) < 0.0) ? 0.0 : volume_get(inputs[i], x, y, d);
          double value = (inputs[0]->weights[((inputs[0]->width * y) + x) * inputs[0]->depth + d] < 0.0) ? 0.0 : inputs[0]->weights[((inputs[0]->width * y) + x) * inputs[0]->depth + d];
          //volume_set(outputs[i], x, y, d, value);
          outputs[0]->weights[((outputs[0]->width * y) + x) * outputs[0]->depth + d] = value;
        }
      }
    }

}

pool_layer_t* make_pool_layer(int input_width, int input_height, int input_depth, int pool_width, int stride)
{
  pool_layer_t* l = (pool_layer_t*)malloc(sizeof(pool_layer_t));

  l->pool_width   = pool_width;
  l->input_depth  = input_depth;
  l->input_width  = input_width;
  l->input_height = input_height;

  l->pool_height = l->pool_width;
  l->stride      = stride;
  l->pad         = 0;

  l->output_depth  = input_depth;
  l->output_width  = floor((l->input_width + l->pad * 2 - l->pool_width) / l->stride + 1);
  l->output_height = floor((l->input_height + l->pad * 2 - l->pool_height) / l->stride + 1);

  return l;
}

// This is like the convolutional layer in that we are sliding across the input
// volume, but instead of having a filter that we use to find the sum of an
// elementwise product, we instead just output the max value of some part of
// the image. For instance, if we consider a 2D case where the following is the
// part of the input that we are considering:
//
//     1 3 5
//     4 2 1
//     2 2 2
//
// then the value of the corresponding element in the output is 5 (since that
// is the maximum element). This effectively compresses the input.
void pool_forward(pool_layer_t* l, volume_t** inputs, volume_t** outputs, int start, int end)
{
  int stride = l->stride;
  int output_depth = l->output_depth;
  int output_width = l->output_width;
  int output_height = l->output_height;
  int pool_width = l->pool_width;
  int pool_height = l->pool_height;


    volume_t* in  = inputs[0];
    volume_t* out = outputs[0];

    int in_width = in->width;
    int in_height = in->height;
    int in_depth = in->depth;
    int out_width = out->width;
    int out_depth = out->depth;

    int n = 0;

    for (int d = 0; d < output_depth; d++)
    {
      int x = -l->pad;
      for (int out_x = 0; out_x < output_width; x += stride, out_x++)
      {
        int y = -l->pad;
        for (int out_y = 0; out_y < output_height; y += stride, out_y++)
        {
          double max = -INFINITY;
          for (int fx = 0; fx < pool_width; fx++)
          {
            for (int fy = 0; fy < pool_height; fy++)
            {
              int in_y = y + fy;
              int in_x = x + fx;
              if (in_x >= 0 && in_x < in_width && in_y >= 0 && in_y < in_height)
              {
                //double v = volume_get(in, in_x, in_y, d);
                double v = in->weights[((in_width * in_y) + in_x) * in_depth + d];
                if (v > max)
                {
                  max = v;
                }
              }
            }
          }

          n++;
          //volume_set(out, out_x, out_y, d, max);
          out->weights[((out_width * out_y) + out_x) * out_depth + d] = max;
        }
      }
    }

}

fc_layer_t* make_fc_layer(int input_width, int input_height, int input_depth, int num_neurons)
{
  fc_layer_t* l = (fc_layer_t*)malloc(sizeof(fc_layer_t));

  l->output_depth = num_neurons;
  l->input_depth  = input_depth;
  l->input_width  = input_width;
  l->input_height = input_height;

  l->num_inputs    = l->input_width * l->input_height * l->input_depth;
  l->output_width  = 1;
  l->output_height = 1;

  l->filters = (volume_t**)malloc(sizeof(volume_t*) * num_neurons);
  for (int i = 0; i < l->output_depth; i++)
  {
    l->filters[i] = make_volume(1, 1, l->num_inputs, 0.0);
  }

  l->bias   = 0.0;
  l->biases = make_volume(1, 1, l->output_depth, l->bias);

  return l;
}

// Computes the dot product (i.e. the sum of the elementwise product) of the
// input's weights with each of the filters. Note that these filters are not
// the same as the filters for the convolutional layer.
void fc_forward(fc_layer_t* l, volume_t** inputs, volume_t** outputs, int start, int end)
{


      volume_t* in  = inputs[0];
      volume_t* out = outputs[0];

      for (int i = 0; i < l->output_depth; i++)
      {
        double dot = 0.0;

        for (int d = 0; d < l->num_inputs; d++)
        {
          dot += in->weights[d] * l->filters[i]->weights[d];
        }
        dot += l->biases->weights[i];
        out->weights[i] = dot;
      }

}

void fc_load(fc_layer_t* l, const char* filename)
{
  FILE* fin = fopen(filename, "r");

  int num_inputs;
  int output_depth;
  fscanf(fin, "%d %d", &num_inputs, &output_depth);
  assert(output_depth == l->output_depth);
  assert(num_inputs == l->num_inputs);

  for (int i = 0; i < l->output_depth; i++)
  {
    for (int j = 0; j < l->num_inputs; j++)
    {
      fscanf(fin, "%lf", &(l->filters[i]->weights[j]));
    }
  }

  for (int i = 0; i < l->output_depth; i++)
  {
    fscanf(fin, "%lf", &(l->biases->weights[i]));
  }

  fclose(fin);
}

softmax_layer_t* make_softmax_layer(int input_width, int input_height, int input_depth)
{
  softmax_layer_t* l = (softmax_layer_t*)malloc(sizeof(softmax_layer_t));

  l->input_depth  = input_depth;
  l->input_width  = input_width;
  l->input_height = input_height;

  l->output_width  = 1;
  l->output_height = 1;
  l->output_depth  = l->input_width * l->input_height * l->input_depth;

  l->likelihoods = (double*)malloc(sizeof(double) * l->output_depth);

  return l;
}

// This function converts an input's weights array into a probability
// distribution by using the following formula:
//
// likelihood[i] = exp(in->weights[i]) / sum(exp(in->weights))
//
// To increase the numerical stability of taking the exponential of a value, we
// subtract the maximum input weights from each weight before taking the
// exponential. This yields exactly the same results as the expression above,
// but is more resilient to floating point errors.
void softmax_forward(softmax_layer_t* l, volume_t** inputs, volume_t** outputs, int start, int end)
{
  double likelihoods[l->output_depth];

  volume_t* in  = inputs[0];
  volume_t* out = outputs[0];

  // Compute max activation (used to compute exponentials)
  double amax = in->weights[0];
  double* in_weights = in->weights;
  for (int i = 1; i < l->output_depth; i++)
  {
    if (in_weights[i] > amax)
    {
      amax = in_weights[i];
    }
  }
  // Compute exponentials in a numerically stable way
  double total = 0.0;

  for (int i = 0; i < l->output_depth; i++)
  {
    double e = exp(in_weights[i] - amax);
    total += e;
    likelihoods[i] = e;
  }

  // Normalize and output to sum to one
  double* out_weights = out->weights;
  // for (int i = 0; i < l->output_depth; i++)
  // {
  //   out_weights[i] = likelihoods[i] / total;
  // }

  __m256d div = _mm256_loadu_pd(likelihoods);
  __m256d simtotal = _mm256_set1_pd(total);
  div = _mm256_div_pd(div, simtotal);
  _mm256_storeu_pd(out_weights, div);

  div = _mm256_loadu_pd(likelihoods + 4);
  div = _mm256_div_pd(div, simtotal);
  _mm256_storeu_pd(out_weights + 4, div);

  out_weights[8] = likelihoods[8] / total;
  out_weights[9] = likelihoods[9] / total;
}
