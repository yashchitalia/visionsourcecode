function H = getEntropy(P)
% P is a column vector containing probabilities
% H is its corresponding entropy

if(size(P,2) > size(P,1))
    P = P';
end

% normalise P
if(sum(P) ~= 0)
    P = P ./ sum(P);
    % calculate entropy
    s_P = size(P);
    H = 0;
    for c = 1:s_P(1,1)
        if(P(c,1) ~= 0)
            H = H - P(c,1) * log2(P(c,1));
        end
    end
else
    error('The sum of P is zero.');
end