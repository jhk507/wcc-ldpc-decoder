function CodeWord = ldpcEncoder(infoWord)

if nargin < 1
    error('Not enough input arguments'); 
end
if ~isreal(infoWord)
    error('infoWord must be a real array');
end

Cw = zeros(1, 672);

ldpcEncoder_mex(infoWord,Cw);
CodeWord = Cw;
end