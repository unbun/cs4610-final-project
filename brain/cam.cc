#include <vector>
#include <iostream>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/aruco.hpp>

#include "cam.hh"

using namespace cv;
using namespace std;

void
cam_init()
{
    namedWindow("camera", 1);
    cout << "named a window" << endl;
}

void cam_show(Mat frame)
{

    if (frame.size().width > 0) {
        imshow("camera", frame);
        cv::waitKey(1);
    }

}

cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_1000);
cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
void detect_markers(Mat frame) {
    if (frame.size().width < 1) {
        return;
    }
    cv::Mat greyMat;
    cv::cvtColor(frame, greyMat, cv::COLOR_BGR2GRAY);
    
    std::vector<int> markerIds;
    std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
    cv::aruco::detectMarkers(greyMat, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);
    cv::Mat outputImage = greyMat.clone();
    cv::aruco::drawDetectedMarkers(outputImage, markerCorners, markerIds);
    if (markerIds.size() > 0) {
        imshow("camera", outputImage);
    } else {
        imshow("camera", greyMat);
    }
    cv::waitKey(1);
}
