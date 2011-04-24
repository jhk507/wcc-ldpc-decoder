#include <mex.h>
#include "ldpcDecoderBP.h"
#include "ldpcMatrixH.h"
#include "matrix.h"


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	short* matrixH;
    short  macroMatrixH[MACRO_MATRIX_M_SIZE][MACRO_MATRIX_N_SIZE] = MACRO_MATRIX;
	double* codeFrame;
    double* infoFrame;
	double var;
    short minSumAppr;
    int frameLen;
	int i, res;
    int iterCount;
    

	if (nrhs != 3)
		 mexErrMsgTxt("Four input arguments are required");
	if (nlhs < 1)
		 mexErrMsgTxt("One or Two output arguments are required");

    frameLen = (int)(mxGetScalar(prhs[1]));
    minSumAppr = (short)(mxGetScalar(prhs[2]));
    
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
        res = DecodeCodeWordBP(codeFrame + i*CODE_WORD_LEN,infoFrame + i*CODE_WORD_LEN,matrixH,&macroMatrixH[0][0],&iterCount,minSumAppr);
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
	
	mxFree(matrixH);
    mxFree(codeFrame);    
    mxFree(infoFrame);
	return;
}