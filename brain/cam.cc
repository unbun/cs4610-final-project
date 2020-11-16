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

vector<Posn> get_marker_centers(std::vector<std::vector<cv::Point2f>> markerCorners) {
    vector<Posn> centers;
    for (int i = 0; i < markerCorners.size(); i++) {
        Posn c = Posn(0,0);
        for (int j = 0; j < markerCorners.at(i).size(); j++) {
            c.first += markerCorners.at(i).at(j).x;
            c.second += markerCorners.at(i).at(j).y;
        }
        c.first = c.first/4;
        c.second = c.second/4;
        centers.push_back(c);
    }

    return centers;

}

cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_50);
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
    vector<Posn> centers = get_marker_centers(markerCorners);
    for (int i = 0; i < centers.size(); i++) {
        printf("\nMarker: %d\n\tx: %f\n\ty: %f\n", markerIds.at(i), centers.at(i).first, centers.at(i).second);
    }

    if (markerIds.size() > 0) {
        imshow("camera", outputImage);
    } else {
        imshow("camera", greyMat);
    }
    cv::waitKey(1);
}
