function Image = loadImage(name, ratio, TO_GRAY)
% Reads and preprocesses an image
Image = imread(name);

if(TO_GRAY && size(Image,3) == 3)
    Image = rgb2gray(Image);
end

if(isa(Image, 'uint8'))
    Image = double(Image) ./ 255;
end

if(ratio < 1)
    Image = imresize(Image, ratio);
end

