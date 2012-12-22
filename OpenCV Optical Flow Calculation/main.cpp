
//Practise code # 1
/*
#include <opencv2/highgui/highgui.hpp>

int main(int argc,char** argv)
{
    cvNamedWindow("Example1",CV_WINDOW_AUTOSIZE);
    CvCapture* capture= cvCreateFileCapture("/Users/yashchitalia/Desktop/OpenCV_trial/OpenCV_trial/flow.MOV");
    IplImage* frame;
    int numFrames = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);

    while(1)
    {
        frame = cvQueryFrame(capture);
        if(!frame) break;
        cvShowImage("Example1",frame);
        char c=cvWaitKey(33);
        if(c==27) break;
        int posFrames   = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES);
        if(posFrames-numFrames==0) break;

    }
    cvReleaseCapture(&capture);
    cvDestroyWindow("Example1");
}
*///Practise code 1
/*
//Practise Code 2
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int g_slider_position=0;
CvCapture* g_capture = NULL;

void onTrackbarSlide(int pos)
{
    cvSetCaptureProperty(g_capture,CV_CAP_PROP_POS_FRAMES,pos);
    
}
int main( int argc,char** argv)
{
    cvNamedWindow("Example2",CV_WINDOW_AUTOSIZE);
    g_capture=cvCreateFileCapture("/Users/yashchitalia/Desktop/OpenCV_trial/OpenCV_trial/flow.MOV");
    int frames=(int)cvGetCaptureProperty(g_capture,CV_CAP_PROP_FRAME_COUNT);
    
    if(frames!=0)
    {
        cvCreateTrackbar("Position","Example2",&g_slider_position,frames,onTrackbarSlide);
    }
    IplImage* frame;
    while(1)
    {
        frame = cvQueryFrame(g_capture);
        if(!frame) break;
        cvShowImage("Example1",frame);
        char c=cvWaitKey(33);
        if(c==27) break;
        
        
    }
    cvReleaseCapture(&g_capture);
    cvDestroyWindow("Example2");
}
 */ //Practise code 2
/*
//Practise code 3
#include <opencv2/highgui/highgui.hpp>

int main(int argc,char** argv)
{
    
    cvNamedWindow("Example1",CV_WINDOW_AUTOSIZE);
    CvCapture* capture;

        capture=cvCreateCameraCapture(0);
    
    IplImage* frame;
    while(1)
    {
        frame = cvQueryFrame(capture);
        if(!frame) break;
        cvShowImage("Example1",frame);
        char c=cvWaitKey(33);
        if(c==27) break;
        
    }
    cvReleaseCapture(&capture);
    cvDestroyWindow("Example1");
}
*/ //Practise code 3
/*
// Code to convert a video to grayscale 1 channel.
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int g_slider_position=0;
CvCapture* g_capture = NULL;
static int g_trackpos=0;

void onTrackbarSlide(int pos)
{
    cvSetCaptureProperty(g_capture,CV_CAP_PROP_POS_FRAMES,pos);
    g_trackpos=pos;
    
}
int main(int argc, char** argv)
{
    cvNamedWindow("Example2",CV_WINDOW_AUTOSIZE);
    g_capture=cvCreateFileCapture("/Users/yashchitalia/Desktop/OpenCV_trial/OpenCV_trial/flow.MOV");
    int frames=(int)cvGetCaptureProperty(g_capture,CV_CAP_PROP_FRAME_COUNT);
    int framerate=(int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FPS);
    CvSize size=cvSize((int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_WIDTH),(int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_HEIGHT));
    if(frames!=0)
    {
        cvCreateTrackbar("Position","Example2",&g_slider_position,frames,onTrackbarSlide);
    }
    
    IplImage* frame;
    IplImage* grayframe=cvCreateImage(size, IPL_DEPTH_8U, 1);

    while(1)
    {   g_trackpos++;
        frame = cvQueryFrame(g_capture);
        if(!frame) break;
        cvSetTrackbarPos("Position", "Example2", g_trackpos);
        //Now we convert to grayscale
        cvCvtColor(frame, grayframe,CV_RGB2GRAY);  //Now successfully converted the RGB Image to 8Bit single channel grayscale.
        
        cvShowImage("Example2",grayframe);
        char c=cvWaitKey(framerate);
        if(c==27) break;
        
        
    }
    cvReleaseCapture(&g_capture);
    cvDestroyWindow("Example2");
}
*/ //Code to convert RGB video to 1 channel 8bit grayscale.
/*

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cvaux.hpp>
#include <opencv/cxcore.hpp>

const int MAX_CORNERS = 500;

int main(int argc, char** argv)
{
    
    IplImage* imgA=cvLoadImage("/Users/yashchitalia/Desktop/OpenCV_trial/OpenCV_trial/IMG_2861 0271.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    IplImage* imgB=cvLoadImage("/Users/yashchitalia/Desktop/OpenCV_trial/OpenCV_trial/IMG_2861 0272.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    
    CvSize img_sz = cvGetSize(imgA);
    int win_size = 100;
    
    IplImage* imgC= cvLoadImage("/Users/yashchitalia/Desktop/OpenCV_trial/OpenCV_trial/image13.jpg", CV_LOAD_IMAGE_UNCHANGED);
    
    IplImage* eig_image=cvCreateImage(img_sz, IPL_DEPTH_32F, 1);
    IplImage* tmp_image=cvCreateImage(img_sz, IPL_DEPTH_32F, 1);
    
    int corner_count= MAX_CORNERS;
    CvPoint2D32f* cornersA= new CvPoint2D32f[ MAX_CORNERS];
    
    cvGoodFeaturesToTrack(imgA, eig_image, tmp_image, cornersA, &corner_count, 0.01, 5.0, 0,3,0,0.04);
    
    cvFindCornerSubPix(imgA, cornersA, corner_count, cvSize(win_size, win_size), cvSize(-1, -1), cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03));
    
    
    char features_found[MAX_CORNERS];
    float feature_errors[MAX_CORNERS];
    
    CvSize pyr_sz=cvSize(imgA->width+8, imgB->height/3);
    
    IplImage* pyrA=cvCreateImage(pyr_sz, IPL_DEPTH_32F, 1);
    IplImage* pyrB=cvCreateImage(pyr_sz, IPL_DEPTH_32F, 1);
    
    CvPoint2D32f* cornersB = new CvPoint2D32f[MAX_CORNERS];
    
    cvCalcOpticalFlowPyrLK(imgA, imgB, pyrA, pyrB, cornersA, cornersB, corner_count, cvSize(win_size, win_size), 5, features_found, feature_errors, cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.3), 0);
    
    for(int i=0;i<corner_count;i++)
    {
        if(features_found[i]==0||feature_errors[i]>550)
        {
            printf("Error is %f/n",feature_errors[i]);
            continue;
        }
        printf("Got it/n");
        CvPoint p0=cvPoint(cvRound(cornersA[i].x),
                           cvRound(cornersA[i].y));
        CvPoint p1=cvPoint(cvRound(cornersB[i].x),
                           cvRound(cornersB[i].y));
        cvLine(imgC, p0, p1, CV_RGB(0,126,0),2);
    }
    cvNamedWindow("ImageA",0);
    cvNamedWindow("ImageB",0);
    cvNamedWindow("LKpyr_OpticalFlow",0);
    
    cvShowImage("ImageA", imgA);
    cvShowImage("ImageB", imgB);
    cvShowImage("LKpyr_OpticalFlow", imgC);
    
    cvWaitKey(0);
    
    return 0;

    
    
        
}
*/ //Optical flow code for two images
/* // Optical flow code for a video
 #include <opencv2/opencv.hpp>
 #include <opencv2/highgui/highgui.hpp>
 #include <opencv/cvaux.hpp>
 #include <opencv/cxcore.hpp>
 
 const int MAX_CORNERS = 35;
 int g_slider_position=0;
 CvCapture* g_capture = NULL;
 static int g_trackpos=0;
 const int gaussian_width=9;
 void onTrackbarSlide(int pos)
 {
 cvSetCaptureProperty(g_capture,CV_CAP_PROP_POS_FRAMES,pos);
 g_trackpos=pos;
 
 }
 int main(int argc, char** argv)
 {
 cvNamedWindow("Example2",CV_WINDOW_AUTOSIZE);
 g_capture=cvCreateFileCapture("/Users/yashchitalia/Desktop/OpenCV_trial/OpenCV_trial/flow.MOV");
 int frames=(int)cvGetCaptureProperty(g_capture,CV_CAP_PROP_FRAME_COUNT);
 int framerate=(int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FPS);
 CvSize size=cvSize((int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_WIDTH),(int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_HEIGHT));
 
 if(frames!=0)
 {
 cvCreateTrackbar("Position","Example2",&g_slider_position,frames,onTrackbarSlide);
 }
 
 IplImage* frame1;
 IplImage* frame2;
 IplImage* grayframe1=cvCreateImage(size, IPL_DEPTH_8U, 1);
 IplImage* grayframe2=cvCreateImage(size, IPL_DEPTH_8U, 1);
 
 int win_size = 100;
 IplImage* eig_image=cvCreateImage(size, IPL_DEPTH_32F, 1);
 IplImage* tmp_image=cvCreateImage(size, IPL_DEPTH_32F, 1);
 int corner_count= MAX_CORNERS;
 CvPoint2D32f* corners1= new CvPoint2D32f[ MAX_CORNERS];
 char features_found[MAX_CORNERS];
 float feature_errors[MAX_CORNERS];
 CvSize pyr_sz=cvSize(grayframe1->width+8, grayframe2->height/3);
 
 IplImage* pyrA=cvCreateImage(pyr_sz, IPL_DEPTH_32F, 1);
 IplImage* pyrB=cvCreateImage(pyr_sz, IPL_DEPTH_32F, 1);
 CvPoint2D32f* corners2 = new CvPoint2D32f[MAX_CORNERS];
 
 bool NeedtoInit=true;
 char refreshtime;
 
 while(1)
 {   g_trackpos++;
 frame1 = cvQueryFrame(g_capture);
 double t1 = (double)cv::getTickCount();
 if(!frame1) break;
 //Now we convert to grayscale
 cvCvtColor(frame1, grayframe1,CV_RGB2GRAY);
 cvSmooth(grayframe1, grayframe1,CV_GAUSSIAN,gaussian_width,0.0);
 //Now we find good features to Track in Grayscaled first frame(Using Shi_Tomasi corner detect)
 if(NeedtoInit)
 {
 cvGoodFeaturesToTrack(grayframe1, eig_image, tmp_image, corners1, &corner_count, 0.01, 5.0, 0,3,0,0.04);
 
 cvFindCornerSubPix(grayframe1, corners1, corner_count, cvSize(win_size, win_size), cvSize(-1, -1), cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03));
 }
 t1 = ((double)cv::getTickCount() - t1)/cv::getTickFrequency();
 if (NeedtoInit)
 {
 refreshtime=cvWaitKey(2);
 NeedtoInit=false;
 }
 else
 {refreshtime=cvWaitKey(2);}
 if(refreshtime==27) break;
 
 //Now capture the next image
 frame2 = cvQueryFrame(g_capture);
 double t2 = (double)cv::getTickCount();
 if(!frame2) break;
 
 //Now we convert to grayscale
 cvCvtColor(frame2, grayframe2,CV_RGB2GRAY);
 cvSmooth(grayframe2, grayframe2,CV_GAUSSIAN,gaussian_width,0.0);
 
 cvCalcOpticalFlowPyrLK(grayframe1, grayframe2, pyrA, pyrB, corners1, corners2, corner_count, cvSize(win_size, win_size), 5, features_found, feature_errors, cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.3), 0);
 
 for(int i=0;i<corner_count;i++)
 {
 if(features_found[i]==0||feature_errors[i]>550)
 {
 NeedtoInit=true;
 continue;
 }
 CvPoint p0=cvPoint(cvRound(corners1[i].x),
 cvRound(corners1[i].y));
 CvPoint p1=cvPoint(cvRound(corners2[i].x),
 cvRound(corners2[i].y));
 cvLine(grayframe1, p0, p1, CV_RGB(0,126,0),2);
 }
 cvShowImage("Example2",grayframe1);
 t2 = ((double)cv::getTickCount() - t2)/cv::getTickFrequency();
 refreshtime=cvWaitKey(2);
 if(refreshtime==27) break;
 int posFrames   = (int) cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES);
 if(posFrames-frames==0) break; //If this is the last frame then exit.
 
 
 
 }
 
 cvReleaseCapture(&g_capture);
 cvDestroyWindow("Example2");
 }
 */ //Optical flow for the video
/*
// Code to convert video capture to avi
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cvaux.hpp>
#include <opencv/cxcore.hpp>

int main( int argc, char** argv ) {
    CvCapture* capture;
    
    capture = cvCreateCameraCapture(0);
    
    assert( capture != NULL );
    
    IplImage* bgr_frame = cvQueryFrame( capture );
    
    CvSize size = cvSize(
                         (int)cvGetCaptureProperty( capture,
                                                   CV_CAP_PROP_FRAME_WIDTH),
                         (int)cvGetCaptureProperty( capture,
                                                   CV_CAP_PROP_FRAME_HEIGHT)
                         );
    
    cvNamedWindow( "Webcam", CV_WINDOW_AUTOSIZE );
    
    CvVideoWriter *writer = cvCreateVideoWriter( "/Users/yashchitalia/Desktop/OpenCV_trial/OpenCV_trial/vidtry.AVI",
                                                CV_FOURCC('W','R','L','E'),
                                                30,
                                                size
                                                );
    
    while( (bgr_frame = cvQueryFrame( capture )) != NULL ) {
        cvWriteFrame(writer, bgr_frame );
        cvShowImage( "Webcam", bgr_frame );
        char c = cvWaitKey( 33 );
        if( c == 27 ) break;
    }
    cvReleaseVideoWriter( &writer );
    cvReleaseCapture( &capture );
    cvDestroyWindow( "Webcam" );
    return( 0 );
}
*/ //Code to store video from Webcam to file (DOESN'T WORK)(WORKS NOW DONT MODIFY CODEC (WRLE)!!!

// Optical flow code for a video
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cvaux.hpp>
#include <opencv/cxcore.hpp>
#include <iostream>
#include <fstream>

const int MAX_CORNERS = 500;
CvCapture* g_capture = NULL;


int main(int argc, char** argv)
{
    cvNamedWindow("Example2",CV_WINDOW_AUTOSIZE);
    g_capture=cvCreateFileCapture("/Users/yashchitalia/Desktop/OpenCV_trial/OpenCV_trial/duder_orig.AVI");
    int frames=(int)cvGetCaptureProperty(g_capture,CV_CAP_PROP_FRAME_COUNT);
    //int fps=(int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FPS);
    CvSize size=cvSize((int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_WIDTH),(int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_HEIGHT));
    
    IplImage* frame2;
    IplImage* grayframe1=cvCreateImage(size, IPL_DEPTH_8U, 1);
    IplImage* grayframe2=cvCreateImage(size, IPL_DEPTH_8U, 1);
    IplImage* unsmoothedgrayframe2=cvCreateImage(size,IPL_DEPTH_8U, 1);

    int win_size = 10;
    IplImage* eig_image=cvCreateImage(size, IPL_DEPTH_32F, 1);
    IplImage* tmp_image=cvCreateImage(size, IPL_DEPTH_32F, 1);
    int corner_count= MAX_CORNERS;
    CvPoint2D32f* corners1= new CvPoint2D32f[ MAX_CORNERS];
    char features_found[MAX_CORNERS];
    float feature_errors[MAX_CORNERS];
    CvSize pyr_sz=cvSize(grayframe1->width+8, grayframe2->height/3);
    const int gaussian_width=9;
    char filename[50];
    
    IplImage* pyrA=cvCreateImage(pyr_sz, IPL_DEPTH_32F, 1);
    IplImage* pyrB=cvCreateImage(pyr_sz, IPL_DEPTH_32F, 1);
    CvPoint2D32f* corners2 = new CvPoint2D32f[MAX_CORNERS];
    
    bool NeedtoInit=true;
    char refreshtime;
    int PosFrames=0;// Current frame;
    int errorcounter=0;
    int endofline_code=6555;
    std::ofstream matlabFile;
    matlabFile.open("/Users/yashchitalia/Desktop/OpenCV_trial/OpenCV_trial/pointsOutput_raw.txt");

    //Image velocity storage information

    while(1)
    {   //matlabFile << "Corners = [ ...\n";//Starting the file
        PosFrames++;
        frame2 = cvQueryFrame(g_capture);
        if(!frame2) break;
        //Now we convert to grayscale
        cvCvtColor(frame2, unsmoothedgrayframe2,CV_RGB2GRAY);
        cvSmooth(unsmoothedgrayframe2,grayframe2,CV_GAUSSIAN,gaussian_width,0.0);
        if(PosFrames==1)
        {
            cvCopy(grayframe2, grayframe1);
            
        }
        //Now we find good features to Track in Grayscaled first frame(Using Shi_Tomasi corner detect)
        //This will only happen if my error in the previous optical flow reading was above 550.
        if(NeedtoInit)
        {
        cvGoodFeaturesToTrack(grayframe1, eig_image, tmp_image, corners1, &corner_count, 0.01, 5.0, 0,3,0,0.04);
         
         cvFindCornerSubPix(grayframe1, corners1, corner_count, cvSize(win_size, win_size), cvSize(-1, -1), cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03));
            NeedtoInit=false;

        }
 
        //Now compute Pyramidal L-K Algorithm
        cvCalcOpticalFlowPyrLK(grayframe1, grayframe2, pyrA, pyrB, corners1, corners2, corner_count, cvSize(win_size, win_size), 5, features_found, feature_errors, cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.3), 0);
        
        errorcounter=0;//Count the number of points that have a higher error.
        matlabFile << endofline_code  << " " << endofline_code << "\n";
        /*
        matlabFile << endofline_code  << " " << endofline_code << " " << endofline_code << " " << endofline_code << " " << endofline_code << " " << endofline_code << "\n";
        */
        for(int i=0;i<corner_count;i++)
         {
         if(features_found[i]==0||feature_errors[i]>100)
         {
         errorcounter++;
         continue;
         }

         CvPoint p0=cvPoint(cvRound(corners1[i].x),
         cvRound(corners1[i].y));
         CvPoint p1=cvPoint(cvRound(corners2[i].x),
         cvRound(corners2[i].y));
         cvCircle(frame2,p0,4,cvScalar(255,0,0),2);
         cvLine(frame2, p0, p1, cvScalar(0,0,255),2);
         matlabFile << corners2[i].x-corners1[i].x << " " << corners2[i].y-corners1[i].y << "\n";
         /*
         matlabFile << corners2[i].x-corners1[i].x << " " << corners2[i].y-corners1[i].y << " " << corners1[i].x<< " "<< corners2[i].x << " " << corners1[i].y<< " " <<corners2[i].y << "\n";
           */
             
         }
        if(errorcounter>=10)
        {NeedtoInit=true;
        }
        sprintf(filename, "/Users/yashchitalia/Desktop/OpenCV_trial/OpenCV_trial/duder_raw/VideoFrame%d.jpg", PosFrames);
        if( !cvSaveImage(filename, frame2) )
        {
            fprintf(stderr, "failed to write image file maybe location doesn't exist%s\n", filename);
        }


        cvShowImage("Example2",frame2);
        refreshtime=cvWaitKey(2);
        if(refreshtime==27) break;
        if(PosFrames-frames==0) break; //If this is the last frame then exit.
        cvCopy(grayframe2, grayframe1);

        
    }
    matlabFile.close();
    cvReleaseCapture(&g_capture);
    cvDestroyWindow("Example2");
    printf("Finished");
}
 //Optical flow for the video
