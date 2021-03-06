function CodeWord = ldpcEncoder(infoFrame, frameLength, codeRate)

if nargin < 2
    error('Not enough input arguments'); 
end
if ~isreal(infoFrame)
    error('infoFrame must be a real array');
end

CodeWord = ldpcEncoder_mex(infoFrame, frameLength, codeRate);
end