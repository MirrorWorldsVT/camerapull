/*
 * VivotekFeed.cpp
 *
 *  Created on: Nov 10, 2014
 *      Author: Ed
 *  
 *	This is a hurriedly put-together method of showing the Vivotek feed in real time
 *		Feed 1 MUST be set to MJPEG (JPEG) or this will not work
 *		The program relies on the camera being on the default IP settings
 *
 *  Tutorials Used:
 *  	http://docs.opencv.org/trunk/doc/tutorials/video/background_subtraction/background_subtraction.html
 *  	http://opencv-srf.blogspot.com/2010/09/object-detection-using-color-seperation.html
 *  	http://mateuszstankiewicz.eu/?p=189
 */

//opencv
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/shape/shape.hpp"

#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

//global variables
Mat frame; //current frame
Mat contourMat;
int keyboard;

//function declarations
void help();
void processVideo(String videoFilename);

void help()
{
  cout
  << "--------------------------------------------------------------------------"  << endl
  << "This program displays the default Vivotek feed.                           "  << endl
  << "--------------------------------------------------------------------------"  << endl
  << endl;
}

int main()
{
	String stream = "http://169.254.244.236/video.mjpg";
	//print help information
	help();

	processVideo(stream);

	//destroy GUI windows
	destroyAllWindows();
	return EXIT_SUCCESS;
}

void processVideo(String videoFilename) {
	//create the capture object
	VideoCapture capture(videoFilename);
	if(!capture.isOpened()){
		//error in opening the video input
		cerr << "Unable to open video file: " << videoFilename << endl;
		exit(EXIT_FAILURE);
	}

	//read input data. ESC or 'q' for quitting
	while( (char)keyboard != 'q' && (char)keyboard != 27 ){

		//read the current frame
		if(!capture.read(frame)) {
			cerr << "Unable to read next frame." << endl;
			cerr << "Exiting..." << endl;
			exit(EXIT_FAILURE);
		}

		//get the frame number and write it on the current frame
		stringstream ss;
		rectangle(frame, cv::Point(10, 2), cv::Point(100,20),
				  cv::Scalar(255,255,255), -1);
		ss << capture.get(CAP_PROP_POS_FRAMES);
		string frameNumberString = ss.str();
		putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
				FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));

		//show the current frame
		imshow("Frame", frame);

		//get the input from the keyboard
		keyboard = waitKey( 30 );
	}
	//delete capture object
	capture.release();
}
