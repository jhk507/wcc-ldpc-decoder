#ifndef __LDPC_ENCODER_H__
#define __LDPC_ENCODER_H__


#include <stdio.h>
#include "ldpcMatrixConstructor.h"

void EncodeInfoWord(short *inInfoWord, short *outCodeWord, short *MatrixH);

#endif /*__LDPC_ENCODER_H__*/