#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <memory>
#include <vector>
#include <string>
#include <iostream>

//Compile with g++ main.cpp -o main `pkg-config --libs --cflags opencv`

using namespace cv;
using namespace std;

int main(int, char**) {
    VideoCapture cap(0);
    if(!cap.isOpened()){
        return -1;
    }

    Mat binarilized;
    Mat edges;
    namedWindow("CV Demo 1",0);
//    cvSetWindowProperty("CV Demo 1", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

    for(;;) {
        Mat frame;
        cap >> frame;
        cvtColor(frame , binarilized , CV_BGR2GRAY);
//        threshold(binarilized , binarilized , 128 , 255 , THRESH_BINARY);

        //Clean up small objects:
/*
        erode(binarilized , binarilized , getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        dilate(binarilized , binarilized , getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        dilate(binarilized , binarilized , getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        erode(binarilized , binarilized , getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
*/
        Canny(binarilized , edges , 100 , 33 , 3);

		imshow("CV Demo 1", edges);

		if(waitKey(30) >= 0) {
			break;
		}
	}
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
