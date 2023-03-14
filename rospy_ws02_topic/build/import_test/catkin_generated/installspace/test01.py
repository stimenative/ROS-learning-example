#!/usr/bin/env python3

import rospy
import os
import sys

import constDemo01


path = os.path.abspath("../..")
sys.path.insert(0,path)
print(sys.path)
print(path)

import time_test.scripts.time_action as ta
print("123lll",ta.rightnow.to_sec())