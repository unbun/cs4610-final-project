#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <map>
#include <gazebo/msgs/msgs.hh>

#include "robot.hh"
#include "cam.hh"

using namespace std;
using std::vector;

float maxSpeed = 10.0f;
float turnSpeed = 7.0f;
float minSpeed = -10.0f;

// BUGFIX: the actual set_vel call happens when you'd expect it to,
// but the vel_cmd Publisher node seems to be getting its message after a small delay _sometimes_

void drive(Robot* robot, char cmd) {
	switch(cmd){
		case 'w': 
			printf(":\tforward\n");
	    	robot->set_vel(maxSpeed, maxSpeed); 
	    	break;

    	case 's':
			printf(":\treverse\n");
	    	robot->set_vel(minSpeed, minSpeed); 
	    	break;

	    case ' ':
			printf(":\tstop\n");
	    	robot->set_vel(0.0, 0.0); 
	    	break;

	    case 'a':
			printf(":\tleft\n");
	    	robot->set_vel(0.0, turnSpeed); 
	    	break;

	    case 'd':
			printf(":\tright\n");
	    	robot->set_vel(turnSpeed, 0.0); 
	    	break;

	    case 'q':
			printf(":\trspin left\n");
	    	robot->set_vel(-turnSpeed, turnSpeed); 
	    	break;

	    case 'e':
			printf(":\trspin right\n");
	    	robot->set_vel(turnSpeed, -turnSpeed); 
	    	break;

	    default:
	    	printf("\n");
	    	break;
	}
}

void callback(Robot* robot)
{
	//https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed
	// stty raw will read stdin without needing to hit enter
    system("stty raw");
    printf("input-> ");

    char ch = getchar();

    if(ch=='~') {         // kill on '~'
        system("stty cooked");
        exit(0); // /BUGFIX: maybe do this more gracefully?
    }

    // stty raw doesn't use the new line character correctly
    system("stty cooked");
	drive(robot, ch);
    return;
}

int
main(int argc, char* argv[])
{
    cout << "here1" <<endl;
    cam_init();

    cout << "making robot" << endl;
    Robot robot(argc, argv, callback);

    robot.do_stuff();

    system("stty cooked"); 
    return 0;
}
