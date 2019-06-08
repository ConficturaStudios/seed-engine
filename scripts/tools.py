#!/usr/bin/env python

import os
import subprocess
import re
import argparse

print()
print("NOTICE: This tool should only be run with the project root as the working directory")
print()

def create_class(args):
    from string import Template
    # The header file
    hpp_file = open("core/include/" + args.name.lower().capitalize() + ".hpp", "w")
    # The source file
    cpp_file = open("core/src/" + args.name.lower().capitalize() + ".cpp", "w")
    # The test file
    test_file = open("core/test/test_" + args.name.lower() + ".cpp", "w")
    print("Creating class " + args.name.lower().capitalize() + "...")
    hpp_template = open(os.path.dirname(os.path.realpath(__file__)) + "/templates/header_template.txt", "r")
    cpp_template = open(os.path.dirname(os.path.realpath(__file__)) + "/templates/source_template.txt", "r")
    test_template = open(os.path.dirname(os.path.realpath(__file__)) + "/templates/test_template.txt", "r")
    
    hpp_src = Template(hpp_template.read())
    cpp_src = Template(cpp_template.read())
    test_src = Template(test_template.read())

    upper_name = args.name.upper()
    class_name = args.name.lower().capitalize()
    test_name = args.name.lower()

    d={ "UPPER_NAME":upper_name, "CLASS_NAME":class_name, "TEST_NAME":test_name }

    hpp_result = hpp_src.substitute(d)
    cpp_result = cpp_src.substitute(d)
    test_result = test_src.substitute(d)

    hpp_template.close()
    cpp_template.close()
    test_template.close()

    hpp_file.write(hpp_result)
    cpp_file.write(cpp_result)
    test_file.write(test_result)

    hpp_file.close()
    cpp_file.close()
    test_file.close()

def run_todo(args):
    try:
        import todo
    except ImportError:
        pass

def build_project(args):
    print("Building project...")
    if args.clean:
        try:
            from clean_rebuild import debug_ret, release_ret
            if args.exec:
                check_debug = not args.release
                if args.release:
                    if release_ret == 0:
                        print()
                        print("Executing program release binaries.")
                        print()
                        subprocess.call("./bin/Release/seed-engine-editor.exe")
                    else:
                        print()
                        print("Could not run program due to compilation error. Checking for Debug success.")
                        print()
                        check_debug = True
                if args.debug and check_debug:
                    if debug_ret == 0:
                        print()
                        print("Executing program debug binaries.")
                        print()
                    else:
                        print()
                        print("Could not run program due to compilation error. Exiting.")
                        print()
                        subprocess.call("./bin/Debug/seed-engine-editor.exe")
                        return
            if args.test:
                check_debug = not args.release
                if args.release:
                    if release_ret == 0:
                        print()
                        print("Executing program release tests.")
                        print()
                        subprocess.call("./bin/Release/seed-engine-core-tests.exe")
                    else:
                        print()
                        print("Could not run tests due to compilation error. Checking for Debug success.")
                        print()
                        check_debug = True
                if args.debug and check_debug:
                    if debug_ret == 0:
                        print()
                        print("Executing program debug tests.")
                        print()
                    else:
                        print()
                        print("Could not run tests due to compilation error. Exiting.")
                        print()
                        subprocess.call("./bin/Debug/seed-engine-core-tests.exe")
                        return
        except ImportError:
            pass
    else:
        try:
            from build import debug_ret, release_ret
            if args.exec:
                check_debug = not args.release
                if args.release:
                    if release_ret == 0:
                        print()
                        print("Executing program release binaries.")
                        print()
                        subprocess.call("./bin/Release/seed-engine-editor.exe")
                    else:
                        print()
                        print("Could not run program due to compilation error. Checking for Debug success.")
                        print()
                        check_debug = True
                if args.debug and check_debug:
                    if debug_ret == 0:
                        print()
                        print("Executing program debug binaries.")
                        print()
                    else:
                        print()
                        print("Could not run program due to compilation error. Exiting.")
                        print()
                        subprocess.call("./bin/Debug/seed-engine-editor.exe")
                        return
                        
            if args.test:
                check_debug = not args.release
                if args.release:
                    if release_ret == 0:
                        print()
                        print("Executing program release tests.")
                        print()
                        subprocess.call("./bin/Release/seed-engine-core-tests.exe")
                    else:
                        print()
                        print("Could not run tests due to compilation error. Checking for Debug success.")
                        print()
                        check_debug = True
                if args.debug and check_debug:
                    if debug_ret == 0:
                        print()
                        print("Executing program debug tests.")
                        print()
                    else:
                        print()
                        print("Could not run tests due to compilation error. Exiting.")
                        print()
                        subprocess.call("./bin/Debug/seed-engine-core-tests.exe")
        except ImportError:
            pass

def fill_files(args):

    from string import Template

    print("Filling empty files...")
    print()
    print("Filling empty header files...")
    print()
    for subdir, dirs, files in os.walk("core/include"):
        for file in files:
            ext = os.path.splitext(file)[-1].lower()
            if ext == ".hpp" and os.stat(os.path.relpath(os.path.join(subdir, file), os.getcwd())).st_size == 0:
                print ("Filling file " + file)
                
                # Get filename
                filename = os.path.splitext(file)[0]

                # The header file
                hpp_file = open("core/include/" + filename + ".hpp", "w")

                hpp_template = open(os.path.dirname(os.path.realpath(__file__)) + "/templates/header_template.txt", "r")
                
                hpp_src = Template(hpp_template.read())

                upper_name = filename.upper()
                class_name = filename

                d={ "UPPER_NAME":upper_name, "CLASS_NAME":class_name }

                hpp_result = hpp_src.substitute(d)

                hpp_template.close()

                hpp_file.write(hpp_result)

                hpp_file.close()
                
    print()
    print("Filling empty source files...")
    print()
    for subdir, dirs, files in os.walk("core/src"):
        for file in files:
            ext = os.path.splitext(file)[-1].lower()
            if ext == ".cpp" and os.stat(os.path.relpath(os.path.join(subdir, file), os.getcwd())).st_size == 0:
                print ("Filling file " + file)

                # Get filename
                filename = os.path.splitext(file)[0]

                # The source file
                cpp_file = open("core/src/" + filename + ".cpp", "w")

                cpp_template = open(os.path.dirname(os.path.realpath(__file__)) + "/templates/source_template.txt", "r")
                
                cpp_src = Template(cpp_template.read())

                upper_name = filename.upper()
                class_name = filename

                d={ "UPPER_NAME":upper_name, "CLASS_NAME":class_name }

                cpp_result = cpp_src.substitute(d)

                cpp_template.close()

                cpp_file.write(cpp_result)

                cpp_file.close()

    print()
    print("Filling empty test files...")
    print()
    for subdir, dirs, files in os.walk("core/test"):
        for file in files:
            ext = os.path.splitext(file)[-1].lower()
            if ext == ".cpp" and os.stat(os.path.relpath(os.path.join(subdir, file), os.getcwd())).st_size == 0:
                print ("Filling file " + file)

                # Get filename
                filename = os.path.splitext(file)[0]

                # The test file
                test_file = open("core/test/" + filename + ".cpp", "w")

                test_template = open(os.path.dirname(os.path.realpath(__file__)) + "/templates/test_template.txt", "r")
                
                test_src = Template(test_template.read())

                upper_name = filename.split("_")[1].upper()
                class_name = filename.split("_")[1].capitalize()
                test_name = filename.split("_")[1]

                d={ "UPPER_NAME":upper_name, "CLASS_NAME":class_name, "TEST_NAME":test_name }

                test_result = test_src.substitute(d)

                test_template.close()

                test_file.write(test_result)

                test_file.close()

argparser = argparse.ArgumentParser(description="Project CLI for file modification and housekeeping.")
subparser = argparser.add_subparsers(help="The command to call")

class_parser = subparser.add_parser("class", description="Create a new class with header, source, and test files.")
class_parser.set_defaults(func=create_class)
class_parser.add_argument("name", metavar="N", type=str, help="the name of the class to create")

todo_parser = subparser.add_parser("todo", description="Generates ToDoLists.txt from all TODO statements in the project.")
todo_parser.set_defaults(func=run_todo)

build_parser = subparser.add_parser("build", description="Builds the project with additional options.")
build_parser.set_defaults(func=build_project)
build_parser.add_argument("-c", "--clean", action="store_false", help="An optional flag to start a clean project rebuild")
build_parser.add_argument("-e", "--exec", action="store_false", help="An optional flag to run the project if compilation is successful")
build_parser.add_argument("-t", "--test", action="store_false", help="An optional flag to run the project tests if compilation is successful")
build_parser.add_argument("-d", "--debug", action="store_true", help="An optional flag to build the project in Debug mode")
build_parser.add_argument("-r", "--release", action="store_true", help="An optional flag to build the project in Release mode")

fill_parser = subparser.add_parser("fill", description="Fills in empty files with template data.")
fill_parser.set_defaults(func=fill_files)

args = argparser.parse_args()
args.func(args)