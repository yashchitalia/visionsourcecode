clear all; close all; clc

fnames=dir('*.jpg');
numfids=length(fnames);


for K=1:numfids-1
    if (K==1)
        im1=imread(fnames(K).name);
        im2=imread(fnames(K+1).name);
        [im2_,H_] = sift_mosaic(im1, im2);

    else
        im1=im2_;
        im2=imread(fnames(K+1).name);
        [im2_,H_] = sift_mosaic(im1, im2);
        
    end
    imwrite(im2_,strcat('\\storage.adsroot.itcs.umich.edu\home\windat.v2\Desktop\442 project code\demo_videos2\893_modify\',fnames(K).name),'jpg');

K
end
