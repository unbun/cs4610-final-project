import xml.etree.ElementTree as ET
import math
import xml.dom.minidom
import os
import random

wall_count = 0

def degrees_to_radians(degrees):
    """
    Converts a value in degrees to radians
    """
    return degrees*math.pi/180

def add_include_object(parent, uri_name, name=None, pose=None):
    """
    Adds an xml 'include' subelement following the Gazebo naming convention.
    """
    include = ET.SubElement(parent, 'include')
    uri = ET.SubElement(include, 'uri')
    uri.text = f"model://{uri_name}"
    if name:
        name_xml = ET.SubElement(include, 'name')
        name_xml.text = name
    if pose:
        pose_xml = ET.SubElement(include, 'pose')
        pose_xml.text = pose    

def add_tankbot(parent):
    """
    Adds the default tankbot to the XML parent.
    """
    model = ET.SubElement(parent, 'model')
    model.set('name', 'tankbot0')
    pose_xml = ET.SubElement(model, 'pose')
    pose_xml.text = "-20 0 0 0 0 0"    
    add_include_object(model, "tankbot")
    plugin_xml = ET.SubElement(model, 'plugin')
    plugin_xml.set('name', "tankbot_control")
    plugin_xml.set('filename', "libtank_control_plugin.so")

def add_wall(parent,x,y,z=0, r1=0, r2=0, r3=0):
    """
    Adds a brick wall to the XML parent.
    """
    pose = " ".join(str(x) for x in [x,y,z,r1,r2,r3])
    global wall_count
    add_include_object(parent, "brick_box_3x1x3", f"wall{wall_count}", pose)
    wall_count += 1

def add_aruco_marker(parent, id, x,y,z=0, r1=0, r2=0, r3=0):
    model = ET.SubElement(parent, 'model')
    model.set('name', f'aruco_visual_marker_{id}')
    pose_xml = ET.SubElement(model, 'pose')
    pose_xml.text = " ".join(str(x) for x in [x,y,z,r1,r2,r3])
    add_include_object(model, f'aruco_visual_marker_{id}')

def write_xml_file(xml_data, file_name):
    """
    Writes an xml file with proper indentation & formatting.
    """
    xml_string = xml.dom.minidom.parseString(ET.tostring(xml_data)).toprettyxml()
    with open(file_name, "w") as f:
        f.write(xml_string)

def setup_world(parent):
    """
    Initalizes a default gazebo world.
    """
    world = ET.SubElement(parent, 'world')
    world.set('name', 'default')

    add_include_object(world, 'sun')
    add_include_object(world, 'ground_plane')
    add_include_object(world, 'checkerboard_plane', 'goal', '0 0 0.01 0 0 0')
    add_tankbot(world)

    return world

direction_to_position = {
    "_":(90,0),
    "/":(-45,1),
    "\\":(45,1),
    "|":(0,0)
}

def add_walls(parent, filename):
    """
    Adds all of the walls in a txt file to the XML parent.
    """

    with open(filename) as f:
        walls = f.read()
    walls = walls.split("\n")

    aruco_order = list(range(6))
    random.shuffle(aruco_order)
    aruco_count = 0

    for i,row in enumerate(walls, -len(walls)//2):
        for j, val in enumerate(row, -len(walls)//2):
            if val in direction_to_position and (i or j):
                angle, shift = direction_to_position[val]
                add_aruco_marker(parent, aruco_order[aruco_count], i*2-shift, j*2, r3=degrees_to_radians(angle))
                aruco_count = aruco_count + 1

if __name__ == "__main__":
    sdf = ET.Element('sdf')
    sdf.set('version', '1.5')
    world = setup_world(sdf)

    current_dir = os.path.split(__file__)[0]
    add_walls(world, os.path.join(current_dir, "final.txt"))
    worlds_dir = "../worlds/"
    write_xml_file(sdf, os.path.join(worlds_dir, "custom_world.world"))