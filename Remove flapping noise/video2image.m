close all;
clc;

filename = 'horz_stable.avi';
hvfr = vision.VideoFileReader(filename, 'ImageColorSpace', 'RGB','VideoOutputDataType', 'single');

K = 1;
while ~isDone(hvfr)
  imagename = ['stable\image' num2str(K) '.jpg'];
  raw_image = step(hvfr);

  imwrite(raw_image,imagename,'jpg');
  
  K = K+1;
end
