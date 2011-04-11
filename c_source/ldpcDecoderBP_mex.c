#include <mex.h>
#include "ldpcDecoderBP.h"
#include "ldpcMatrixH.h"


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	short* matrixH;
    short  macroMatrixH[MACRO_MATRIX_M_SIZE][MACRO_MATRIX_N_SIZE] = MACRO_MATRIX;
	double* codeWord;
    double* infoWord;
	double var;
	int i;

	if (nrhs != 2)
		 mexErrMsgTxt("Two input arguments are required");
	if (nlhs != 1)
		 mexErrMsgTxt("One output argument is required");

	matrixH  = (short *)mxCalloc(BINARY_MATRIX_N_SIZE*BINARY_MATRIX_M_SIZE,sizeof(short));
    codeWord = (double *)mxCalloc(CODE_WORD_LEN,sizeof(double));
    infoWord = (double *)mxCalloc(INFO_WORD_LEN,sizeof(double));
	CreateBinaryMatrix(&macroMatrixH[0][0],matrixH);

	for(i = 0;i<CODE_WORD_LEN;i++)
        codeWord[i] = (double)*(mxGetPr(prhs[0])+ i);
	var = (double)*(mxGetPr(prhs[1]));
	
	DecodeCodeWordBP(codeWord,infoWord,matrixH,macroMatrixH,var);

	plhs[0] = mxCreateDoubleMatrix(INFO_WORD_LEN, 1, mxREAL);
	for (i = 0; i< INFO_WORD_LEN; i++)
         *(mxGetPr(plhs[0]) + i) = (double)infoWord[i];
	
	mxFree(matrixH);
    mxFree(codeWord);    
    mxFree(infoWord);
	return;
}