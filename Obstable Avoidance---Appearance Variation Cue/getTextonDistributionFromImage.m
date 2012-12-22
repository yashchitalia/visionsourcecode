function distribution = getTextonDistributionFromImage(Image, Dictionary)
% Estimates the distribution of textons in "Dictionary" in the "Image",
WIDTH = size(Image,2);
HEIGHT = size(Image,1);
finished = false;
x = 1; 
y = 1;
s = 0;
FULL_SAMPLING=false;
no_textons=30;
patch_size=5;
no_samples=50;
% initialize distribution
distribution = zeros(1,no_textons);
bin_size = HEIGHT;

% The method can use full sampling, in which case image patches are extracted
% at all pixels, or random sampling with a fixed number of samples, no_samples.

while(~finished)
    
    if(~FULL_SAMPLING)
        s = s + 1;
        x = 1 + round(rand(1) * (WIDTH - patch_size - 1));
        y = 1 + round(rand(1) * (HEIGHT - patch_size - 1));
    end

    % extract sample
    Sample = Image(y:y+patch_size-1, x:x+patch_size-1, :);
    Sample = Sample(:)';
    
    % determine the closest word
    for w = 1:no_textons
        dists(w) = pdist([double(Sample);Dictionary(w,:)]);
    end
    
    % add to the distribution
    [val,ind] = min(dists);
    distribution(ind) = distribution(ind) + 1;
       
        if (s == no_samples)
            finished = true;
        end
    end

% Normalize distribution
distribution = distribution ./ sum(distribution);
