#include <mex.h>
#include "ldpcEncoder.h"
#include "matrix.h"
#include "matrixH_1_2.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	short* matrixH;
    short* macroMatrixH;
    short* codeFrame;
    short* infoFrame;
    int i;
    int frameLen;
	double codeRate;
	int infoWordLen;
    int res;
    
	if (nrhs != 3)
		 mexErrMsgTxt("Two input arguments are required: InfoWord, FrameLen, CodeRate");
	if (nlhs != 1)
		 mexErrMsgTxt("One output argument is required: CodeWorde");
    
    frameLen = (int)(mxGetScalar(prhs[1]));
	codeRate = (double)(mxGetScalar(prhs[2]));
	
	infoWordLen = codeWordLen*codeRate;
	
	if (codeRate == 0.5)
	{ 
		matrixH  = &encodeBinaryMatrixH_1_2;
		macroMatrixH = &macroMatrixH_1_2; 
	}
	else
	{	
		mexErrMsgTxt("Unknown CodeRate");
	}
	
    codeFrame = (short *)mxCalloc(codeWordLen * frameLen,sizeof(short));
	infoFrame = (short *)mxCalloc(infoWordLen * frameLen,sizeof(short));
	for(i = 0;i<infoWordLen * frameLen;i++)
        infoFrame[i] = (short)*(mxGetPr(prhs[0])+ i);
    
     for(i = 0; i<frameLen;i++)
     {
             EncodeInfoWord(infoFrame + i*infoWordLen,codeFrame + i*codeWordLen, matrixH, codeWordLen, codeRate);	
             //res = CheckCodeWord(codeFrame + i*codeWordLen, matrixH, binaryMatrixH_1_2_SizeM, binaryMatrixH_1_2_SizeN);
     }
     
    plhs[0] = mxCreateDoubleMatrix(1, codeWordLen * frameLen, mxREAL);
    for (i = 0; i< codeWordLen * frameLen; i++)
         *(mxGetPr(plhs[0]) + i) = (double)codeFrame[i];
    
    mxFree(codeFrame);    
    mxFree(infoFrame);
    
    return;
}