#include "ldpcEncoder.h"

int CheckCodeWord(short *codeWord, short *MatrixH)
{
	int i,j;
	short sum;
	for(i = 0;i<BINARY_MATRIX_M_SIZE;i++)
	{	sum = 0;
		for (j = 0;j<BINARY_MATRIX_N_SIZE;j++)
			sum = (sum + *(codeWord + j)* *(MatrixH + i*BINARY_MATRIX_N_SIZE + j))%2;
		if (sum)
			return -1;
	}
	return 0;			
}

void EncodeInfoWord(short *inInfoWord, short *outCodeWord, short *MatrixH)
{
	int i,j;
	short p;
	for (i = 0; i<INFO_WORD_LEN; i++)
		*(outCodeWord + i) = *(inInfoWord + i);
	for (i = INFO_WORD_LEN; i<CODE_WORD_LEN;i++)
	{
		p = 0;
		for(j = 0; j<i;j++)
			if(*(MatrixH + (i-INFO_WORD_LEN)*BINARY_MATRIX_N_SIZE + j))
				p = (p + *(outCodeWord + j) * *(MatrixH + (i-INFO_WORD_LEN)*BINARY_MATRIX_N_SIZE + j))%2;
		*(outCodeWord + i) = p;
	}
}
