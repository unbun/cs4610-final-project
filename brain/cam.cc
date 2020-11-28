#include <vector>
#include <iostream>
#include <map>
#include <math.h>
#include <algorithm>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/aruco.hpp>

#include "cam.hh"

using namespace cv;
using namespace std;

/*
    Note: The OpenCV code is based off of the OpenCV tutorials
    that are linked in the README 
*/

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

/*
Given the marker corners, returns the center.
*/
Posn get_marker_center(std::vector<cv::Point2f> markerCorners) {
    Posn c = Posn(0,0);
    for (int j = 0; j < markerCorners.size(); j++) {
        c.first += markerCorners.at(j).x;
        c.second += markerCorners.at(j).y;
    }
    c.first = c.first/4;
    c.second = c.second/4;

    return c;

}

/*
Given two points, returns the distance between them.
*/
float distance_formula(cv::Point2f p1, cv::Point2f p2) {
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;
    return sqrt(pow(dx,2)+pow(dy,2));
}

/*
Given the marker corners, returns the diagnol size of the marker.
*/
float get_marker_size(std::vector<cv::Point2f> markerCorners) {
    return max(distance_formula(markerCorners.at(0), markerCorners.at(2)),
                distance_formula(markerCorners.at(1), markerCorners.at(3)));
}

cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_50);
cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();

/*
Given a cv::mat returns a map of {marker_id: (marker_center, marker_size)}.
*/
map<int, pair<Posn, float>> detect_markers(Mat frame) {
    map<int, pair<Posn, float>> marker_id_to_info;

    if (frame.size().width < 1) {
        return marker_id_to_info;
    }
    cv::Mat greyMat;
    cv::cvtColor(frame, greyMat, cv::COLOR_BGR2GRAY);

    std::vector<int> markerIds;
    std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
    cv::aruco::detectMarkers(greyMat, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);
    cv::Mat outputImage = greyMat.clone();
    cv::aruco::drawDetectedMarkers(outputImage, markerCorners, markerIds);

    for (int i = 0; i < markerIds.size(); i++) {
        marker_id_to_info.insert(
            pair<int, pair<Posn, int>>(
                markerIds.at(i),
                pair<Posn, int>(
                    get_marker_center(markerCorners.at(i)),
                    get_marker_size(markerCorners.at(i))
                )
            )
        );
    }

    if (markerIds.size() > 0) {
        imshow("camera", outputImage);
    } else {
        imshow("camera", greyMat);
    }
    cv::waitKey(1);
    return marker_id_to_info;
}


/*
Given a translation vector, calculates the 3D distance it is away.
*/
float calculate_distance(cv::Vec3d translation_vector) {
    float distance = 0;
    for (int i = 0; i < 3; i++) {
        distance = distance + pow(translation_vector[0],2);
    }
    return sqrt(distance);
}

/*
Given an image and calibration parameters returns a map of {marker_id: (distance, rotation_vector)}.
Note: Read the calibration parameters from a file, after manually calibrating
*/
map<int, pair<float, cv::Vec3d>> get_real_world_marker_position(
    Mat frame, cv::Mat cameraMatrix, cv::Mat distCoeffs) {

    double MARKER_SIZE = 1; // change as necessary

    cv::Mat greyMat;
    cv::cvtColor(frame, greyMat, cv::COLOR_BGR2GRAY);

    std::vector<int> markerIds;
    std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
    cv::aruco::detectMarkers(greyMat, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);

    map<int, pair<float, cv::Vec3d>> real_world_marker_positions;

    std::vector<cv::Vec3d> rvecs, tvecs;
    cv::aruco::estimatePoseSingleMarkers(markerCorners, MARKER_SIZE, cameraMatrix, distCoeffs, rvecs, tvecs);

    for (int i = 0; i < markerIds.size(); i++) {
        real_world_marker_positions.insert(
            pair<int, pair<float, cv::Vec3d>>(
                markerIds.at(i),
                pair<float, cv::Vec3d>(
                    calculate_distance(tvecs.at(i)),
                    rvecs.at(i)
                )
            )
        );
    }

    return real_world_marker_positions;

}
