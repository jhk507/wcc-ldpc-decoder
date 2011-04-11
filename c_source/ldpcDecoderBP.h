#ifndef __LDPC_DECODER_BP_H__
#define __LDPC_DECODER_BP_H__

#include "ldpcMatrixConstructor.h"
#include <math.h>

void DecodeCodeWordBP(double *inCodeWord, double *outCodeWord, short* binaryMatrixH, short* macroMatrix, double SNR);

#endif /*__LDPC_DECODER_BP_H__*/