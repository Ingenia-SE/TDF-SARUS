#!/usr/bin/env python3
#
#  ADD DESCRIPTION
#
#
#

import numpy as np
import matplotlib.pyplot as plt
import sys

import rospy
from geometry_msgs.msg import PolygonStamped
from geometry_msgs.msg import PoseStamped
from nav_msgs.msg import Path

from skimage.draw import polygon

from cpp_algorithms import darp, stc, bcd, wavefront
from cpp_algorithms import get_drone_map, get_random_coords
from cpp_algorithms import get_all_area_maps, plot, imshow, imshow_scatter
from cpp_algorithms.darp.darp_helpers import get_assigned_count
from cpp_algorithms.coverage_path.pathing_helpers import has_isolated_areas
from cpp_algorithms import dist_fill


def cambiaIntervalo (N, a0, b0, aF, bF):
    return aF + (bF - aF)*(N - a0)/(b0 - a0)

def alg2gazebo (point, Yindexes, Xindexes, north, south, east, west):
    newPoint = [[[cambiaIntervalo(drone[0], 0, Xindexes-1, west, east), cambiaIntervalo(drone[1], 0, Yindexes-1, south, north), 15] for drone in drones] for drones in point]
    return newPoint
'''
def gazebo2alg (point):
    newPoint = [[[cambiaIntervalo(coord, -100, 100, 0, 31) for coord in drone] for drone in drones] for drones in point]
    return newPoint
'''
def makePolygon (points, width=10):	#Polygon to bitmap with pixels of ~ 10x10 m
    # Acotamos el cuadrado
    north = points[0].y
    south = points[0].y
    east = points[0].x
    west = points[0].x
    for point in points:
        if point.y > north:
            north = point.y
        if point.y < south:
            south = point.y
        if point.x > east:
            east = point.x
        if point.x < west:
            west = point.x
    # Dividimos en grupos de 10
    Ysize = north - south
    Yindexes = np.floor(Ysize/width)		#N of divisions
    Yindexes = np.int8(Yindexes)
    Ywidth = Ysize/Yindexes			#exact width of divisions
    Xsize = north - south
    Xindexes = np.floor(Xsize/width)
    Xindexes = np.int8(Xindexes)
    Xwidth = Xsize/Xindexes
    y = [];
    x = [];
    for point in points:
        y.append(np.floor(cambiaIntervalo(point.y, south, north, 0, Yindexes)))
        x.append(np.floor(cambiaIntervalo(point.x, west, east, 0, Xindexes)))

    print("Square width: " + str(Ysize)+"x"+str(Xsize))
    print("N of squares: " + str(Yindexes)+"x"+str(Xindexes))
    map_x, map_y = polygon(y,x)
    area_map =np.zeros((Yindexes, Xindexes), dtype=np.int8)
    area_map[map_y, map_x]=1
    area_map=area_map-1
    return area_map, Yindexes, Xindexes, north, south, east, west

def appendtoPath(coordinates, to_C2):
    msg = PoseStamped()
    # Also possible with numpy
    # Separate the position in its coordinates
    msg.pose.position.x=coordinates[0]
    msg.pose.position.y=coordinates[1]
    if to_C2 == True:
        msg.pose.position.z=0.0 #coordinates[2]
        msg.header.frame_id = 'map'
    else:
        msg.pose.position.z=10.0 #coordinates[2]
        msg.header.frame_id = 'world'
    return msg

def poly_cb(data):
    global base_polygon
    base_polygon=np.array(data.polygon.points)
    rospy.loginfo('Polygon received')
    global update
    update = True


def n_cb(ndrones):
    global n
    global pubC2
    global pubAerostack
    n=int(data)
    for i in range(n-len(pubAerostack)):
        Atopic='/drone11' + str(i+1) + '/motion_reference/path'
        pubAerostack.append(rospy.Publisher(Atopic, Path, queue_size=10))
        C2topic='/mapviz/path'+str(i+1)
        pubC2.append(rospy.Publisher(C2topic, Path, queue_size=10))

########################
### Program Start ######
########################
rospy.init_node('mission_planner', anonymous=True) #Create node

plot=0
if len(sys.argv)>1:
    plot=sys.argv[1]

pubC2 = []
pubAerostack = []
pubC2.append(rospy.Publisher('/mapviz/path1', Path, queue_size=10))
pubAerostack.append(rospy.Publisher('/drone111/motion_reference/path', Path, queue_size=10))

n=1



# Frequency of the sleep
rate = rospy.Rate(0.2) #0.2 Hz -> 5s
rospy.loginfo('Mision Planner ready')

# Datos de Interfaz:


old_polygon = np.empty(2)

#rospy.Subscriber('/interfaz/poligono', Int32MultiArray, poly_cb)
rospy.Subscriber('/mapviz/polygon', PolygonStamped, poly_cb)


while True:
    if 'update' in vars() and update == 1:
        rospy.loginfo('Recalculating path...')
        area_map, Yindexes, Xindexes, north, south, east, west = makePolygon(base_polygon) #Make bitmap from polygon
        start_points = get_random_coords(area_map, n) # Random start coordinates
        A, losses = darp(300, area_map, start_points, pbar=True) # Area division algorithm
        drone_maps = [get_drone_map(A,i) for i in range(n)] #assign a map for each drone
        coverage_paths = [bcd(drone_maps[i],start_points[i]) for i in range(n)]  #Calculate the routes for each drone
        old_polygon = base_polygon

        if plot:
          imshow(A,1,4,1, figsize=(20,5))
          imshow_scatter(start_points,color="black")
          dist_maps = [dist_fill(drone_maps[i],[start_points[i]]) for i in range(n)]
          [imshow(dist_maps[i],1,4,i+2) for i in range(n)];

          for i in range(n):
            imshow(dist_maps[i],1,4,i+2)
            plot(coverage_paths[i],color="white",alpha=0.6)
            end_point = coverage_paths[i][-1]
            imshow_scatter(start_points[i], color="green")
            imshow_scatter(end_point, color="red")

          plt.show()

        #################################################
        ### meter topic salida a aerostack drone111/#####
        #################################################
        coverage_path_gazebo = alg2gazebo(coverage_paths, Yindexes, Xindexes, north, south, east, west)


        for drone in range(n):        # Number of drones

            C2Path= Path()
            aerostackPath= Path()
            for point in coverage_path_gazebo[n]:
                try:
                    C2Path.poses.append(appendtoPath(point, True))
                    aerostackPath.poses.append(appendtoPath(point, False))
                    #rospy.loginfo('Drone '+ str(drone+1) + ' = ' + str(coverage_path_gazebo[drone][pos]))
                except:
                    rospy.logerror('Problem with Drone ', drone+1, ' path')
            pubC2[drone].publish(C2Path)
            pubAerostack[drone].publish(aerostackPath)


        update = False

####################################
#### IMPLEMENTAR VUELTA A CASA #####
####################################


