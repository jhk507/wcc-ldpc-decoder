#include "ldpcEncoder.h"

int CheckCodeWord(short *codeWord, short *MatrixH, int matrixSizeM, int matrixSizeN)
{
	int i,j;
	short sum;
	for(i = 0;i<matrixSizeM;i++)
	{	sum = 0;
		for (j = 0;j<matrixSizeN;j++)
			sum = (sum + *(codeWord + j)* *(MatrixH + i*matrixSizeN + j))%2;
		if (sum)
			return -1;
	}
	return 0;			
}

void EncodeInfoWord(short *inInfoWord, short *outCodeWord, short *MatrixH, int codeWordLen, double codeRate)
{
	int i,j;
	short p;
	int infoWordLen = codeWordLen*codeRate;
	int binMatrixSizeN = codeWordLen; 						//!!!!!!!!!!!!!!!!!
	for (i = 0; i<infoWordLen; i++)
		*(outCodeWord + i) = *(inInfoWord + i);
	for (i = infoWordLen; i<codeWordLen;i++)
	{
		p = 0;
		for(j = 0; j<i;j++)
			if(*(MatrixH + (i-infoWordLen)*binMatrixSizeN  + j))
				p = (p + *(outCodeWord + j) * *(MatrixH + (i-infoWordLen)*binMatrixSizeN  + j))%2;
		*(outCodeWord + i) = p;
	}
}
