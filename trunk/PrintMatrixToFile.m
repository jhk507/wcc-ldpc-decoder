function [] = PrintMatrixToFile(fid,matrixP,matrixName)
[rowCount ,colCount] = size(matrixP);
fprintf(fid,'short %s [%d][%d] =\t { \\\n',matrixName,rowCount,colCount);
for ii = 1:rowCount
		fprintf(fid,'{');
			for jj = 1:colCount
				if (jj ~= colCount)
					fprintf(fid,'%d, ',matrixP(ii,jj));
				else
					fprintf(fid,'%d ',matrixP(ii,jj));
                end
            end
			if (ii ~= (rowCount))
				fprintf(fid,'}, \\\n');
			else
				fprintf(fid,'}  \\\n};\n\n');
            end
end
end