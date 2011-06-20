#include <mex.h>
#include "ldpcDecoderBP.h"
#include "ldpcMatrixH.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	//short matrixH[BINARY_MATRIX_M_SIZE][BINARY_MATRIX_N_SIZE] = BINARY_H_MATRIX;
    short* matrixH;
    short  macroMatrixH[MACRO_MATRIX_M_SIZE][MACRO_MATRIX_N_SIZE] = MACRO_MATRIX;
	double* codeFrame;
    double* infoFrame;
    short* matrixHn;
    short* matrixHm;
	double var;
    short minSumAppr;
    int frameLen;
	int i, j, res;
    int iterCount;
    FILE *binMatrix = fopen("binMatrixH.txt","w");

	if (nrhs < 3)
		 mexErrMsgTxt("Four input arguments are required");
	if (nlhs < 1)
		 mexErrMsgTxt("One or Two output arguments are required");

    frameLen = (int)(mxGetScalar(prhs[1]));
    minSumAppr = (short)(mxGetScalar(prhs[2]));
    
 	matrixHm = (short *)mxCalloc(BINARY_MATRIX_N_SIZE*5,sizeof(short));
    matrixHn = (short *)mxCalloc(BINARY_MATRIX_M_SIZE*8,sizeof(short));
    matrixH  = (short *)mxCalloc(BINARY_MATRIX_N_SIZE*BINARY_MATRIX_M_SIZE,sizeof(short));
    codeFrame = (double *)mxCalloc(CODE_WORD_LEN * frameLen,sizeof(double));
    infoFrame = (double *)mxCalloc(CODE_WORD_LEN * frameLen,sizeof(double));
	CreateBinaryMatrix(&macroMatrixH[0][0],matrixH);

	for(i = 0;i<CODE_WORD_LEN * frameLen;i++)
    {
        codeFrame[i] = (double)*(mxGetPr(prhs[0])+ i);
    }
    
	for (i = 0; i<frameLen; i++)
    {
        res = DecodeCodeWordBP(codeFrame + i*CODE_WORD_LEN,infoFrame + i*CODE_WORD_LEN,matrixH,&macroMatrixH[0][0],&iterCount,minSumAppr,matrixHn,matrixHm);
        printf("%d\t",res);
    }
    printf("\n");    

	plhs[0] = mxCreateDoubleMatrix(1, CODE_WORD_LEN * frameLen, mxREAL);
	for (i = 0; i< CODE_WORD_LEN * frameLen; i++)
    {
         *(mxGetPr(plhs[0]) + i) = (double)infoFrame[i];
    }
    plhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
    *(mxGetPr(plhs[1])) = iterCount;
    plhs[2] = mxCreateDoubleMatrix(8,336,mxREAL);
    plhs[3] = mxCreateDoubleMatrix (672,5,mxREAL);
    for (i = 0; i< 336; i++)
        for(j = 0; j < 8; j++)
        *(mxGetPr(plhs[2]) + 8*i + j) = *(matrixHn + 8*i + j);
    
     for (i = 0; i< 5; i++)
        for(j = 0; j < 672; j++)
        *(mxGetPr(plhs[3]) + 672*i + j) = *(matrixHm + 672*i + j);  
	
 	mxFree(matrixHn);
    mxFree(matrixHm);
    mxFree(matrixH);
    mxFree(codeFrame);    
    mxFree(infoFrame);
	return;
}