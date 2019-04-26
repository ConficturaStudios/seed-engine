#!/usr/bin/env python

import os
import re

print("Checking project for TODO statements...")

# The file to write the to do lists to
todo_file = open("ToDoLists.txt", "w")

# The pattern to check for in .cpp, .hpp, .c, and .h files
cpp_todo_pattern = "^.*//(?:\\s*)?TODO:\\s*(.*)$"

# Directories to skip
exclude_dirs = set(["extern", ".git", ".vs", "bin", "build", "ci", "lib", "scripts", "spike", "data", "docs"])

# Walk though the current directory
for subdir, dirs, files in os.walk(os.getcwd()):
    # Skip excluded files
    dirs[:] = [d for d in dirs if d not in exclude_dirs]
    # Iterate thorugh all files
    for file in files:
        # Get filename
        filename = os.fsdecode(file)
        # Check the file type
        if filename.endswith(".cpp") or filename.endswith(".hpp"): 
            # Get the path relative to the current working directory
            rel_path = os.path.relpath(os.path.join(subdir, file), os.getcwd())
            # Gets the highest level directory in the relative path
            project_dir = rel_path.split(os.sep)[0].upper()
            # Read the file
            with open(rel_path) as fp:
                # The current line
                line = fp.readline()
                # The current line number
                count = 1
                # Iterate through every line
                while line:
                    # Check if the line matches the pattern
                    match_obj = re.match(cpp_todo_pattern, line, re.M)
                    # If a match exists
                    if match_obj:
                        # Extract the to do statement from the pattern and print it
                        todo_info = "{0}: [{1} line {2}]: {3}".format(project_dir, filename, count, match_obj.group(1))
                        # Prints the information to the console
                        print(todo_info)
                        # Writes the information to the ToDoLists.txt file
                        todo_file.write(todo_info + '\n')
                    # Read the next line
                    line = fp.readline()
                    # Increase the line count
                    count += 1
            continue
        else:
            continue
# Close the open file
todo_file.close()
print()