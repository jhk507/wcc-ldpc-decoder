function outMatrix = cyclicMatrixOffset( inMatrix, offset )

[mN,mM] = size(inMatrix);
outMatrix = zeros(mN,mM);
for itCnt = 1:1:mM
    outMatrix(:,mod(itCnt + offset, mN) + 1) = inMatrix(:,mod(itCnt, mN) + 1);
end

