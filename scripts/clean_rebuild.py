#!/usr/bin/env python

import os
import shutil

def deleteDir(directory):
    try:
        if os.path.exists(directory) and os.path.isdir(directory):
            print("Removing directory '%s'" % (directory))
            shutil.rmtree(directory)
    except OSError as e:
        print ("Error: %s - %s." % (e.filename, e.strerror))
    print()
    
print()

deleteDir("bin")
deleteDir("build")
deleteDir("lib")
deleteDir(".vs")

try:
    import todo
except ImportError:
    pass

os.system("cmake -S . -B build/Debug -DCMAKE_BUILD_TYPE=Debug -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGRAPHICS_API:STRING=OPENGL")
os.system("cmake --build build/Debug --config Debug")
os.system("cmake -S . -B build/Release -DCMAKE_BUILD_TYPE=Release -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGRAPHICS_API:STRING=OPENGL")
os.system("cmake --build build/Release --config Release")