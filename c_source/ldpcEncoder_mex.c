#include <mex.h>
#include "ldpcEncoder.h"
#include "ldpcMatrixH.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	short* matrixH = (short *)malloc(BINARY_MATRIX_N_SIZE*BINARY_MATRIX_M_SIZE*sizeof(short));
	
	if (nrhs != 1)
		 mexErrMsgTxt("One input arguments are required");
	if (nlhs != 1)
		 mexErrMsgTxt("One output arguments are required");
	if (mxIsComplex(plhs[0]))
		 mexErrMsgTxt("Output arguments should not be complex");
	if (mxIsComplex(prhs[0]))
		 mexErrMsgTxt("Input arguments should not be complex");

	EncodeInfoWord(mxGetPr(prhs[0]),mxGetPr(plhs[0]), matrixH);	
}