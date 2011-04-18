#include "ldpcEncoder.h"
#include "ldpcDecoderBP.h"

int main()
{
	short macroMatrixH[MACRO_MATRIX_M_SIZE][MACRO_MATRIX_N_SIZE] = MACRO_MATRIX;
	short *binaryMatrixH = (short *)malloc(BINARY_MATRIX_M_SIZE*BINARY_MATRIX_N_SIZE*sizeof(short));
	short *infoWord = (short *)malloc(INFO_WORD_LEN*sizeof(short));
	short *codeWord = (short *)malloc(CODE_WORD_LEN*sizeof(short));
	FILE *outFile = fopen("outBinMatrix.txt","w");
	FILE *dataToDecoderFile = fopen("llr.txt","r");
	int i, checkCW, resDec;
	int errCnt = 0;
	double *llrFromDemapper = (double *)malloc(CODE_WORD_LEN*sizeof(double));
	double *llrFromDecoder	= (double *)malloc(CODE_WORD_LEN*sizeof(double));

	for(i = 0;i<INFO_WORD_LEN;i++) *(infoWord + i) = ((i%41) == 0);

	CreateBinaryMatrix(&macroMatrixH[0][0],binaryMatrixH);
	/*EncodeInfoWord(infoWord,codeWord,binaryMatrixH);
	checkCW = CheckCodeWord(codeWord,binaryMatrixH);*/
	


	fseek(dataToDecoderFile, 0L, SEEK_SET );
	for (i = 0;i<CODE_WORD_LEN;i++)
		fscanf(dataToDecoderFile,"%lf",llrFromDemapper+i);

	fclose(dataToDecoderFile);
	resDec = DecodeCodeWordBP(llrFromDemapper,llrFromDecoder,binaryMatrixH,&macroMatrixH[0][0],0.1,0);
	HardDecisionCodeWord(llrFromDecoder,codeWord);
	
	PrintMatrixToFile(codeWord,1,CODE_WORD_LEN,outFile);
	fclose(outFile);
	checkCW = CheckCodeWord(codeWord,binaryMatrixH);
	printf("checkCW Result: %d\n",checkCW);

	for(i = 0;i<CODE_WORD_LEN; i++)
		if(*(codeWord + i) != (*(llrFromDemapper + i)>0))
		{
			printf("Error of decoding in %d bit\n",i);
			errCnt++;
		}
	if (!errCnt)
		printf("Decoding has no errors\n");

	return 0;
}