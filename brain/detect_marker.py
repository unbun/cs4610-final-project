import cv2
from cv2 import aruco
import numpy as np

aruco_dict = aruco.getPredefinedDictionary(aruco.DICT_6X6_50)
parameters = aruco.DetectorParameters_create()

def get_center(corner):
    return np.mean(corner[0], axis=0)

def get_distance(p1, p2):
    dx = p1[0] - p2[0]
    dy = p1[1] - p2[1]

    return np.sqrt(dx**2 + dy**2)

def get_size(corner):
    corner = corner[0]
    return max(get_distance(corner[0], corner[2]), get_distance(corner[1], corner[3]))

def detect_markers(frame):

    corners, ids, _ = aruco.detectMarkers(image=frame, dictionary=aruco_dict, parameters=parameters)

    return {
        id[0]: [get_center(corner), get_size(corner)]
        for id, corner in zip(ids, corners)
    }


if __name__ == "__main__":
    img_file = "/home/nikhil/Pictures/test_aruco_image.png"
    img = cv2.imread(img_file)
    id_to_marker_info = detect_markers(img)
    print(id_to_marker_info)