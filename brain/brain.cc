#include <iostream>
#include <math.h>
#include <time.h>

#include "robot.hh"
#include "cam.hh"

using namespace std;

void callback(Robot* robot)
{
    cam_show(robot->frame);
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
