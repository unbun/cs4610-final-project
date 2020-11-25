#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <map>

#include "robot.hh"
#include "cam.hh"

using namespace std;
using std::vector;

float maxSpeed = 10.0f;
float turnSpeed = 7.0f;
float minSpeed = -10.0f;

int FORWARD = 0;
int BACKWARDS = 1;
int LEFT = 2;
int RIGHT = 3;
int driveDir = 0;

// void moveInDir(int newDir) {
// 	if(driveDir == FORWARD){
// 		if(newDir == )
// 	}
// }

void callback(Robot* robot)
{
	//https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed
	// stty raw will read stdin without needing to hit enter
    system("stty raw");
    printf("input-> ");

    char ch = getchar();

    if(ch=='~') {         // kill on '~'
        system("stty cooked");
        exit(0);
    }

    // stty raw doesn't use the new line character correctly
    system("stty cooked");
    printf("\nyou pressed %c",ch);
    if(ch == 'w') {
    	printf("\tFORWARD\n");
    	robot->set_vel(maxSpeed, maxSpeed);

    } else if(ch == 's') {
    	printf("\tBACKWARDS\n");
    	robot->set_vel(minSpeed, minSpeed);

    } else if(ch == 'a') {
    	printf("\tLEFT\n");
    	robot->set_vel(turnSpeed, 0);

    } else if(ch == 'd'){
    	printf("\tRIGHT\n");
    	robot->set_vel(0, turnSpeed);
    } else {
    	printf("\n");
    }
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
