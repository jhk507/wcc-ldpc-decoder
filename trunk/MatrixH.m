clc
clear
macroMatrixNSize = 16;
macroMatrixMSize = 8;
elemMatrixSize = 42;
elemIdentMatrix = eye(elemMatrixSize);

macroMatrix1_2 = [40, -1, 38, -1, 13, -1,  5, -1, 18, -1, -1, -1, -1, -1, -1, -1;...
                  34, -1, 35, -1, 27, -1, -1, 30,  2,  1, -1, -1, -1, -1, -1, -1;...
                  -1, 36, -1, 31, -1,  7, -1, 34, -1, 10, 41, -1, -1, -1, -1, -1;...
                  -1, 27, -1, 18, -1, 12, 20, -1, -1, -1, 15,  6, -1, -1, -1, -1;...
                  35, -1, 41, -1, 40, -1, 39, -1, 28, -1, -1,  3, 28, -1, -1, -1;...
                  29, -1,  0, -1, -1, 22, -1,  4, -1, 28, -1, -1, 24, 23, -1, -1;...
                  -1, 31, -1, 23, -1, 21, -1, 20, -1, -1, 12, -1, -1,  0, 13, -1;...
                  -1, 22, -1, 34, 31, -1, 14, -1, -1, -1, -1, 18, -1, -1, 22, 24];
              
binaryMatrix = [];
tempMatrix = [];
              
for jj = 1:1:macroMatrixMSize
    tempMatrix = [];
    for ii = 1:1:macroMatrixNSize
      if macroMatrix1_2(jj,ii)> -1
      tempMatrix = [tempMatrix, cyclicMatrixOffset(elemIdentMatrix, macroMatrix1_2(jj,ii))];
      else
      tempMatrix = [tempMatrix, zeros(elemMatrixSize)];
      end
    end
    binaryMatrix = [binaryMatrix; tempMatrix];
end

fid = fopen('matrixH_1_2.txt','w');
fprintf(fid,'#define BINARY_H_MATRIX_N_SIZE \t %d \n',macroMatrixNSize*elemMatrixSize);
fprintf(fid,'#define BINARY_H_MATRIX_M_SIZE \t %d \n',macroMatrixNSize*elemMatrixSize);
fprintf(fid,'#define CODE_RATE \t 1/2 \n');
fprintf(fid,'#define CODE_WORD_LEN \t %d \n',macroMatrixNSize*elemMatrixSize);
fprintf(fid,'#define INFO_WORD_LEN \t CODE_WORD_LEN*CODE_RATE \n');
fprintf(fid,'#define BINARY_H_MATRIX \t { \\\n');
 for ii = 1:1:macroMatrixMSize*elemMatrixSize
     for jj = 1:1:macroMatrixNSize*elemMatrixSize
        fprintf(fid,'%d, ',binaryMatrix(ii,jj));         
     end
  end
 fclose(fid);