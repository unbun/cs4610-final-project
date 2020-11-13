#ifndef CAM_HH
#define CAM_HH

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include<vector>
typedef std::pair<int, int> Posn; 
void cam_init();
void cam_show(cv::Mat);

#endif
