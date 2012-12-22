function Dictionary = formTextonDictionaryModified(im_dir, images, outputToScreen, graphics)
% Learns a dictionary with a Kohonen network.
outputToScreen = true;
graphics = true;
n_images = length(images);
no_textons=30;
patch_size=5;
% get image information:
Image = loadImage([im_dir, '/', images{1}],1,true);
WIDTH = size(Image, 2);
HEIGHT = size(Image, 1);
if(size(Image,3) == 3)
    COLOR = true;
    Dictionary = zeros(no_textons,patch_size*patch_size * 3);
    else
    COLOR = false;
    Dictionary = zeros(no_textons,patch_size*patch_size);    
end
% during training we use full sampling
fprintf('Training with samples that cover the entire image %\n');
alpha = 0.5; % alpha is the learning rate, which will decrease over time.
for im = 1:n_images
        if(mod(im, floor(n_images / 10)) == 0)
            fprintf('.');
        end
Image = loadImage([im_dir '/' images{im}],1,true);
    % extract samples
    for x = 1:patch_size:WIDTH-patch_size
        for y = 1:patch_size:HEIGHT-patch_size
            % extract a sample
            Sample = Image(y:y+patch_size-1, x:x+patch_size-1, :);
            Sample = Sample(:)';
            % determine the closest texton
            for w = 1:no_textons
                distns(w) = pdist([double(Sample);Dictionary(w,:)]);
            end
            [val,ind] = min(distns);
            % move the closest word towards the sample
            if(ind >= 1 && ind <= size(Dictionary,1))
                err_clust = Sample - Dictionary(ind,:); 
            end
            Dictionary(ind,:) = Dictionary(ind,:) + alpha * err_clust;
        end
    end
    % if all textons are filled in, start decreasing alpha
    D_sum = sum(Dictionary,2);    
    if(sum(size(find(D_sum == 0))) < 2)
        remaining_images = n_images - im;
        alpha = alpha - 0.5 / remaining_images;
        if(alpha < 0.05)
            alpha = 0.05;
        end
    end
end
fprintf('\n');
% save('Dictionary',Dictionary);
end
