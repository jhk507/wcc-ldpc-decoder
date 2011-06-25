#include "ldpcDecoderBP.h"

int CheckCodeSindrom(double* codeWord, short binMatrixSizeM, short* matrixHn, short matrixHnSizeN)
{
	int i,j;
	short sind;
	for(i = 0; i< binMatrixSizeM; i++)
	{
		j = 0;
		sind = 0;
		while(*(matrixHn+ i*matrixHnSizeN + j) != -1)
		{
			sind = (sind + (*(codeWord + *(matrixHn+ i*matrixHnSizeN + j) ) > 0) )%2;
			j++;
		}
		if (sind)
			return 0;
	}
	return 1;	
}

void HardDecisionCodeWord(double *llrWord, short *codeWord, int codeWordLen)
{
	int i;
	for (i = 0; i<codeWordLen; i++)
		*(codeWord + i) = (short)(*(llrWord + i) > 0 );
}

int DecodeCodeWordBP(double *inCodeWord, short *outCodeWord, short* binaryMatrixH, int binMatrixSizeM, int binMatrixSizeN, \
					 short* macroMatrix, int macroMatrixSizeM, int macroMatrixSizeN, \
					 short* matrixHn, int matrixHnSizeN, short* matrixHm, int matrixHmSizeM,\
					 int maxIterCount, short minSumApprox, int* iterCount)
{
	double *lamb		= (double *)malloc(binMatrixSizeN*sizeof(double));
	double *lambPrevIt	= (double *)malloc(binMatrixSizeN*sizeof(double));
	double *Umn			= (double *)malloc(binMatrixSizeM*binMatrixSizeN*sizeof(double));
	double *UmnPrevIt	= (double *)malloc(binMatrixSizeM*binMatrixSizeN*sizeof(double));
	int i,j,m,n,k,signUl,iii;
	int	iterL, checkRes;
	double	Ul;
	int		codeWordLen = binMatrixSizeN;

	//initialization
	for (i = 0;i<binMatrixSizeN;i++)
	{
 		*(lamb + i) = 0;
		*(lambPrevIt + i) = *(inCodeWord + i);
		for(j = 0;j<binMatrixSizeM;j++)
			{
				*(Umn + j*binMatrixSizeN + i) = 0;
				*(UmnPrevIt + j*binMatrixSizeN + i) = 0;
			}
	}

	//iterate
	iterL = 0;
	while(iterL < maxIterCount)
	{ 
	for (n = 0; n<binMatrixSizeN; n++)
	{
		m = *(matrixHm + n);
		i = 0;
		*(lamb + n) = *(inCodeWord + n);

		while(m >= 0)
		{
			j = *(matrixHn + matrixHnSizeN*m);
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
							if ( (*(UmnPrevIt + m*binMatrixSizeN + j)- *(lambPrevIt + j) ) < 0 )
								signUl++;
							if(fabs(Ul) > fabs ( *(UmnPrevIt + m*binMatrixSizeN + j)- *(lambPrevIt + j)) )
								Ul = fabs ( *(UmnPrevIt + m*binMatrixSizeN + j)- *(lambPrevIt + j) );
						}
						else
							Ul = Ul*tanh(*(UmnPrevIt + m*binMatrixSizeN + j)*0.5 - *(lambPrevIt + j)*0.5 );
					}
				k++;
				j = *(matrixHn + matrixHnSizeN*m + k);
			}	// while (j >= 0)
			if (minSumApprox)
			{
				if (signUl%2 == 0)
					Ul = -Ul;
			}
			else
			{
				Ul = -2*ATANH(Ul);
			}
			*(Umn + m*binMatrixSizeN + n) = Ul;
			*(lamb + n) = *(lamb + n) + Ul;
			i++;
			m = *(matrixHm + i*binMatrixSizeN + n);
		}	//while(m >= 0)
	}

	for(j = 0; j<binMatrixSizeN;j++)
	{
		*(lambPrevIt + j) = *(lamb + j);
		for (i = 0; i<binMatrixSizeM;i++)
			if (*(binaryMatrixH + i*binMatrixSizeN + j))
			*(UmnPrevIt + i*binMatrixSizeN + j) = *(Umn + i*binMatrixSizeN + j);
	}

	checkRes = CheckCodeSindrom(lamb,binMatrixSizeM,matrixHn,matrixHnSizeN);
	iterL++;
	if (checkRes == 1)
		break;
	}
	
	*iterCount = iterL;
	HardDecisionCodeWord(lamb,outCodeWord,codeWordLen);

	free(lamb);
	free(lambPrevIt);
	free(Umn);
	free(UmnPrevIt);

	return checkRes;
}