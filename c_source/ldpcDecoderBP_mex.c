#include <mex.h>
#include "ldpcDecoderBP.h"
#include "matrixH_1_2.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	double* codeFrame;
    short* infoFrame;
	int infoWordLen;
	
	short* matrixH;
	short  matrixHSizeM = 0;
	short  matrixHSizeN = 0;
    short* macroMatrixH;
	short  macroMatrixHSizeM = 0;
	short  macroMatrixHSizeN = 0;
    short* matrixHn;
    short  matrixHnSizeN = 0;
    short* matrixHm;
    short  matrixHmSizeM = 0;
	
    short minSumAppr;
    int frameLen;
	double  codeRate;
	int maxIterCount;

	int i, j, res;
    int iterCount;

	if (nrhs < 4)
		 mexErrMsgTxt("Four input arguments are required");
	if (nlhs < 1)
		 mexErrMsgTxt("One or Two output arguments are required");

    frameLen = (int)(mxGetScalar(prhs[1]));
	codeRate = (double)(mxGetScalar(prhs[2]));
	maxIterCount = (int)(mxGetScalar(prhs[3]));
    minSumAppr = (short)(mxGetScalar(prhs[4]));

	if (codeRate ==  0.5)
	{
		matrixH = &binaryMatrixH_1_2;
		matrixHSizeM = binaryMatrixH_1_2_SizeM;
		matrixHSizeN = binaryMatrixH_1_2_SizeN;
		macroMatrixH = &macroMatrixH_1_2;
		macroMatrixHSizeM = macroMatrixH_1_2_SizeM;
		macroMatrixHSizeN = macroMatrixH_1_2_SizeN;
		matrixHn = &matrixHn_1_2;
		matrixHnSizeN = matrixHn_1_2_SizeN;
		matrixHm = &matrixHm_1_2;
		matrixHmSizeM = matrixHm_1_2_SizeM;
	}
	else
		mexErrMsgTxt("Unknown CodeRate (supported: 1/2)");
    
    infoWordLen = ceil(codeRate * codeWordLen);
    codeFrame = (double *)mxCalloc(codeWordLen * frameLen,sizeof(double));
    infoFrame = (short	*)mxCalloc(codeWordLen * frameLen,sizeof(short));

	for(i = 0;i<codeWordLen * frameLen;i++)
    {
        codeFrame[i] = (double)*(mxGetPr(prhs[0])+ i);
    }

	plhs[1] = mxCreateDoubleMatrix(1, frameLen, mxREAL);
    plhs[2] = mxCreateDoubleMatrix(1, frameLen, mxREAL);    
	for (i = 0; i<frameLen; i++)
    {
		res = DecodeCodeWordBP(	codeFrame + i*codeWordLen, infoFrame + i*infoWordLen, matrixH, matrixHSizeM, matrixHSizeN, \
								macroMatrixH, macroMatrixHSizeM, macroMatrixHSizeN, \
								matrixHn, matrixHnSizeN, matrixHm, matrixHmSizeM,\
								maxIterCount, minSumAppr, &iterCount);
        printf("%d\t",res);
		*(mxGetPr(plhs[2]) + i) = res;
        *(mxGetPr(plhs[1]) + i) = iterCount;
    }
    printf("\n");    

	plhs[0] = mxCreateDoubleMatrix(1, infoWordLen*frameLen, mxREAL);
	for (j = 0; j< frameLen; j++)
		for (i = 0; i< infoWordLen; i++)
		{
		     *(mxGetPr(plhs[0]) + i + j*infoWordLen) = (double)infoFrame[i + j*infoWordLen];
		}



    mxFree(codeFrame);    
    mxFree(infoFrame);
	return;
}