#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <map>

#include "robot.hh"
#include "cam.hh"

using namespace std;

map<int, pair<Posn, float>> marker_id_to_info;

void print_map() {
    map<int, pair<Posn, float>>::iterator itr; 
    cout << "\nDetected Markers\n";
    for (itr = marker_id_to_info.begin(); itr != marker_id_to_info.end(); ++itr) { 
        printf("ID: %d\n\tSize: %.2f\n\tPos: (%.2f, %.2f)\n", 
        itr->first, itr->second.second, itr->second.first.first, itr->second.first.second);
    } 
}

void callback(Robot* robot)
{
    marker_id_to_info = detect_markers(robot->frame);
    print_map();

    robot->set_vel(0.0, 0.0);
}

int
main(int argc, char* argv[])
{
    cout << "here1" <<endl;
    cam_init();

    cout << "making robot" << endl;
    Robot robot(argc, argv, callback);
    robot.do_stuff();

    return 0;
}
