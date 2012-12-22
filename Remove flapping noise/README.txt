Procedure of reducing flapping noise:

1. video2image is to make images from  raw video.

2. making_border is for making the black border around the 1st image, for convience of stitching later.

3. whole_video_sift is for stitching the images. whole_video_sift invokes the function in sift_mosaic.

4. resizing_centuring is for centering the wrapped images with respect to x-axis, for keeping the optical flow in horizontal direction.

5. image2video is for making video from images. It's used for making video for demo.