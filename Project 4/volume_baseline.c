#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "volume.h"

inline double volume_get(volume_t* v, int x, int y, int d) {
  return v->weights[((v->width * y) + x) * v->depth + d];
}

inline void volume_set(volume_t* v, int x, int y, int d, double value) {
  v->weights[((v->width * y) + x) * v->depth + d] = value;
}

volume_t* make_volume(int width, int height, int depth, double value) {
  volume_t* new_vol = malloc(sizeof(struct volume));
  new_vol->weights = malloc(sizeof(double) * width * height * depth);

  new_vol->width  = width;
  new_vol->height = height;
  new_vol->depth  = depth;

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      for (int d = 0; d < depth; d++) {
        volume_set(new_vol, x, y, d, value);
      }
    }
  }

  return new_vol;
}

void copy_volume(volume_t* dest, volume_t* src) {
  assert(dest->width == src->width);
  assert(dest->height == src->height);
  assert(dest->depth == src->depth);

  for (int x = 0; x < dest->width; x++) {
    for (int y = 0; y < dest->height; y++) {
      for (int d = 0; d < dest->depth; d++) {
        volume_set(dest, x, y, d, volume_get(src, x, y, d));
      }
    }
  }
}

void free_volume(volume_t* v) {
  free(v->weights);
  free(v);
}

