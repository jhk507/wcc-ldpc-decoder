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
			sind = (sind + (*(codeWord + *(matrixHn+ i*matrixNSize + j) ) > 0) )%2;
			j++;
		}
		if (sind)
			return -1;
	}
	return 0;	
}

int DecodeCodeWordBP(double *inCodeWord, double *outCodeWord, short* binaryMatrixH, short* macroMatrix, int* iterCount, short minSumApprox)
{
	double *lamb		= (double *)malloc(BINARY_MATRIX_N_SIZE*sizeof(double));
	double *lambPrevIt	= (double *)malloc(BINARY_MATRIX_N_SIZE*sizeof(double));
	double *Umn			= (double *)malloc(BINARY_MATRIX_M_SIZE*BINARY_MATRIX_N_SIZE*sizeof(double));
	double *UmnPrevIt	= (double *)malloc(BINARY_MATRIX_M_SIZE*BINARY_MATRIX_N_SIZE*sizeof(double));
	short *newBinaryMatrixHm = NULL;
	short *newBinaryMatrixHn = NULL;
	int newMSize = 0;	
	int newNSize = 0;	
	int i,j,m,n,k,signUl,iii;
	int	iterL, checkRes;
	double	Ul;
//	FILE *fHm = fopen("matrixHm.txt","w");
//	FILE *fHn = fopen("matrixHn.txt","w");

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
	
//	PrintMatrixToFile(newBinaryMatrixHn,BINARY_MATRIX_M_SIZE,newNSize,fHn);
//	fclose(fHn);

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
//	PrintMatrixToFile(newBinaryMatrixHm,newMSize,BINARY_MATRIX_N_SIZE,fHm);
//	fclose(fHm);	

	//initialization
	for (i = 0;i<BINARY_MATRIX_N_SIZE;i++)
	{
 		*(lamb + i) = 0;
		*(lambPrevIt + i) = *(inCodeWord + i);
		for(j = 0;j<BINARY_MATRIX_M_SIZE;j++)
			//if (*(binaryMatrixH + j*BINARY_MATRIX_N_SIZE + i))
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
		*(lamb + n) = *(inCodeWord + n);

		while(m >= 0)
		{
			j = *(newBinaryMatrixHn + newNSize*m);
			k = 0;

			if (minSumApprox)
			{
				Ul = 1.79769313486231579E+308;
				signUl = 0;
			}
			else
				Ul = 1.0;
			while (j >= 0)
			{
				if (j != n)
					{
						if(minSumApprox)
						{
							if ((*(UmnPrevIt + m*BINARY_MATRIX_N_SIZE + j) - *(lambPrevIt + j))/2 > 0 )
								signUl++;
							if(fabs(Ul) > fabs ( (*(UmnPrevIt + m*BINARY_MATRIX_N_SIZE + j) - *(lambPrevIt + j) )/2 ) )
								Ul = fabs( (*(UmnPrevIt + m*BINARY_MATRIX_N_SIZE + j) - *(lambPrevIt + j) )/2 );
						}
						else
							Ul = Ul*tanh( *(UmnPrevIt + m*BINARY_MATRIX_N_SIZE + j)/2 - *(lambPrevIt + j)/2 );
					}
				k++;
				j = *(newBinaryMatrixHn + newNSize*m + k);
			}	// while (j >= 0)
			if (minSumApprox)
			{
				if (signUl%2)
					Ul = -Ul;
			}
			else
			{
				Ul = -2*ATANH(Ul);
			}
			*(Umn + m*BINARY_MATRIX_N_SIZE + n) = Ul;
			*(lamb + n) = *(lamb + n) + Ul;
			i++;
			m = *(newBinaryMatrixHm + i*BINARY_MATRIX_N_SIZE + n);
		}	//while(m >= 0)
	}

	for(j = 0; j<BINARY_MATRIX_N_SIZE;j++)
	{
		*(lambPrevIt + j) = *(lamb + j);
		for (i = 0; i<BINARY_MATRIX_M_SIZE;i++)
			if (*(binaryMatrixH + i*BINARY_MATRIX_N_SIZE + j))
			*(UmnPrevIt + i*BINARY_MATRIX_N_SIZE + j) = *(Umn + i*BINARY_MATRIX_N_SIZE + j);
	}

	checkRes = CheckCodeSindrom(lamb,newBinaryMatrixHn,newNSize);
	iterL++;
	if (checkRes == 0)
		break;
	}
	
	for (i = 0; i<CODE_WORD_LEN; i++)
		*(outCodeWord + i) = *(lamb + i);
	*iterCount = iterL;

	free(lamb);
	free(lambPrevIt);
	free(Umn);
	free(UmnPrevIt);
	free(newBinaryMatrixHm);
	free(newBinaryMatrixHn);

	return checkRes;
}

void HardDecisionCodeWord(double *llrWord, short *codeWord)
{
	int i;
	for (i = 0; i<CODE_WORD_LEN; i++)
		*(codeWord + i) = (short)(*(llrWord + i) > 0 );
}