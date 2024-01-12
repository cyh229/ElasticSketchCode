#ifndef _PARAM_H_
#define _PARAM_H_

#include "../common/BOBHash32.h"

#include <x86intrin.h>
#include <string.h>
#include <stdint.h>
#include <random>
#include <string>
#include <memory>
#include <iostream>
#include <cmath>
#include <math.h>

#define COUNTER_PER_BUCKET 8
#define MAX_VALID_COUNTER 7 // counters[7] stores vote-

#define ALIGNMENT 64

#define COUNTER_PER_WORD 8
#define BIT_TO_DETERMINE_COUNTER 3
#define K_HASH_WORD 1


#define KEY_LENGTH_4 4 // fp fingerprint
#define KEY_LENGTH_13 13 // IP 5-tuple

#define CONSTANT_NUMBER 2654435761u
#define CalculateBucketPos(fp) (((fp) * CONSTANT_NUMBER) >> 15)

#define GetCounterVal(val) ((uint32_t)((val) & 0x7FFFFFFF))

#define JUDGE_IF_SWAP(min_val, guard_val) ((guard_val) > ((min_val) << 3)) // << 3 : \lambda = 8

#define UPDATE_GUARD_VAL(guard_val) ((guard_val) + 1) // ? why not add f?

#define SWAP_MIN_VAL_THRESHOLD 5

#define HIGHEST_BIT_IS_1(val) ((val) & 0x80000000) // highest bit means flags : need to add lignt part, and low 31bits means vote+



struct Bucket
{
	uint32_t key[COUNTER_PER_BUCKET];
	uint32_t val[COUNTER_PER_BUCKET];
};


#endif