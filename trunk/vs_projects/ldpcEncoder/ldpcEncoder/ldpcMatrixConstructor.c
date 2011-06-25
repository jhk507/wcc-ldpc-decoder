#include "ldpcMatrixConstructor.h"

void CyclicMatrixOffset(short *inMatrix, short *outMatrix, int matrixSize, int matrixOffset)
{
	int i,j;

	for (i = 0; i<matrixSize; i++)
		for(j = 0;j<matrixSize; j++)
			*(outMatrix+i*matrixSize+(matrixOffset + j)%matrixSize) = *(inMatrix+j*matrixSize+i);//(matrixOffset + i)%matrixSize
}

void CreateIdentityMatrix(short *outMatrix, int matrixSize)
{
	int i,j;
	for (i = 0; i< matrixSize; i++)
		for(j = 0; j<matrixSize; j++)
			if (i == j)
			*(outMatrix+i*matrixSize+j) = 1;
			else
			*(outMatrix+i*matrixSize+j) = 0;
}

void CreateNullMatrix(short *outMatrix, int matrixSize)
{
	int i;	
	for (i = 0; i<matrixSize*matrixSize; i++) 
		*(outMatrix + i) = 0;
}

void MicroToBinaryMatrixInsert(short *inMicroMatrix, int insPosM, int insPosN, short *outBinaryMatrix)
{
	int i,j;
	for (i = 0; i<MICRO_IDENTITY_MATRIX_SIZE; i++)
		for (j = 0; j<MICRO_IDENTITY_MATRIX_SIZE; j++)
			*(outBinaryMatrix + (i + insPosM*MICRO_IDENTITY_MATRIX_SIZE)*BINARY_MATRIX_N_SIZE + (j + insPosN*MICRO_IDENTITY_MATRIX_SIZE)) = *(inMicroMatrix + i*MICRO_IDENTITY_MATRIX_SIZE + j);
}

void TransformToBinaryMatrix(short *inMacroMatrix, short *outBinaryMatrix)
{
	int i,j;
	short *identityMatrix = (short *)malloc(MICRO_IDENTITY_MATRIX_SIZE*MICRO_IDENTITY_MATRIX_SIZE*sizeof(short));
	short *nullMatrix = (short *)malloc(MICRO_IDENTITY_MATRIX_SIZE*MICRO_IDENTITY_MATRIX_SIZE*sizeof(short));
	short *insertMatrix = (short *)malloc(MICRO_IDENTITY_MATRIX_SIZE*MICRO_IDENTITY_MATRIX_SIZE*sizeof(short));

	CreateIdentityMatrix(identityMatrix,MICRO_IDENTITY_MATRIX_SIZE);
	CreateNullMatrix(nullMatrix,MICRO_IDENTITY_MATRIX_SIZE);

	for (i = 0; i< MACRO_MATRIX_M_SIZE; i++)
		for (j = 0; j< MACRO_MATRIX_N_SIZE; j++)
		{
			if(*(inMacroMatrix + i*MACRO_MATRIX_N_SIZE + j) != -1)
			{
				CyclicMatrixOffset(identityMatrix,insertMatrix,MICRO_IDENTITY_MATRIX_SIZE,*(inMacroMatrix + i*MACRO_MATRIX_N_SIZE + j));
				MicroToBinaryMatrixInsert(insertMatrix,i,j,outBinaryMatrix);
			}
			else
				MicroToBinaryMatrixInsert(nullMatrix,i,j,outBinaryMatrix);
		}
	free(identityMatrix);
	free(nullMatrix);
	free(insertMatrix);
}

void CopyRowsOfMatrix(short *inMatrix, short *outMatrix, int colCount, int fromN, int toN)
{
	int i;
	for (i = 0;i<colCount;i++)
		*(outMatrix + toN*colCount + i) = *(inMatrix + fromN*colCount + i);
}

void TransformToTriangularView(short *inBinaryMatrix, short *inMacroMatrix, short *outBinaryMatrix)
{
	int i,n,j;
	int offset;
	n = MACRO_MATRIX_N_SIZE - 1;
	for (i = 0; i<MACRO_MATRIX_M_SIZE;i++)
	{
		offset = *(inMacroMatrix + (MACRO_MATRIX_M_SIZE - 1 - i)*MACRO_MATRIX_N_SIZE +n);
		for (j = 0; j<MICRO_IDENTITY_MATRIX_SIZE;j++)		
			CopyRowsOfMatrix(inBinaryMatrix,outBinaryMatrix,BINARY_MATRIX_N_SIZE,(j+MICRO_IDENTITY_MATRIX_SIZE-offset)%MICRO_IDENTITY_MATRIX_SIZE + (MACRO_MATRIX_M_SIZE - 1 - i)*MICRO_IDENTITY_MATRIX_SIZE,j + (MACRO_MATRIX_M_SIZE - 1 - i)*MICRO_IDENTITY_MATRIX_SIZE);
		n--;
	}
}

void CreateBinaryMatrix(short *inMacroMatrix, short *outBinaryMatrix)
{
	short *tmpBinaryMatrix = (short *)malloc(BINARY_MATRIX_M_SIZE*BINARY_MATRIX_N_SIZE*sizeof(short));

	TransformToBinaryMatrix(inMacroMatrix,tmpBinaryMatrix);
 	TransformToTriangularView(tmpBinaryMatrix,inMacroMatrix,outBinaryMatrix);
 	free(tmpBinaryMatrix);
}

void PrintMatrix(short *matrix, int rowCount, int colCount)
{
	int i, j;
	for (i = 0; i< rowCount; i++)
	{
		for (j = 0; j< colCount; j++)
			printf("%d ",*(matrix + i*colCount + j));
		printf("\n");
	}
}

void PrintMatrixToFile(short *matrix, int rowCount, int colCount, FILE *outputFile)
{
	int i, j;
	for (i = 0; i< rowCount; i++)
	{
		for (j = 0; j< colCount; j++)
			fprintf(outputFile,"%d\t",*(matrix + i*colCount + j));
		fprintf(outputFile,"\n");
	}
}

void PrintMatrixToHFile(short *matrix, int rowCount, int colCount, FILE *outputFile)
{
	int i, j;
		fprintf(outputFile,"#define BINARY_H_MATRIX_N_SIZE \t %d \n",colCount);
		fprintf(outputFile,"#define BINARY_H_MATRIX_M_SIZE \t %d \n",rowCount);
		fprintf(outputFile,"#define CODE_RATE \t 1/2 \n");
		fprintf(outputFile,"#define CODE_WORD_LEN \t %d \n",colCount);
		fprintf(outputFile,"#define INFO_WORD_LEN \t CODE_WORD_LEN*CODE_RATE \n");
		fprintf(outputFile,"#define BINARY_H_MATRIX \t { \\\n");
		for (i = 0; i< rowCount; i++)
		{
			fprintf(outputFile,"{");
			for (j = 0; j< colCount; j++)
				if (j != (colCount - 1))
					fprintf(outputFile,"%d, ",*(matrix + i*colCount + j));
				else
					fprintf(outputFile,"%d ",*(matrix + i*colCount + j));
			if (i != (rowCount - 1))
				fprintf(outputFile,"}, \\\n");
			else
				fprintf(outputFile,"}  \\\n}");
		}
}

