#ifndef __LDPC_MATRIX_CONSTRUCTOR_H__
#define __LDPC_MATRIX_CONSTRUCTOR_H__

#include "ldpcMatrixH.h"
#include <stdio.h>

void CreateBinaryMatrix(short *inMacroMatrix, short *outBinaryMatrix);

void PrintMatrix(short *matrix, int rowCount, int colCount);
void PrintMatrixToHFile(short *matrix, int rowCount, int colCount, FILE *outputFile);
void PrintMatrixToFile(short *matrix, int rowCount, int colCount, FILE *outputFile);

#endif /*__LDPC_MATRIX_CONSTRUCTOR_H__*/
