#!/usr/bin/env python

import os

try:
    import todo
except ImportError:
    pass

os.system("cmake --build build/Debug --config Debug")
os.system("cmake --build build/Release --config Release")