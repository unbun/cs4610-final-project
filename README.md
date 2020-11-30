
# Vision-Guided Robotic Navigation in Modular 3D Space

Our project goal is to develop a physical robot and control program that can precisely navigate a modular, 3D environment. Given an ordered list of target ids, the robot’s goal will be to visit all targets in the environment. Using a mounted phone as a camera, the robot will detect the visual targets and begin navigating towards the first target. The robot will repeat the cycle of detection and navigation until all targets have been visited.

# Running the project

## Gazebo
1. If you wish the modify the world, update the /mazegen/final.txt
2. In /mazegen, run: ```python3 gen_world.py```
3. Compile all the code, run: ```make all```
4. In a new terminal, run gazebo world: ```./run_world```
5. In a new terminal, run inside /brain: ```./brain```
6. Watch the demo execute in gazebo simulation

## Real World

### Updating Python Paths in real_world_brain.py
1. Update sys.path (line 2) to the local system package of python2.7 opencv
2. Update the correct USB port (line 59) of the mBot ranger. You can use Arduino IDE or terminal to find the correct port number
3. Update video capture input (line 61) to the URL of the IP Camera

### Updating mbot firmware
1. Plug in mBot ranger into computer and open up mBlock app. Upload the latest firmware for the Auriga of the mbot Ranger ([Linked here](https://github.com/Makeblock-official/Makeblock-Libraries/blob/master/examples/Firmware_for_Auriga/Firmware_for_Auriga.ino))

### Running the script
1. Run the python script in /brain: ```sudo python real_world_brain.py```

## Bonus Point: Gazebo World Generation

The most helpful functions are:

- setup_world: Given an XML parent, this function initalizes a default gazebo world with a checkerboard, sun, and tankbot.
- add_walls: Given an XML parent, and a txt file, populates the XML object with gazebo walls.

Generating a gazebo worldfile can be a bit tricky. This code simplifies this process, by providing helpful functions to set up a world file, and even generate one from a txt file.

## Bonus Point: Manually controlled Gazebo robot

`brain-input.cc` contains a simulation setup and manual control program for a simple Gazebo tankbot. To change the velocity of the robot, hold down the corresponding key, and the Gazebo robot will follow that command. Replace `brain.cc` with this file and run `make` to use it. The command keys are as setup as following:

- `w`: Forward
- `s`: Reverse
- `a`: Veer Left
- `d`: Veer right
- `q`: Spin left
- `e`: Spin right
- `Space`: Stop
- `~`: Exit program

# References
- https://github.com/joselusl/aruco_gazebo [For Aruco Models]
- https://stackoverflow.com/questions/10344246/how-can-i-convert-a-cvmat-to-a-gray-scale-in-opencv
- https://docs.opencv.org/master/d5/dae/tutorial_aruco_detection.html [For Aruco Detection]
- https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed [For keyboard control]
- https://github.com/xeecos/python-for-mbot [For mBot Ranger python commands (mbot.py)]
