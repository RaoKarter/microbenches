#ifndef __THREADS_H__
#define __THREADS_H__

#include <stdio.h>
#include <stdlib.h>
#include <qsim_magic.h>
#include <iostream>
#include <math.h>
#include <vector>

#include <omp.h>

#define NUM_ITER1 5
#define L2BANKMUL 128
#define L1MUL 1365

struct s_var {
int var1[L1MUL + 1];			// 5464B
double var2[L1MUL];				// 10920KB
};								// 5464 + 10920 = 16384B = 16KB

#endif /* __THREADS_H__ */

