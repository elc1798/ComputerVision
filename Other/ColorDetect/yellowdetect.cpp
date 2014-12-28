#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <memory>
#include <vector>
#include <string>
#include <iostream>

#define LOW_H 15
#define LOW_S 120
#define LOW_V 120
#define HIGH_H 50
#define HIGH_S 255
#define HIGH_V 255

//Compile with g++ main.cpp -o main `pkg-config --libs --cflags opencv`

using namespace cv;
using namespace std;

int main(int, char**) {
	VideoCapture cap(0);
	if(!cap.isOpened()){
		return -1;
	}

	Mat yellow;
	namedWindow("CV Demo 1",1);

	for(;;) {
		Mat frame;
		cap >> frame;
		cvtColor(frame , frame , CV_BGR2HSV);
                inRange(frame , Scalar(LOW_H , LOW_S , LOW_V), Scalar(HIGH_H , HIGH_S , HIGH_V), yellow);

		//Clean up small objects:

		erode(yellow , yellow , getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
		dilate(yellow , yellow , getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
		dilate(yellow , yellow , getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
		erode(yellow , yellow , getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

		imshow("CV Demo 1", yellow);

		if(waitKey(30) >= 0) {
			break;
		}
	}
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
