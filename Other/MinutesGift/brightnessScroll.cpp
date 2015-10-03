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

    double alpha = 1.0;
    bool up = true;
    Mat binarilized;
    Mat tinted;
    namedWindow("CV Demo 1",0);
    cvSetWindowProperty("CV Demo 1", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

    for(;;) {
        Mat frame;
        cap >> frame;
        tinted = frame.clone();
        for (int y = 0; y < tinted.rows; y++) {
            for (int x = 0; x < tinted.cols; x++) {
                for (int i = 0; i < 3; i++) {
                    tinted.at<Vec3b>(y , x)[i] = saturate_cast<uchar>(alpha * (tinted.at<Vec3b>(y , x)[i]) + 35);
                }
            }
        }
		imshow("CV Demo 1", tinted);

		if(waitKey(30) >= 0) {
			break;
		}
	    
	    if (up) {
		    alpha += 0.1;
		    if (alpha > 2.975) {
                up = false;
            }
        } else {
            alpha -= 0.1;
            if (alpha < 0.05) {
                up = true;
            }
        }
	}
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
