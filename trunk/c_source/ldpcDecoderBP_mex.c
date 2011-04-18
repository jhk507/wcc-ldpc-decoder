#include <mex.h>
#include "ldpcDecoderBP.h"
#include "ldpcMatrixH.h"


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	short* matrixH;
    short  macroMatrixH[MACRO_MATRIX_M_SIZE][MACRO_MATRIX_N_SIZE] = MACRO_MATRIX;
	double* codeFrame;
    double* infoFrame;
	double var = (double)*(mxGetPr(prhs[2]));
    short minSumAppr = (short)*(mxGetPr(prhs[3]));
    int frameLen = (int)*(mxGetPr(prhs[1]));
	int i, res;
    

	if (nrhs != 4)
		 mexErrMsgTxt("Four input arguments are required");
	if (nlhs != 1)
		 mexErrMsgTxt("One output argument is required");

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
        res = DecodeCodeWordBP(codeFrame + i*CODE_WORD_LEN,infoFrame + i*CODE_WORD_LEN,matrixH,&macroMatrixH[0][0],var,minSumAppr);
        printf("%d\t",res);
    }
    printf("\n");    

	plhs[0] = mxCreateDoubleMatrix(1, CODE_WORD_LEN * frameLen, mxREAL);
	for (i = 0; i< CODE_WORD_LEN * frameLen; i++)
    {
         *(mxGetPr(plhs[0]) + i) = (double)infoFrame[i];
    }
	
	mxFree(matrixH);
    mxFree(codeFrame);    
    mxFree(infoFrame);
	return;
}