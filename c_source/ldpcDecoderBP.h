#ifndef __LDPC_DECODER_BP_H__
#define __LDPC_DECODER_BP_H__

#include "ldpcMatrixConstructor.h"
#include <math.h>
#include <malloc.h>
#include <float.h>


#define ATANH(z)	(0.5*log((1.+z)/(1.-z)))

int DecodeCodeWordBP(double *inCodeWord, double *outCodeWord, short* binaryMatrixH, short* macroMatrix, int* iterCount, short minSumApprox);
void HardDecisionCodeWord(double *llrWord, short *codeWord);

#endif /*__LDPC_DECODER_BP_H__*/