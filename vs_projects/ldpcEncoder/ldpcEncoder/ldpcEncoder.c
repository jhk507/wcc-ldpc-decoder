#include "ldpcEncoder.h"

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
