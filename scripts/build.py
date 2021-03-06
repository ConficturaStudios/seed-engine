#!/usr/bin/env python

import os
import subprocess

try:
    import todo
except ImportError:
    pass

debug_ret = subprocess.call("cmake --build build/Debug --config Debug")
release_ret = subprocess.call("cmake --build build/Release --config Release")
print("Debug Result: %s" % format(debug_ret))
print("Release Result: %s" % format(release_ret))