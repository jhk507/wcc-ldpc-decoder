clc
% clear
macroMatrixNSize = 16;
macroMatrixMSize = 8;
elemMatrixSize = 42;
binaryMatrixNSize = macroMatrixNSize*elemMatrixSize;
binaryMatrixMSize = macroMatrixMSize*elemMatrixSize;
elemIdentMatrix = eye(elemMatrixSize);

macroMatrix1_2 = [40  -1  38  -1  13  -1   5  -1  18  -1  -1  -1  -1  -1  -1  -1; 
                34  -1  35  -1  27  -1  -1  30   2   1  -1  -1  -1  -1  -1  -1; 
                -1  36  -1  31  -1   7  -1  34  -1  10  41  -1  -1  -1  -1  -1; 
                -1  27  -1  18  -1  12  20  -1  -1  -1  15   6  -1  -1  -1  -1; 
                35  -1  41  -1  40  -1  39  -1  28  -1  -1   3  28  -1  -1  -1; 
                29  -1   0  -1  -1  22  -1   4  -1  28  -1  27  -1  23  -1  -1; 
                -1  31  -1  23  -1  21  -1  20  -1  -1  12  -1  -1   0  13  -1; 
                -1  22  -1  34  31  -1  14  -1   4  -1  -1  -1  13  -1  22  24];
              
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

offset = 0;
encodeBinaryMatrix = zeros(binaryMatrixMSize,binaryMatrixNSize);
n = macroMatrixNSize;
	for ii = 1:macroMatrixMSize
	
		offset = macroMatrix1_2(macroMatrixMSize - ii + 1,n);
		for jj = 1:elemMatrixSize
			encodeBinaryMatrix((macroMatrixMSize-ii)*elemMatrixSize + jj,:) = binaryMatrix((macroMatrixMSize-ii)*elemMatrixSize + mod(elemMatrixSize - offset + jj - 1,elemMatrixSize) + 1,:);
%             CopyRowsOfMatrix(inBinaryMatrix,outBinaryMatrix,BINARY_MATRIX_N_SIZE,(j+MICRO_IDENTITY_MATRIX_SIZE-offset)%MICRO_IDENTITY_MATRIX_SIZE + 5(MACRO_MATRIX_M_SIZE - 1 - i)*MICRO_IDENTITY_MATRIX_SIZE,j + (MACRO_MATRIX_M_SIZE - 1 - i)*MICRO_IDENTITY_MATRIX_SIZE);
		end
        n = n - 1;
    end

maxN = 0;
for ii = 1:macroMatrixMSize
    if(maxN<sum(macroMatrix1_2(ii,:)>0))
        maxN = sum(macroMatrix1_2(ii,:)>0);
    end
end
matrixHn = zeros(binaryMatrixMSize,maxN + 1);
for ii = 1:binaryMatrixMSize
    n = 1;
    for jj = 1:binaryMatrixNSize
       if binaryMatrix(ii,jj)>0
           matrixHn(ii,n) = jj - 1;
           n = n + 1;
       end
       if jj == binaryMatrixNSize
           matrixHn(ii,n) = -1;
       end
    end
end


maxM = 0;
for ii = 1:macroMatrixNSize
    if(maxM<sum(macroMatrix1_2(:,ii)>0))
        maxM = sum(macroMatrix1_2(:,ii)>0);
    end
end
matrixHm = zeros(maxM + 1,binaryMatrixNSize);
for ii = 1:binaryMatrixNSize
    n = 1;
    for jj = 1:binaryMatrixMSize
       if binaryMatrix(jj,ii)>0
           matrixHm(n,ii) = jj - 1;
           n = n + 1;
       end
       if jj == binaryMatrixMSize
           matrixHm(n,ii) = -1;
       end
    end
end

%-------------------------------------
% 
%  ---- Print matrices to h-file -----
% 
%--------------------------------------

fid = fopen('c_source\matrixH_1_2.h','w');

% -- print config parameters for H-matrix --
fprintf(fid,'#ifndef __MATRIX_H_1_2__\n');
fprintf(fid,'#define __MATRIX_H_1_2__\n\n');
fprintf(fid,'int macroMatrixH_1_2_SizeN\t = \t %d;\n',macroMatrixNSize);
fprintf(fid,'int macroMatrixH_1_2_SizeM\t = \t %d;\n',macroMatrixMSize);
fprintf(fid,'int codeWordLen\t = \t %d;\n\n',binaryMatrixNSize);

% -- print macro H-matrix --
PrintMatrixToFile(fid,macroMatrix1_2,'macroMatrixH_1_2');

% -- print binary H-matrix for decoding --
fprintf(fid,'int binaryMatrixH_1_2_SizeN\t = \t %d;\n',binaryMatrixNSize);
fprintf(fid,'int binaryMatrixH_1_2_SizeM\t = \t %d;\n',binaryMatrixMSize);
PrintMatrixToFile(fid,binaryMatrix,'binaryMatrixH_1_2');

% -- print binary H-matrix for encoding --
PrintMatrixToFile(fid,encodeBinaryMatrix,'encodeBinaryMatrixH_1_2');

%  -- print Hm-matrix for decoding --
fprintf(fid,'int matrixHm_1_2_SizeM\t = \t %d;\n',maxM + 1);
PrintMatrixToFile(fid,matrixHm,'matrixHm_1_2');

%  -- print Hn-matrix for decoding --
fprintf(fid,'int matrixHn_1_2_SizeN\t = \t %d;\n',maxN + 1);
PrintMatrixToFile(fid,matrixHn,'matrixHn_1_2');

fprintf(fid,'#endif /*__MATRIX_H_1_2__*/\n');
 fclose(fid);