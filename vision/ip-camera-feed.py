import cv2
import numpy as np
#import cv2.aruco as aruco

"""
IP camera app google play: https://play.google.com/store/apps/details?id=com.pas.webcam
connect to IP camera: https://stackoverflow.com/questions/49978705/access-ip-camera-in-python-opencv

Gets video feed from IP camera app. Tested with android.
Haven't implemented the aruco detection yet
"""

vid = cv2.VideoCapture('IP URL')  # replace IP URL with given url in app

while (True):
    ret, frame = vid.read()
    #gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)  # converts image to grayscale
    #aruco_dict = aruco.Dictionary_get(aruco.DICT_6X6_250)

    cv2.imshow('frame', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

vid.release()
