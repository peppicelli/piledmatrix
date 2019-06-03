import os
import sys
# Add the current path to the system path. 
# The goal is to be able to import the objects defined in the c++ shared lib.
sys.path.append(os.path.dirname(__file__))

from _piledmatrix import *
