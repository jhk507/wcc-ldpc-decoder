#ifndef __LDPC_DECODER_BP_H__
#define __LDPC_DECODER_BP_H__

#include "ldpcMatrixConstructor.h"
#include <math.h>

void DecodeCodeWordBP(float *inCodeWord, float *outCodeWord, short* binaryMatrixH, short* macroMatrix);

#endif /*__LDPC_DECODER_BP_H__*/