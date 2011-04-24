#include <mex.h>
#include "ldpcEncoder.h"
#include "ldpcMatrixH.h"
#include "matrix.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	short* matrixH;
    short  macroMatrixH[MACRO_MATRIX_M_SIZE][MACRO_MATRIX_N_SIZE] = MACRO_MATRIX;
    short* codeFrame;
    short* infoFrame;
    int i;
    int frameLen;
    
	if (nrhs != 2)
		 mexErrMsgTxt("Two input arguments are required");
	if (nlhs != 1)
		 mexErrMsgTxt("One output argument is required");
    
    frameLen = (int)(mxGetScalar(prhs[1]));
    
    matrixH  = (short *)mxCalloc(BINARY_MATRIX_N_SIZE*BINARY_MATRIX_M_SIZE,sizeof(short));
    codeFrame = (short *)mxCalloc(CODE_WORD_LEN * frameLen,sizeof(short));
    infoFrame = (short *)mxCalloc(INFO_WORD_LEN * frameLen,sizeof(short));
            
    CreateBinaryMatrix(&macroMatrixH[0][0],matrixH);
    for(i = 0;i<INFO_WORD_LEN * frameLen;i++)
        infoFrame[i] = (short)*(mxGetPr(prhs[0])+ i);
    
     for(i = 0; i<frameLen;i++)
     {
             EncodeInfoWord(infoFrame + i*INFO_WORD_LEN,codeFrame + i*CODE_WORD_LEN, matrixH);	
             printf("%d\t",CheckCodeWord(codeFrame + i*CODE_WORD_LEN,matrixH));
     }
    printf("\n");
     
    plhs[0] = mxCreateDoubleMatrix(1, CODE_WORD_LEN * frameLen, mxREAL);
    for (i = 0; i< CODE_WORD_LEN * frameLen; i++)
         *(mxGetPr(plhs[0]) + i) = (double)codeFrame[i];
    
    mxFree(matrixH);
    mxFree(codeFrame);    
    mxFree(infoFrame);
    
    return;
}