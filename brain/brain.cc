#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <map>
#include <fstream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>

#include "cam.hh"

using namespace std;
using std::vector;

map<int, pair<Posn, float>> marker_id_to_info;
vector <int> IDs{6, 5, 4, 3, 2, 1, 0};


void print_map() {
    map<int, pair<Posn, float>>::iterator itr; 
    cout << "\nDetected Markers\n";
    for (itr = marker_id_to_info.begin(); itr != marker_id_to_info.end(); ++itr) { 
        printf("ID: %d\n\tSize: %.2f\n\tPos: (%.2f, %.2f)\n", 
        itr->first, itr->second.second, itr->second.first.first, itr->second.first.second);
    } 
}

bool detected_target_id(int target_id) {
	
	map<int, pair<Posn, float>>::iterator itr; 
    for (itr = marker_id_to_info.begin(); itr != marker_id_to_info.end(); ++itr) { 
		if (itr->first == target_id)	
		{
			return true;
		}
    } 
	
	return false;
}

string callback(cv::Mat frame)
{
	marker_id_to_info = detect_markers(frame);
    //print_map();

	// current target aruco ID
	float target_id = IDs.back();
	cout << "target_id: " << target_id <<endl;

	// if the ID is not detected keep rotating
	if (!detected_target_id(target_id))
	{
		cout << "not detected: turning" << endl;
		
		//robot->set_vel(-1, -1);
	}

	Posn target_pos = marker_id_to_info[target_id].first; // target position
	float target_diag = marker_id_to_info[target_id].second; // target aruco diagonal length

	// if  the target diagonal size is more than a threshold, pop the target ID and go to the next one	
	if (target_diag > 300)
	{
		IDs.pop_back();
	}

	printf("target pos: %.2f, %.2f)\n", target_pos.first, target_pos.second);
	// go to ID 1
	//cout << "dim: " <<  target_pos.first - robot->frame.size().width/2 << endl;
	//cout << "width: " << robot->frame.size().width << endl;
	if (target_pos.first - frame.size().width/2 > 10)
	{
		cout << "turing right" << endl;
		//robot->set_vel(1, -1);
		return "1 -1";
	}

	if (target_pos.first - frame.size().width/2 < -10)
	{
		cout << "turning left" << endl;
		return "-1 1";
		//robot->set_vel(-1, 1);
		/* remove the FIFO */

	}

	else
	{
		cout << "found: going straight" << endl;

		return "2 2";

		//robot->set_vel(2, 2);

	}
}

int
main(int argc, char* argv[])
{
	cv::VideoCapture inputVideo;
	inputVideo.open("https://172.20.10.11:8080/video");
	
	cv::Mat frame;

    cout << "here1" <<endl;
    cam_init();

	int fd; 
  
    // FIFO file path 
    char * myfifo = "/tmp/myfifo"; 
  
    // Creating the named file(FIFO) 
    // mkfifo(<pathname>, <permission>) 
    mkfifo(myfifo, 0666); 

    while (inputVideo.grab()) 
    { 
		inputVideo.read(frame);
        // Open FIFO for write only 
        fd = open(myfifo, O_WRONLY); 
  
        // Take an input arr2ing from user. 
        // 80 is maximum length 
		std::string str = callback(frame);
		char* arr2 = new char[str.size() + 1];
		std::copy(str.begin(), str.end(), arr2);
		arr2[str.size()] = '\0';
  
        // Write the input arr2ing on FIFO 
        // and close it 
        write(fd, arr2, strlen(arr2)+1); 
        close(fd); 
  }
    //Robot robot(argc, argv, callback);
    //robot.do_stuff();

    return 0;
}
