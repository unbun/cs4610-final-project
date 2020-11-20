#ifndef CAM_HH
#define CAM_HH

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include<vector>
#include<map>

typedef std::pair<float, float> Posn; 
void cam_init();
void cam_show(cv::Mat);
std::map<int, std::pair<Posn, float>> detect_markers(cv::Mat frame);
#endif
