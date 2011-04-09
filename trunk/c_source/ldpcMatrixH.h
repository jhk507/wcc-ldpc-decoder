#ifndef __LDPC_MATRIX_H__
#define __LDPC_MATRIX_H__

#define MACRO_MATRIX_N_SIZE	16
#define MACRO_MATRIX_M_SIZE	8
#define MICRO_IDENTITY_MATRIX_SIZE		42
#define BINARY_MATRIX_N_SIZE	672
#define BINARY_MATRIX_M_SIZE	336

#define CODE_RATE 	 1/2 
#define CODE_WORD_LEN 	 672 
#define INFO_WORD_LEN 	 CODE_WORD_LEN*CODE_RATE

#define L_MAX	7

#define MACRO_MATRIX {{40, -1, 38, -1, 13, -1,  5, -1, 18, -1, -1, -1, -1, -1, -1, -1}, \
					  {34, -1, 35, -1, 27, -1, -1, 30,  2,  1, -1, -1, -1, -1, -1, -1}, \
					  {-1, 36, -1, 31, -1,  7, -1, 34, -1, 10, 41, -1, -1, -1, -1, -1}, \
					  {-1, 27, -1, 18, -1, 12, 20, -1, -1, -1, 15,  6, -1, -1, -1, -1}, \
					  {35, -1, 41, -1, 40, -1, 39, -1, 28, -1, -1,  3, 28, -1, -1, -1}, \
					  {29, -1,  0, -1, -1, 22, -1,  4, -1, 28, -1, -1, 24, 23, -1, -1}, \
					  {-1, 31, -1, 23, -1, 21, -1, 20, -1, -1, 12, -1, -1,  0, 13, -1}, \
					  {-1, 22, -1, 34, 31, -1, 14, -1, -1, -1, -1, 18, -1, -1, 22, 24}}

#endif /*__LDPC_MATRIX_H__*/