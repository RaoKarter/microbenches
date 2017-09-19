#ifndef __THREADS_H__
#define __THREADS_H__

#include <stdio.h>
#include <stdlib.h>
#include <qsim_magic.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <stdint.h>

#include <omp.h>

#define NUM_ITER1 5
#define L2BANKMUL 256
#define L1MUL 1365
#define MEM_FETCH_INTERVAL ( (L2BANKMUL/4) - 1 )
#define VAR_SIZE (L1MUL*16)

#define PAGE_SIZE 4096				// 4KB
#define NUM_MEM_FETCHES 10			// Parameter to keep num of mem ops fixed
#define NUM_CPU_OPS 10				// Parameter to increase MIPS

#define DOUBLE_ELE_SIZE 8			// 8B
#define DB_2_MB 262144				// length of a double sized array. sizeof(double_arr1[262144]) = 2MB
#define STR_ELE_SIZE 16				// 16B
#define STR_2_MB 131072				// length of s_16B array. sizeof(s_16B_arr1[131072]) = 2MB

#define NUM_ELE_IN_PAGE (PAGE_SIZE/STR_ELE_SIZE)	// Number of elements of particular type in a 4KB page
													// For a double sized array NUM_ELE_IN_PAGE = 512
													// For a struct s_16B sized array NUM_ELE_IN_PAGE = 256

/*
Core mapping
0  ->  2
1  ->  3
2  ->  4
...
12 ->  14
13 ->  15
14 ->  0
15 ->  1
*/ 
#define CORE_NUMBER 0
/*
L2 Bank mapping
0  ->  13
1  ->  14
2  ->  15
3  ->  0
...
15 ->  12
*/
#define L2BANKID 6

struct s_var {
int var1[VAR_SIZE + 1];				// 5464B should be brought into L1
double var2[VAR_SIZE];				// 10920KB should be brought into L1
};									// 5464 + 10920 = 16384B = 16KB


struct s_16B {
int int_var1, int_var2;
double double_var3;
};

#endif /* __THREADS_H__ */

