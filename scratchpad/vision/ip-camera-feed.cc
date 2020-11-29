#include "opencv2/opencv.hpp"
#include "opencv2/aruco.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "iostream"

int main(int, char**) {

		cv::VideoCapture inputVideo;
		inputVideo.open("https://172.20.10.11:8080/video");
		cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
		while (inputVideo.grab()) {
			cv::Mat image, imageCopy, imageOut;
			inputVideo.retrieve(image);
			image.copyTo(imageCopy);
			image.copyTo(imageOut);
			std::vector<int> ids;
			std::vector<std::vector<cv::Point2f> > corners;
			cv::aruco::detectMarkers(image, dictionary, corners, ids);
			// if at least one marker detected
			if (ids.size() > 0)
				cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);

			cv::resize(imageCopy, imageOut, cv::Size(), 0.5, 0.5);
			cv::imshow("out", imageOut);
			char key = (char) cv::waitKey(10);
			if (key == 27)
				break;
		}
}
