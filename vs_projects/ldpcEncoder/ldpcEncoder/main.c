#include "ldpcEncoder.h"
#include "ldpcDecoderBP.h"

int main()
{
	short macroMatrixH[MACRO_MATRIX_M_SIZE][MACRO_MATRIX_N_SIZE] = MACRO_MATRIX;
	short *binaryMatrixH = (short *)malloc(BINARY_MATRIX_M_SIZE*BINARY_MATRIX_N_SIZE*sizeof(short));
	short *infoWord = (short *)malloc(INFO_WORD_LEN*sizeof(short));
	short *codeWord = (short *)malloc(CODE_WORD_LEN*sizeof(short));
	FILE *outFile = fopen("outBinMatrix.txt","w");
	int i;
	float codeWordFromChanel[CODE_WORD_LEN] = {0};
	float codeWordFromDecoder[CODE_WORD_LEN] = {0};

	for(i = 0;i<INFO_WORD_LEN;i++) *(infoWord + i) = ((i%41) == 0);

	CreateBinaryMatrix(&macroMatrixH[0][0],binaryMatrixH);
	EncodeInfoWord(infoWord,codeWord,binaryMatrixH);

	DecodeCodeWordBP(codeWordFromChanel,codeWordFromDecoder,binaryMatrixH,&macroMatrixH[0][0]);
	
	PrintMatrixToFile(codeWord,1,CODE_WORD_LEN,outFile);
	fclose(outFile);

	return 0;
}