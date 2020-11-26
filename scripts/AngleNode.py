#!/usr/bin/python3

import rospy
from std_msgs.msg import String
import sys
import time

from pymata4 import pymata4


BOARD_PORT = "/dev/ttyACM0"
SERVO_PIN=5

def servo_callback(angle):
    angle_data = float(angle.data) / 1.5;    
    board.servo_write(SERVO_PIN, int(angle_data))


if __name__ == '__main__':
    try:
        #ros node init\
        board = pymata4.Pymata4(BOARD_PORT)
        rospy.init_node("pymata")
        rospy.Subscriber("angle", String, servo_callback)
        board.set_pin_mode_servo(SERVO_PIN)
        rospy.spin()
    except KeyboardInterrupt:
        board.shutdown()
        sys.exit(0)
