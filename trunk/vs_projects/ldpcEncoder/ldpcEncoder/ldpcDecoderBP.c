#include "ldpcDecoderBP.h"

void DetMaxNewMatrixDim(short* macroMatrix, int* maxM, int* maxN)
{
	int i,j;
	int tmp_val;
	*maxM = 0;
	*maxN = 0;
	for (i = 0; i<MACRO_MATRIX_N_SIZE; i++)
	{	tmp_val = 0;
		for (j = 0; j<MACRO_MATRIX_M_SIZE;j++)
			if(*(macroMatrix + j*MACRO_MATRIX_N_SIZE + i) != -1) 
				tmp_val++;
		if (tmp_val > *maxM)
			*maxM = tmp_val;
	}

	for (i = 0; i<MACRO_MATRIX_M_SIZE; i++)
	{	tmp_val = 0;
		for (j = 0; j<MACRO_MATRIX_N_SIZE;j++)
			if(*(macroMatrix + i*MACRO_MATRIX_N_SIZE + j) != -1) 
				tmp_val++;
		if (tmp_val > *maxN)
			*maxN = tmp_val;
	}
}

int CheckCodeSindrom(short* codeWord, short* matrixHn, short matrixNSize)
{
	int i,j;
	short sind;
	for(i = 0; i< BINARY_MATRIX_M_SIZE; i++)
	{
		j = 0;
		sind = 0;
		while(*(matrixHn+ i*matrixNSize + j) != -1)
		{
			sind = (sind + *(codeWord + *(matrixHn+ i*matrixNSize + j)))%2;
			j++;
		}
		if (sind)
			return -1;
	}
	return 0;	
}

int DecodeCodeWordBP(double *inCodeWord, double *outCodeWord, short* binaryMatrixH, short* macroMatrix, double SNR, short minSumApprox)
{
	double *lamb		= (double *)malloc(BINARY_MATRIX_N_SIZE*sizeof(double));
	double *lambPrevIt	= (double *)malloc(BINARY_MATRIX_N_SIZE*sizeof(double));
	double *Umn			= (double *)malloc(BINARY_MATRIX_M_SIZE*BINARY_MATRIX_N_SIZE*sizeof(double));
	double *UmnPrevIt	= (double *)malloc(BINARY_MATRIX_M_SIZE*BINARY_MATRIX_N_SIZE*sizeof(double));
	short *newBinaryMatrixHm = NULL;
	short *newBinaryMatrixHn = NULL;
	int newMSize = 0;	
	int newNSize = 0;	
	int i,j,m,n,k;
	int	iterL, checkRes;
	double	Ul;

	DetMaxNewMatrixDim(macroMatrix,&newMSize,&newNSize);
	newMSize++;
	newNSize++;
	newBinaryMatrixHm = (short *)malloc(BINARY_MATRIX_N_SIZE*newMSize*sizeof(short));
	newBinaryMatrixHn = (short *)malloc(BINARY_MATRIX_M_SIZE*newNSize*sizeof(short));

	for (i = 0; i<BINARY_MATRIX_M_SIZE;i++)
	{
		n = 0;
		for(j = 0; j<BINARY_MATRIX_N_SIZE;j++)
			if(*(binaryMatrixH + i*BINARY_MATRIX_N_SIZE + j))
			{
				*(newBinaryMatrixHn + i*newNSize + n) = j;
				n++;
			}
		*(newBinaryMatrixHn + i*newNSize + n) = -1;
	}
	for (j = 0; j<BINARY_MATRIX_N_SIZE;j++)
	{
		m = 0;
		for(i = 0; i<BINARY_MATRIX_M_SIZE;i++)
			if(*(binaryMatrixH + i*BINARY_MATRIX_N_SIZE + j))
			{
				*(newBinaryMatrixHm + m*BINARY_MATRIX_N_SIZE + j) = i;
				m++;
			}
		*(newBinaryMatrixHm + m*BINARY_MATRIX_N_SIZE + j) = -1;
	}
	
	//initialization
	for (i = 0;i<BINARY_MATRIX_N_SIZE;i++)
	{
		*(lamb + i) = *(inCodeWord + i);
		*(lambPrevIt + i) = 0;
		for(j = 0;j<BINARY_MATRIX_M_SIZE;j++)
		{
		*(Umn + j*BINARY_MATRIX_N_SIZE + i) = 0;
		*(UmnPrevIt + j*BINARY_MATRIX_N_SIZE + i) = 0;
		}
	}

	//iterate
	iterL = 0;

	while(iterL < L_MAX)
	{
	for (n = 0; n<BINARY_MATRIX_N_SIZE; n++)
	{
		m = *(newBinaryMatrixHm + n);
		i = 0;
		*(lambPrevIt + n) = *(lamb + n);
		*(lamb + n) = *(inCodeWord + n);

		while(m >= 0)
		{
			j = *(newBinaryMatrixHn + newNSize*m);
			k = 0;
			Ul = 1;
			while (j >= 0)
			{
				if (j != n)
					{
						Ul = Ul*tanh( (*(UmnPrevIt + m*BINARY_MATRIX_N_SIZE + j) + *(lambPrevIt + j))/2 );
					}
				k++;
				j = *(newBinaryMatrixHn + newNSize*m + k);
			}
			Ul = -2*ATANH(Ul);
			*(UmnPrevIt + m*BINARY_MATRIX_N_SIZE + n) = *(Umn + m*BINARY_MATRIX_N_SIZE + n);
			*(Umn + m*BINARY_MATRIX_N_SIZE + n) = Ul;
			*(lamb + n) = *(lamb + n) + Ul;
			i++;
			m = *(newBinaryMatrixHm + i*BINARY_MATRIX_N_SIZE + n);
		}
	}

	checkRes = CheckCodeSindrom(inCodeWord,newBinaryMatrixHn,newNSize);
	if (checkRes == 0)
		break;

	iterL++;
	}
	
	for (i = 0; i<INFO_WORD_LEN; i++)
		*(outCodeWord + i) = *(lamb + i);

	free(lamb);
	free(lambPrevIt);
	free(Umn);
	free(UmnPrevIt);
	free(newBinaryMatrixHm);
	free(newBinaryMatrixHn);

	if (checkRes == 0)
		return 0;
	else
		return -1;
}