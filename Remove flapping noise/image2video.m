clear all; close all; clc

fnames=dir('*.jpg');
numfids=length(fnames);

aviobj = VideoWriter('example3.avi');
open(aviobj);
fig=figure;

for K=1: numfids

    im2_=imread(fnames(K).name);

    imshow(im2_);
    F = getframe(fig,[100,100,650,600]);
    writeVideo(aviobj,F);
K
end

close(fig);
close(aviobj);




