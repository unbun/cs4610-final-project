#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <map>

#include "robot.hh"
#include "cam.hh"

using namespace std;
using std::vector;

map<int, pair<Posn, float>> marker_id_to_info;
vector <int> IDs{5, 4, 3, 2, 1, 0};  // aruco target IDs

/**
* Function for printing the map of detected aruco markers and their 
* properties.
*/
void print_map() {
    map<int, pair<Posn, float>>::iterator itr; 
    cout << "\nDetected Markers\n";
    for (itr = marker_id_to_info.begin(); itr != marker_id_to_info.end(); ++itr) { 
        printf("ID: %d\n\tSize: %.2f\n\tPos: (%.2f, %.2f)\n", 
        itr->first, itr->second.second, itr->second.first.first, itr->second.first.second);
    } 
}

/**
* Function that returns a true or false value based on the detection of the 
* target_id argument input.
*/
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

/**
* Robot callback
*/
void callback(Robot* robot)
{
	// check if all targets have been visited (empty target ID array)
	if (IDs.empty())
	{
		cout << "=========================" << endl;
		cout << "==== ALL IDs VISITED ====" << endl;
		cout << "=========================" << endl;
		return;
	} 

    marker_id_to_info = detect_markers(robot->frame);
    //print_map();

	float target_id = IDs.back();  // current aruco target ID
	cout << "target_id: " << target_id <<endl;

	// if the ID is not detected keep rotating
	bool detected = detected_target_id(target_id);
	if (!detected)
	{	
		cout << "TURNING TO FIND MARKER" << endl;
		robot->set_vel(-1, 1);
	}

	bool straight_flag = false;  // on if set to go straight
	bool turning_flag = false;  // on if set to turn
	Posn target_pos = marker_id_to_info[target_id].first; // target position
	float target_diag = marker_id_to_info[target_id].second; // target aruco diagonal length

	// if  the target diagonal size is more than a threshold, pop the target ID
	// and set next target ID
	// the target has now been visited
	if (target_diag > 300)
	{
		IDs.pop_back();
	}

	printf("target coordinates: (%.2f, %.2f)\n", target_pos.first, target_pos.second);
	cout << "aruco center to frame center distance: " <<  target_pos.first - robot->frame.size().width/2 << endl;

	// if the target ID is detected then center it on the frame and go straight
	if (detected==1)
	{
		// if the the horizontal coordinate of the center of the target marker 
		// is inside a certain threshold, set to go straight
		if (((target_pos.first - robot->frame.size().width/2 < 20) && target_pos.first - robot->frame.size().width/2 > -20))
		{
			cout << "SETTING TO STRAIGHT" << endl;
			turning_flag = false;
			straight_flag = true;
			robot->set_vel(-1, 1);
		} 
		
		// if the horizontal coordinate of the center of the target marker is 
		// outside a certain threshold, set to turn
		if (((target_pos.first - robot->frame.size().width/2 > 80) || target_pos.first - robot->frame.size().width/2 < -80))
		{
			turning_flag = true;
			straight_flag = false;
			cout << "TURNING TO FIND MARKER" << endl;
		}

		// turn
		if (turning_flag==1)
		{
			robot->set_vel(-1, 1);
		}
		// go straight
		if (straight_flag==1)
		{
			robot->set_vel(2, 2);
		}
	}
}

int
main(int argc, char* argv[])
{
    cam_init();

    cout << "making robot" << endl;
    Robot robot(argc, argv, callback);
    robot.do_stuff();

    return 0;
}