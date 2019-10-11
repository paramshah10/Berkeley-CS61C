#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "network.h"
#include "volume.h"

// Place where test data is stored on instructional machines.
const char* DATA_FOLDER = "/home/ff/cs61c/proj4/cifar-10-batches-bin";
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
network_t* load_cnn_snapshot() {
  network_t* net = make_network();
  conv_load(net->l0, "./snapshot/layer1_conv.txt");
  conv_load(net->l3, "./snapshot/layer4_conv.txt");
  conv_load(net->l6, "./snapshot/layer7_conv.txt");
  fc_load(net->l9, "./snapshot/layer10_fc.txt");
  return net;
}

// Load an image from the cifar10 data set.
void load_sample(volume_t* v, int sample_num) {
  printf("Loading input sample %d...\n", sample_num);

  int batch = sample_num / 10000;
  int ix    = sample_num % 10000;

  char file_name[1024];
  sprintf(file_name, "%s/data_batch_%d.bin", DATA_FOLDER, batch + 1);

  FILE* fin = fopen(file_name, "rb");
  assert(fin != NULL);

  fseek(fin, ix * 3073, SEEK_SET);

  uint8_t data[3073];
  assert(fread(data, 1, 3073, fin) == 3073);

  int outp = 1;
  for (int d = 0; d < 3; d++) {
    for (int y = 0; y < 32; y++) {
      for (int x = 0; x < 32; x++) {
        volume_set(v, x, y, d, ((double)data[outp++]) / 255.0 - 0.5);
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
  sprintf(file_name, "%s/data_batch_%d.bin", DATA_FOLDER, batch + 1);

  FILE* fin = fopen(file_name, "rb");
  assert(fin != NULL);
  batch_t batchdata = malloc(sizeof(volume_t*) * 10000);

  for (int i = 0; i < 10000; i++) {
    batchdata[i] = make_volume(32, 32, 3, 0.0);

    uint8_t data[3073];
    assert(fread(data, 1, 3073, fin) == 3073);

    int outp = 1;
    for (int d = 0; d < 3; d++) {
      for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 32; x++) {
          volume_set(batchdata[i], x, y, d, ((double)data[outp++]) / 255.0 - 0.5);
        }
      }
    }
  }

  fclose(fin);

  return batchdata;
}

// Computes the accuracy of our neural network by comparing our predicted values
// with the actual labels.
double get_accuracy(int* samples, int* predictions, int n) {
  int num_correct = 0;

  char file_name[1024];

  // Open all data batch files.
  FILE* batch_files[5];
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

  return ((double)num_correct) / n;
}

// Perform the classification (this calls into the functions from network.c)
void run_classification(int* samples, int n, double*** keep_likelihoods) {
  printf("Making network...\n");
  network_t* net = load_cnn_snapshot();

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

  volume_t** input = (volume_t**)malloc(sizeof(volume_t*) * n);
  for (int i = 0; i < n; i++) {
    input[i] = batches[samples[i] / 10000][samples[i] % 10000];
  }

  double** likelihoods = (double**)malloc(sizeof(double*) * n);
  for (int c = 0; c < n; c++) {
    likelihoods[c] = (double*)malloc(sizeof(double) * NUM_CLASSES);
  }

  printf("Running classification...\n");
  net_classify(net, input, likelihoods, n);

  int predictions[n];
  for (int i = 0; i < n; i++) {
    int best_class        = -1;
    double max_likelihood = -INFINITY;
    for (int c = 0; c < NUM_CLASSES; c++) {
      if (max_likelihood < likelihoods[i][c]) {
        max_likelihood = likelihoods[i][c];
        best_class     = c;
      }
    }
    predictions[i] = best_class;
  }

  printf("%lf%% accuracy\n", 100 * get_accuracy(samples, predictions, n));

  free_network(net);
  free(input);

  for (int i = 0; i < 50; i++) {
    if (batches[i] != NULL) {
      for (int j = 0; j < 10000; j++) {
        free_volume(batches[i][j]);
      }
      free(batches[i]);
    }
  }

  if (keep_likelihoods == NULL) {
    for (int i = 0; i < n; i++) {
      free(likelihoods[i]);
    }
    free(likelihoods);
  } else {
    *keep_likelihoods = likelihoods;
  }
}

// Run benchmark on a specified number samples (if there is none, then
// DEFAULT_BENCHMARK_SIZE). Returns the number of seconds taken to perform the
// benchmark.
void do_benchmark(int argc, char** argv) {
  int num_samples = DEFAULT_BENCHMARK_SIZE;
  if (argc > 0) {
    num_samples = atoi(argv[0]);
  }

  printf("RUNNING BENCHMARK ON %d PICTURES...\n", num_samples);

  // Pick DEFAULT_BENCHMARK_SIZE random samples, it doesn't matter which.
  int* samples = (int*)malloc(sizeof(int) * num_samples);
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
void do_layers_test(int argc, char** argv) {
  int sample_num = 0;

  if (argc > 0) {
    sample_num = atoi(argv[0]);
  }

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
void do_parallel_test(int argc, char** argv) {
  int test_size = PARTEST_SIZE;

  if (argc > 0) {
    test_size = atoi(argv[0]);
  }

  srand(1234);

  int* samples = (int*)malloc(sizeof(int) * test_size);
  for (int i = 0; i < test_size; i++) {
    samples[i] = (int)((double)rand() / ((double)RAND_MAX + 1) * 50000);
  }

  double** kept_output;
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

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("Usage: ./benchmark <benchmark|test|partest> [args]\n");
    return 2;
  }

  if (!strcmp(argv[1], "benchmark")) {
    do_benchmark(argc - 2, argv + 2);
    return 0;
  }

  if (!strcmp(argv[1], "test")) {
    do_layers_test(argc - 2, argv + 2);
    return 0;
  }

  if (!strcmp(argv[1], "partest")) {
    do_parallel_test(argc - 2, argv + 2);
    return 0;
  }

  printf("ERROR: Unknown command\n");

  return 2;
}

