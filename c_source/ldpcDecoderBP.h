#ifndef __LDPC_DECODER_BP_H__
#define __LDPC_DECODER_BP_H__

#include <math.h>
#include <malloc.h>
#include <float.h>


#define ATANH(z)	0.5*(log((1.0+z)/(1.0-z)))

int DecodeCodeWordBP(double *inCodeWord, short *outCodeWord, short* binaryMatrixH, int binMatrixSizeM, int binMatrixSizeN, \
					 short* macroMatrix, int macroMatrixSizeM, int macroMatrixSizeN, \
					 short* matrixHn, int matrixHnSizeN, short* matrixHm, int matrixHmSizeM,\
					 int maxIterCount, short minSumApprox, int* iterCount);

void HardDecisionCodeWord(double *llrWord, short *codeWord, int codeWordLen);

#endif /*__LDPC_DECODER_BP_H__*/