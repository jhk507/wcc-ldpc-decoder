#include "mex.h"
//#include "ldpcEncoder.h"
#include "ldpcMatrixH.h"
#include <math.h>
#include <stdio.h>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	short* matrixH;
    short  macroMatrixH[MACRO_MATRIX_M_SIZE][MACRO_MATRIX_N_SIZE] = MACRO_MATRIX;
    short* codeWord;
    short* infoWord;
    int i;
    
	if (nrhs != 1)
		 mexErrMsgTxt("One input arguments are required");
	if (nlhs != 1)
		 mexErrMsgTxt("One output arguments are required");
    
    matrixH  = (short *)mxCalloc(BINARY_MATRIX_N_SIZE*BINARY_MATRIX_M_SIZE,sizeof(short));
    codeWord = (short *)mxCalloc(CODE_WORD_LEN,sizeof(short));
    infoWord = (short *)mxCalloc(INFO_WORD_LEN,sizeof(short));
    
    CreateBinaryMatrix(&macroMatrixH[0][0],matrixH);
    for(i = 0;i<INFO_WORD_LEN;i++)
        infoWord[i] = (short)*(mxGetPr(prhs[0])+ i);
    
    EncodeInfoWord(infoWord,codeWord, matrixH);	
    plhs[0] = mxCreateDoubleMatrix(CODE_WORD_LEN, 1, mxREAL);
    for (i = 0; i< CODE_WORD_LEN; i++)
         *(mxGetPr(plhs[0]) + i) = (double)codeWord[i];
    
    mxFree(matrixH);
    mxFree(codeWord);    
    mxFree(infoWord);
    
    return;
}