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

    int alpha = 1;
    bool up = true;
    Mat binarilized;
    Mat tinted;
    namedWindow("CV Demo 1",0);
//    cvSetWindowProperty("CV Demo 1", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

    for(;;) {
        Mat frame;
        cap >> frame;
        cvtColor(frame , tinted , CV_BGR2HSV);
        for (int y = 0; y < tinted.rows; y++) {
            for (int x = 0; x < tinted.cols; x++) {
                tinted.at<Vec3b>(y , x)[0] = alpha;
            }
        }
		imshow("CV Demo 1", tinted);

		if(waitKey(30) >= 0) {
			break;
		}
	    
	    if (up) {
		    alpha += 2;
		    if (alpha > 175) {
                up = false;
            }
        } else {
            alpha -= 2;
            if (alpha < 3) {
                up = true;
            }
        }
	}
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
