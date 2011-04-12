function CodeWord = ldpcEncoder(infoWord)

if nargin < 1
    error('Not enough input arguments'); 
end
if ~isreal(infoWord)
    error('infoWord must be a real array');
end

CodeWord = ldpcEncoder_mex(infoWord);
end