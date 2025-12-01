/*
 * GENANN - Minimal C Artificial Neural Network
 *
 * Copyright (c) 2015-2018 Lewis Van Winkle
 *
 * http://CodePlea.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgement in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

#include "genann.h"
#include "minctest.h"
#include <bench.h>
#include <stdlib.h>

static const struct {
  int loops;
  int correct;
  uint32_t cs1, cs2, cs3;
  uint64_t ref_time;
} *ps, settings[BENCH_NR_SETTING] = {
         {0, 50, 0xb94aa991, 0x56737059, 0xc180f104, 0},
         {4, 80, 0x6534b5a8, 0x4ac24b94, 0x06adffe1, 66},
         {20000, 147, 0x8b6aa37f, 0xb5796f2e, 0x631fc3f2, 243780},
         {1000000, 149, 0x0d457d31, 0x655161ef, 0xc180f104, 12477223},
};

void basic() {
  genann *ann = genann_init(1, 0, 0, 1);

  lequal(ann->total_weights, 2);
  int a;

  a = 0;
  ann->weight[0] = 0;
  ann->weight[1] = 0;
  lfequal(HALF, *genann_run(ann, &a));

  a = ONE;
  lfequal(HALF, *genann_run(ann, &a));

  a = SCALE_UP(11);
  lfequal(HALF, *genann_run(ann, &a));

  a = SCALE_UP(1);
  ann->weight[0] = ONE;
  ann->weight[1] = ONE;
  lfequal(HALF, *genann_run(ann, &a));

  a = SCALE_UP(10);
  ann->weight[0] = ONE;
  ann->weight[1] = ONE;
  lfequal(ONE, *genann_run(ann, &a));

  a = SCALE_UP(-10);
  lfequal(0, *genann_run(ann, &a));

  genann_free(ann);
}

void xor_() {
  genann *ann = genann_init(2, 1, 2, 1);
  ann->activation_hidden = genann_act_threshold;
  ann->activation_output = genann_act_threshold;

  lequal(ann->total_weights, 9);

  /* First hidden. */
  ann->weight[0] = HALF;
  ann->weight[1] = ONE;
  ann->weight[2] = ONE;

  /* Second hidden. */
  ann->weight[3] = ONE;
  ann->weight[4] = ONE;
  ann->weight[5] = ONE;

  /* Output. */
  ann->weight[6] = HALF;
  ann->weight[7] = ONE;
  ann->weight[8] = -ONE;

  int input[4][2] = {{0, 0}, {0, ONE}, {ONE, 0}, {ONE, ONE}};
  int output[4] = {0, ONE, ONE, 0};

  lfequal(output[0], *genann_run(ann, input[0]));
  lfequal(output[1], *genann_run(ann, input[1]));
  lfequal(output[2], *genann_run(ann, input[2]));
  lfequal(output[3], *genann_run(ann, input[3]));

  genann_free(ann);
}

void backprop() {
  genann *ann = genann_init(1, 0, 0, 1);

  int input, output;
  input = HALF;
  output = ONE;

  int first_try = *genann_run(ann, &input);
  genann_train(ann, &input, &output, HALF);
  int second_try = *genann_run(ann, &input);
  lok(abs(first_try - output) > abs(second_try - output));

  genann_free(ann);
}

void train_and() {
  int input[4][2] = {{0, 0}, {0, ONE}, {ONE, 0}, {ONE, ONE}};
  int output[4] = {0, 0, 0, ONE};

  genann *ann = genann_init(2, 0, 0, 1);

  int i, j;

  for (i = 0; i < 20; ++i) {
    for (j = 0; j < 4; ++j) {
      genann_train(ann, input[j], output + j, SCALE * 4 / 5);
    }
  }

  ann->activation_output = genann_act_threshold;
  lfequal(output[0], *genann_run(ann, input[0]));
  lfequal(output[1], *genann_run(ann, input[1]));
  lfequal(output[2], *genann_run(ann, input[2]));
  lfequal(output[3], *genann_run(ann, input[3]));

  genann_free(ann);
}

void train_or() {
  int input[4][2] = {{0, 0}, {0, ONE}, {ONE, 0}, {ONE, ONE}};
  int output[4] = {0, ONE, ONE, ONE};

  genann *ann = genann_init(2, 0, 0, 1);
  genann_randomize(ann);

  int i, j;

  for (i = 0; i < 25; ++i) {
    for (j = 0; j < 4; ++j) {
      genann_train(ann, input[j], output + j, SCALE * 4 / 5);
    }
  }

  ann->activation_output = genann_act_threshold;
  lfequal(output[0], *genann_run(ann, input[0]));
  lfequal(output[1], *genann_run(ann, input[1]));
  lfequal(output[2], *genann_run(ann, input[2]));
  lfequal(output[3], *genann_run(ann, input[3]));

  genann_free(ann);
}

void train_xor() {
  int input[4][2] = {{0, 0}, {0, ONE}, {ONE, 0}, {ONE, ONE}};
  int output[4] = {0, ONE, ONE, 0};

  genann *ann = genann_init(2, 1, 2, 1);

  int i, j;

  for (i = 0; i < 310; ++i) {
    for (j = 0; j < 4; ++j) {
      genann_train(ann, input[j], output + j, SCALE_UP(3));
    }
    /* printf("%1.2f ", xor_score(ann)); */
  }

  ann->activation_output = genann_act_threshold;
  lfequal(output[0], *genann_run(ann, input[0]));
  lfequal(output[1], *genann_run(ann, input[1]));
  lfequal(output[2], *genann_run(ann, input[2]));
  lfequal(output[3], *genann_run(ann, input[3]));

  genann_free(ann);
}

typedef struct IRIS_data { // See iris.names for details.
  int attr[4];             // length in mm
  int label;               // 0 - Iris Setosa, 1 - Iris Versicolour, 2 - Iris Virginica
} IRIS_data;
static const IRIS_data iris_data[] = {
  {{51, 35, 14, 2}, 0},  {{49, 30, 14, 2}, 0},  {{47, 32, 13, 2}, 0},  {{46, 31, 15, 2}, 0},  {{50, 36, 14, 2}, 0},
  {{54, 39, 17, 4}, 0},  {{46, 34, 14, 3}, 0},  {{50, 34, 15, 2}, 0},  {{44, 29, 14, 2}, 0},  {{49, 31, 15, 1}, 0},
  {{54, 37, 15, 2}, 0},  {{48, 34, 16, 2}, 0},  {{48, 30, 14, 1}, 0},  {{43, 30, 11, 1}, 0},  {{58, 40, 12, 2}, 0},
  {{57, 44, 15, 4}, 0},  {{54, 39, 13, 4}, 0},  {{51, 35, 14, 3}, 0},  {{57, 38, 17, 3}, 0},  {{51, 38, 15, 3}, 0},
  {{54, 34, 17, 2}, 0},  {{51, 37, 15, 4}, 0},  {{46, 36, 10, 2}, 0},  {{51, 33, 17, 5}, 0},  {{48, 34, 19, 2}, 0},
  {{50, 30, 16, 2}, 0},  {{50, 34, 16, 4}, 0},  {{52, 35, 15, 2}, 0},  {{52, 34, 14, 2}, 0},  {{47, 32, 16, 2}, 0},
  {{48, 31, 16, 2}, 0},  {{54, 34, 15, 4}, 0},  {{52, 41, 15, 1}, 0},  {{55, 42, 14, 2}, 0},  {{49, 31, 15, 1}, 0},
  {{50, 32, 12, 2}, 0},  {{55, 35, 13, 2}, 0},  {{49, 31, 15, 1}, 0},  {{44, 30, 13, 2}, 0},  {{51, 34, 15, 2}, 0},
  {{50, 35, 13, 3}, 0},  {{45, 23, 13, 3}, 0},  {{44, 32, 13, 2}, 0},  {{50, 35, 16, 6}, 0},  {{51, 38, 19, 4}, 0},
  {{48, 30, 14, 3}, 0},  {{51, 38, 16, 2}, 0},  {{46, 32, 14, 2}, 0},  {{53, 37, 15, 2}, 0},  {{50, 33, 14, 2}, 0},
  {{70, 32, 47, 14}, 1}, {{64, 32, 45, 15}, 1}, {{69, 31, 49, 15}, 1}, {{55, 23, 40, 13}, 1}, {{65, 28, 46, 15}, 1},
  {{57, 28, 45, 13}, 1}, {{63, 33, 47, 16}, 1}, {{49, 24, 33, 10}, 1}, {{66, 29, 46, 13}, 1}, {{52, 27, 39, 14}, 1},
  {{50, 20, 35, 10}, 1}, {{59, 30, 42, 15}, 1}, {{60, 22, 40, 10}, 1}, {{61, 29, 47, 14}, 1}, {{56, 29, 36, 13}, 1},
  {{67, 31, 44, 14}, 1}, {{56, 30, 45, 15}, 1}, {{58, 27, 41, 10}, 1}, {{62, 22, 45, 15}, 1}, {{56, 25, 39, 11}, 1},
  {{59, 32, 48, 18}, 1}, {{61, 28, 40, 13}, 1}, {{63, 25, 49, 15}, 1}, {{61, 28, 47, 12}, 1}, {{64, 29, 43, 13}, 1},
  {{66, 30, 44, 14}, 1}, {{68, 28, 48, 14}, 1}, {{67, 30, 50, 17}, 1}, {{60, 29, 45, 15}, 1}, {{57, 26, 35, 10}, 1},
  {{55, 24, 38, 11}, 1}, {{55, 24, 37, 10}, 1}, {{58, 27, 39, 12}, 1}, {{60, 27, 51, 16}, 1}, {{54, 30, 45, 15}, 1},
  {{60, 34, 45, 16}, 1}, {{67, 31, 47, 15}, 1}, {{63, 23, 44, 13}, 1}, {{56, 30, 41, 13}, 1}, {{55, 25, 40, 13}, 1},
  {{55, 26, 44, 12}, 1}, {{61, 30, 46, 14}, 1}, {{58, 26, 40, 12}, 1}, {{50, 23, 33, 10}, 1}, {{56, 27, 42, 13}, 1},
  {{57, 30, 42, 12}, 1}, {{57, 29, 42, 13}, 1}, {{62, 29, 43, 13}, 1}, {{51, 25, 30, 11}, 1}, {{57, 28, 41, 13}, 1},
  {{63, 33, 60, 25}, 2}, {{58, 27, 51, 19}, 2}, {{71, 30, 59, 21}, 2}, {{63, 29, 56, 18}, 2}, {{65, 30, 58, 22}, 2},
  {{76, 30, 66, 21}, 2}, {{49, 25, 45, 17}, 2}, {{73, 29, 63, 18}, 2}, {{67, 25, 58, 18}, 2}, {{72, 36, 61, 25}, 2},
  {{65, 32, 51, 20}, 2}, {{64, 27, 53, 19}, 2}, {{68, 30, 55, 21}, 2}, {{57, 25, 50, 20}, 2}, {{58, 28, 51, 24}, 2},
  {{64, 32, 53, 23}, 2}, {{65, 30, 55, 18}, 2}, {{77, 38, 67, 22}, 2}, {{77, 26, 69, 23}, 2}, {{60, 22, 50, 15}, 2},
  {{69, 32, 57, 23}, 2}, {{56, 28, 49, 20}, 2}, {{77, 28, 67, 20}, 2}, {{63, 27, 49, 18}, 2}, {{67, 33, 57, 21}, 2},
  {{72, 32, 60, 18}, 2}, {{62, 28, 48, 18}, 2}, {{61, 30, 49, 18}, 2}, {{64, 28, 56, 21}, 2}, {{72, 30, 58, 16}, 2},
  {{74, 28, 61, 19}, 2}, {{79, 38, 64, 20}, 2}, {{64, 28, 56, 22}, 2}, {{63, 28, 51, 15}, 2}, {{61, 26, 56, 14}, 2},
  {{77, 30, 61, 23}, 2}, {{63, 34, 56, 24}, 2}, {{64, 31, 55, 18}, 2}, {{60, 30, 48, 18}, 2}, {{69, 31, 54, 21}, 2},
  {{67, 31, 56, 24}, 2}, {{69, 31, 51, 23}, 2}, {{58, 27, 51, 19}, 2}, {{68, 32, 59, 23}, 2}, {{67, 33, 57, 25}, 2},
  {{67, 30, 52, 23}, 2}, {{63, 25, 50, 19}, 2}, {{65, 30, 52, 20}, 2}, {{62, 34, 54, 23}, 2}, {{59, 30, 51, 18}, 2}};

int iris_test() {
  printf("Train an ANN on the IRIS dataset using backpropagation.\n");

  int loops = ps->loops;
  int samples = sizeof(iris_data) / sizeof(iris_data[0]);
  int *input = malloc(sizeof(int) * samples * 4);
  int *class = malloc(sizeof(int) * samples * 3);

  /* Preprocessing. */
  int i, j;
  for (i = 0; i < samples; i++) {
    int *p = input + i * 4;
    int *c = class + i * 3;
    c[0] = c[1] = c[2] = 0;

    for (j = 0; j < 4; j++) {
      p[j] = iris_data[i].attr[j] * ONE / 10;
    }
    c[iris_data[i].label] = ONE;
  }

  /* 4 inputs.
   * 1 hidden layer(s) of 4 neurons.
   * 3 outputs (1 per class)
   */
  genann *ann = genann_init(4, 1, 4, 3);

  /* Train the network with backpropagation. */
  printf("Training for %d loops over data.\n", loops);
  for (i = 0; i < loops; ++i) {
    for (j = 0; j < samples; ++j) {
      genann_train(ann, input + j * 4, class + j * 3, ONE / 100);
    }
  }

  int correct = 0;
  for (j = 0; j < samples; ++j) {
    const int *guess = genann_run(ann, input + j * 4);
    if (class[j * 3 + 0] == ONE) {
      if (guess[0] > guess[1] && guess[0] > guess[2])
        ++correct;
    } else if (class[j * 3 + 1] == ONE) {
      if (guess[1] > guess[0] && guess[1] > guess[2])
        ++correct;
    } else if (class[j * 3 + 2] == ONE) {
      if (guess[2] > guess[0] && guess[2] > guess[1])
        ++correct;
    } else {
      printf("Logic error.\n");
      return -1;
    }
  }

  printf("%d/%d correct\n", correct, samples);

  uint32_t cs1 = bench_checksum(ann->weight, ann->weight + ann->total_weights);
  uint32_t cs2 = bench_checksum(ann->output, ann->output + ann->total_neurons);
  uint32_t cs3 = bench_checksum(ann->delta, ann->delta + (ann->total_neurons - ann->inputs));
  int fail = (correct != ps->correct) || (cs1 != ps->cs1) || (cs2 != ps->cs2) || (cs3 != ps->cs3);
  if (fail)
    correct = -1;

  genann_free(ann);
  free(input);
  free(class);

  return correct;
}

static int iris_correct;

void bench_init(int setting) {
  printf("GENANN TEST SUITE\n");
  ps = &settings[setting];
  bench_srand(100); //Repeatable test results.
  ltests = 0;
  lfails = 0;
}

uint64_t bench_run() {
  lrun("basic", basic);
  lrun("xor", xor_);
  lrun("backprop", backprop);
  lrun("train and", train_and);
  lrun("train or", train_or);
  //lrun("train xor", train_xor);
  iris_correct = iris_test();
  return ps->ref_time;
}

int bench_validate() {
  lresults();
  return (lfails != 0) || (iris_correct == -1);
}
