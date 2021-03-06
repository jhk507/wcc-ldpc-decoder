#include "ldpcEncoder.h"
#include "ldpcDecoderBP.h"
#include "matrixH_1_2.h"

int main()
{
	//short macroMatrixH[MACRO_MATRIX_M_SIZE][MACRO_MATRIX_N_SIZE] = MACRO_MATRIX;
	//short *binaryMatrixH = (short *)malloc(BINARY_MATRIX_M_SIZE*BINARY_MATRIX_N_SIZE*sizeof(short));
	short *infoWord = (short *)malloc(INFO_WORD_LEN*sizeof(short));
	short *codeWord = (short *)malloc(CODE_WORD_LEN*sizeof(short));
	//FILE *outFile = fopen("outBinMatrix.txt","w");
	FILE *dataToDecoderFile = fopen("llr.txt","r");
	FILE *codeFile = fopen("code.txt","r");
	int i, j, checkCW, resDec;
	int errCnt, itCount;
	double *llrFromDemapper = (double *)malloc(CODE_WORD_LEN*sizeof(double));
	double *llrFromDecoder	= (double *)malloc(CODE_WORD_LEN*sizeof(double));
	int *realCodeWord	= (double *)malloc(CODE_WORD_LEN*sizeof(double));
	int frameCnt = 5;
	double BER = 0;

	//CreateBinaryMatrix(&macroMatrixH[0][0],binaryMatrixH);
	/*EncodeInfoWord(infoWord,codeWord,binaryMatrixH);*/
	//PrintMatrixToHFile(binaryMatrixH,BINARY_MATRIX_M_SIZE,BINARY_MATRIX_N_SIZE,outFile);
	//fclose(outFile);

	for (i = 0;i<CODE_WORD_LEN;i++)
		*(codeWord + i) = 0;
	checkCW = CheckCodeWord(codeWord,&binaryMatrixH_1_2[0][0]);
	
	fseek(dataToDecoderFile, 0L, SEEK_SET );
	fseek(codeFile, 0L, SEEK_SET );
	for (j = 0; j< frameCnt;j++)
	{

		for (i = 0;i<CODE_WORD_LEN;i++)
		{
			fscanf(dataToDecoderFile,"%lf",llrFromDemapper+i);
			fscanf(codeFile,"%d",realCodeWord+i);
		}

		resDec = DecodeCodeWordBP(llrFromDemapper,llrFromDecoder,&binaryMatrixH_1_2[0][0],&macroMatrixH_1_2[0][0],&itCount,1);
		HardDecisionCodeWord(llrFromDecoder,codeWord);
	
		checkCW = CheckCodeWord(codeWord,&binaryMatrixH_1_2[0][0]);
		printf("checkCW Result: %d\n",checkCW);
		
		errCnt = 0;
		for(i = 0;i<CODE_WORD_LEN; i++)
			if(*(codeWord + i) != (*(realCodeWord + i)>0))
			{
	//			printf("Error of decoding in %d bit\n",i);
				errCnt++;
			}
		BER = ((double)errCnt/CODE_WORD_LEN);
		printf("BER = %lf\n",BER);
		if (!errCnt)
			printf("Decoding has no errors\n");
	}
	free(llrFromDecoder);
	free(llrFromDemapper);
	free(realCodeWord);
	free(codeWord);
	free(infoWord);
	fclose(dataToDecoderFile);
	fclose(codeFile);

	return 0;
}