README FOR THE OPENCV OPTICAL FLOW COMPUTATION:


1. This code "main.cpp" will take the video "duder-orig.AVI" and compute optical flow on the same.
The user must first change the code "main.cpp" to modify the current location of the .AVI video.


2. It will store each frame of the processed video in a folder called "duder_raw" that the user must create in the desired location and then modify the method that writes to this folder in the code main.cpp.


3. The code will also generate a text file that contains the optical flow vectors per frame. This vectors per frame are listed, with " 6555 6555 6555 6555" code inserted to identify start of a new frame. This was done to avoid "Harris corner detection" output confusion, since the method did not spit out the actual number of corners detected. Therefore the user must modify the location where this text file will be written.



4.Note: Each of the lines of code that the user must modify to run the code have been given a comment as // MODIFY THIS!!! . 
Just change that much.