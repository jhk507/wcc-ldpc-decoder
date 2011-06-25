#ifndef __LDPC_ENCODER_H__
#define __LDPC_ENCODER_H__

#include <stdio.h>

int CheckCodeWord(short *codeWord, short *MatrixH, int matrixSizeM, int matrixSizeN);
void EncodeInfoWord(short *inInfoWord, short *outCodeWord, short *MatrixH, int codeWordLen, double codeRate);

#endif /*__LDPC_ENCODER_H__*/