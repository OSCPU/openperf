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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

  for (i = 0; i < 50; ++i) {
    for (j = 0; j < 4; ++j) {
      genann_train(ann, input[j], output + j, SCALE_UP(.8));
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

  for (i = 0; i < 50; ++i) {
    for (j = 0; j < 4; ++j) {
      genann_train(ann, input[j], output + j, SCALE_UP(.8));
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

  for (i = 0; i < 500; ++i) {
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

int main(int argc, char *argv[]) {
  printf("GENANN TEST SUITE\n");

  srand(100); //Repeatable test results.

  lrun("basic", basic);
  lrun("xor", xor_);
  lrun("backprop", backprop);
  lrun("train and", train_and);
  lrun("train or", train_or);
  lrun("train xor", train_xor);

  lresults();

  return lfails != 0;
}
