import argparse
import json
import sys
import os
import subprocess
import shutil
import datetime

from enum import Enum

def to_snake_case(text):
    import re
    t1 = re.sub("(.)([A-Z][a-z]+)", r'\1_\2', text)
    return re.sub("([a-z0-9])([A-Z])", r'\1_\2', t1).lower()
    #return ''.join(['_' + i.lower() if i.isupper() else i for i in text]).lstrip('_')

def print_error(value):
    print("ERROR: " + value)

# The available build types for a module
class BuildTarget(Enum):
    Shared = "SHARED"
    Static = "STATIC"
    Executable = "EXE"

    def __str__(self):
        return self.name
    
    @staticmethod
    def argparse(s):
        try:
            return BuildTarget[s]
        except KeyError:
            raise ValueError()

    @staticmethod
    def list():
        return list(map(lambda n: n.name, BuildTarget))

# A dependency that can be held by a module
class Dependency:
    def __init__(self, domain, module):
        self.domain = domain
        self.module = module

    def equals(self, dep):
        return self.domain == dep.domain and self.module == dep.module

# A module within the project
class Module:
    def __init__(self, domain, name, build_target=BuildTarget.Shared, dependencies=None, generate_cmake=True, generate_api=True, generate_composite_h=True, custom_cmake_instructions=None):
        self.domain = domain
        self.name = name
        self.build_target = build_target
        self.dependencies = [] if dependencies is None else dependencies
        self.generate_cmake = generate_cmake
        self.generate_api = generate_api
        self.generate_composite_h = generate_composite_h
        self.custom_cmake_instructions = [] if custom_cmake_instructions is None else custom_cmake_instructions

# The command line interface for the project
class SeedEngineCLI(object):

    ENGINE_PATH = "Engine/"
    SOURCE_PATH = ENGINE_PATH + "Source/"
    TEMPLATE_PATH = os.path.dirname(os.path.realpath(__file__)) + "/Templates/"

    PUBLIC_DIR = "Public/"
    PRIVATE_DIR = "Private/"
    INTERFACE_DIR = "Interface/"
    TEST_DIR = "Test/"

    BINARY_PATH = ENGINE_PATH + "Bin/"
    BUILD_PATH = ENGINE_PATH + "Build/"
    LIBRARY_PATH = ENGINE_PATH + "Lib/"
    VS_PATH = SOURCE_PATH + ".vs/"

    PROJECT_DICT_CONSTANTS = {
        "PROJECT_NAME": "Seed Engine",
        "LICENSE": "MIT",
        "PROJECT_NAMESPACE": "seedengine",
        "PROJECT_HEADER_GUARD_PREFIX": "SEEDENGINE_",
        "PROJECT_API_MACRO": "ENGINE_API",
        "OWNER": "Confictura Studios",
        "REPO": "https://github.com/conficturastudios/seed-engine",
        "YEAR": datetime.datetime.now().year,
        "DATE": datetime.datetime.now().strftime("%m/%d/%Y")
    }

    def __init__(self):
        
        print()
        print("NOTICE: This tool should only be run with the project root as the working directory")
        print()

        argparser = argparse.ArgumentParser(
            description="Project CLI for file modification and housekeeping.",
            usage="<command> [<args>, <subcommand> [<args>]]"
            )
        
        subparsers = argparser.add_subparsers()

    # --- Add ---

        add_parser = subparsers.add_parser("add", description="Adds a new item to the project.")
        add_subparsers = add_parser.add_subparsers()

        # Add class

        add_class_parser = add_subparsers.add_parser("class", description="Adds a new class to a module within the project.")
        add_class_parser.set_defaults(func=self.add_class)
        add_class_parser.add_argument("domain", metavar="D", type=str, help="The domain to target (e.g. Runtime, Editor, etc.)")
        add_class_parser.add_argument("module", metavar="M", type=str, help="The name of the module to add this to")
        add_class_parser.add_argument("name", metavar="N", type=str, help="The name of the class to create")
        add_class_parser.add_argument("--folder", metavar="F", type=str, help="The subfolder to place this class inside")
        add_class_access = add_class_parser.add_mutually_exclusive_group(required=False)
        add_class_access.add_argument("--public", dest="access", action="store_true", help="Used to make the class public")
        add_class_access.add_argument("--private", dest="access", action="store_false", help="Used to make the class private",)
        add_class_access.set_defaults(access=True) # Set access to public by default

        # Add header

        add_header_parser = add_subparsers.add_parser("header", description="Adds a new header to a module within the project.")
        add_header_parser.set_defaults(func=self.add_header)
        add_header_parser.add_argument("domain", metavar="D", type=str, help="The domain to target (e.g. Runtime, Editor, etc.)")
        add_header_parser.add_argument("module", metavar="M", type=str, help="The name of the module to add this to")
        add_header_parser.add_argument("name", metavar="N", type=str, help="The name of the file to create")
        add_header_parser.add_argument("-c", "--makeclass", action="store_false", help="An optional flag to generate a header only class", required=False)
        add_header_parser.add_argument("--folder", metavar="F", type=str, help="The subfolder to place this class inside")
        add_header_access = add_header_parser.add_mutually_exclusive_group(required=False)
        add_header_access.add_argument("--public", dest="access", action="store_true", help="Used to make the header public")
        add_header_access.add_argument("--private", dest="access", action="store_false", help="Used to make the header private",)
        add_header_access.set_defaults(access=True) # Set access to public by default

        # Add source

        add_source_parser = add_subparsers.add_parser("source", description="Adds a new source file to a module within the project.")
        add_source_parser.set_defaults(func=self.add_source)
        add_source_parser.add_argument("domain", metavar="D", type=str, help="The domain to target (e.g. Runtime, Editor, etc.)")
        add_source_parser.add_argument("module", metavar="M", type=str, help="The name of the module to add this to")
        add_source_parser.add_argument("name", metavar="N", type=str, help="The name of the file to create")
        add_source_parser.add_argument("--folder", metavar="F", type=str, help="The subfolder to place this class inside")

        # Add test

        add_source_parser = add_subparsers.add_parser("test", description="Adds a new test file to a module within the project.")
        add_source_parser.set_defaults(func=self.add_test)
        add_source_parser.add_argument("domain", metavar="D", type=str, help="The domain to target (e.g. Runtime, Editor, etc.)")
        add_source_parser.add_argument("module", metavar="M", type=str, help="The name of the module to add this to")
        add_source_parser.add_argument("name", metavar="N", type=str, help="The name of the test suite")
        add_source_parser.add_argument("--folder", metavar="F", type=str, help="The subfolder to place this test inside")

        # Add module

        add_module_parser = add_subparsers.add_parser("module", description="Adds a new module to the project.")
        add_module_parser.set_defaults(func=self.add_module)
        add_module_parser.add_argument("domain", metavar="D", type=str, help="the domain to target (e.g. Runtime, Editor, etc.)")
        add_module_parser.add_argument("name", metavar="N", type=str, help="The name of the module to create")
        add_module_parser.add_argument("target", metavar="T", type=BuildTarget.argparse, choices=list(BuildTarget),
            help=("The targeted build type for this module [" + (", ".join(BuildTarget.list())) + "]"))
        add_module_parser.add_argument("dependencies", metavar="P", nargs='*', type=str,
            help="The modules that this module is dependent on. This should be in the form \"Domain Module\" with a single space for seperation.")

        # Add dependency
        
        add_dep_parser = add_subparsers.add_parser("dep", description="Adds a new dependency to a module within the project.")
        add_dep_parser.set_defaults(func=self.add_dependency)
        add_dep_parser.add_argument("domain", metavar="D", type=str, help="The domain to target (e.g. Runtime, Editor, etc.)")
        add_dep_parser.add_argument("module", metavar="M", type=str, help="The name of the module to add this to")
        add_dep_parser.add_argument("dep_domain", metavar="DD", type=str, help="The domain of the dependency to add")
        add_dep_parser.add_argument("dep_module", metavar="DM", type=str, help="The module of the dependency to add")

    # --- Remove ---

        remove_parser = subparsers.add_parser("remove", description="Removes an existing item from the project.")
        remove_subparsers = remove_parser.add_subparsers()

        #TODO: Add more item removal options (class, header, source, test, module)

        # Remove dependency
        
        remove_dep_parser = remove_subparsers.add_parser("dep", description="Removes an existing dependency from a module within the project.")
        remove_dep_parser.set_defaults(func=self.remove_dependency)
        remove_dep_parser.add_argument("domain", metavar="D", type=str, help="The domain to target (e.g. Runtime, Editor, etc.)")
        remove_dep_parser.add_argument("module", metavar="M", type=str, help="The name of the module to remove this from")
        remove_dep_parser.add_argument("dep_domain", metavar="DD", type=str, help="The domain of the dependency to remove")
        remove_dep_parser.add_argument("dep_module", metavar="DM", type=str, help="The module of the dependency to remove")
        #TODO: Add -f --force option to supress warnings about removal
        #TODO: Add warnings and confirmation options to this operation
        #TODO: Create generalized action confirmation utility

    # --- Refactor ---

        #TODO: Add refactoring tools

    # --- Build ---

        build_parser = subparsers.add_parser("build", description="Builds the project with additional options.")
        build_parser.set_defaults(func=self.build)
        build_parser.add_argument("-c", "--clean", action="store_true", help="An optional flag to start a clean project rebuild", required=False)
        build_parser.add_argument("-e", "--exec", action="store_true", help="An optional flag to run the project if compilation is successful", required=False)
        build_parser.add_argument("-t", "--test", action="store_true", help="An optional flag to run the project tests if compilation is successful", required=False)
        build_parser.add_argument("-d", "--debug", action="store_false", help="An optional flag to build the project in Debug mode", required=False)
        build_parser.add_argument("-r", "--release", action="store_false", help="An optional flag to build the project in Release mode", required=False)
                
    # --- To Do ---

        todo_parser = subparsers.add_parser("todo", description="Generates ToDoLists.txt from all TODO statements in the project.")
        todo_parser.set_defaults(func=self.todo)

    # --- Run ---

        run_parser = subparsers.add_parser("run", description="Runs the project with additional options.")
        run_parser.set_defaults(func=self.run)
        run_parser.add_argument("-d", "--debug", action="store_true", help="An optional flag to run the project Debug build")
        run_parser.add_argument("-t", "--test", action="store_true", help="An optional flag to run the project tests")

    # --- Regenerate procedural files ---

        # Regenerate module

        regen_parser = subparsers.add_parser("regen", description="Rebuilds generated CMakeLists.txt and API header files if enabled. Updates file tracking.")
        regen_parser.set_defaults(func=self.regen)
        regen_parser.add_argument("domain", metavar="D", type=str, help="The domain to target (e.g. Runtime, Editor, etc.)")
        regen_parser.add_argument("module", metavar="M", type=str, help="The name of the module regenerate")

        # Regenerate modules in domain

        regen_all_parser = subparsers.add_parser("regenall", description="Rebuilds generated CMakeLists.txt and API header files for all modules if enabled. Updates file tracking.")
        regen_all_parser.set_defaults(func=self.regen_all)
        regen_all_parser.add_argument("domain", metavar="D", type=str, help="The domain to target (e.g. Runtime, Editor, etc.)")

    # --- Get module info ---

        list_parser = subparsers.add_parser("list", description="Lists information about the project.")
        list_subparsers = list_parser.add_subparsers()

        # List modules
        
        list_module_parser = list_subparsers.add_parser("module", description="Lists the modules of the specified domain.")
        list_module_parser.set_defaults(func=self.list_modules)
        list_module_parser.add_argument("domain", metavar="D", type=str, help="The domain to check (e.g. Runtime, Editor, etc.)")

        # List domains

        list_domain_parser = list_subparsers.add_parser("domain", description="Lists the domains of the project.")
        list_domain_parser.set_defaults(func=self.list_domains)

        # List module dependencies
        
        list_dep_parser = list_subparsers.add_parser("dep", description="Lists the dependencies of the specified module.")
        list_dep_parser.set_defaults(func=self.list_dependencies)
        list_dep_parser.add_argument("domain", metavar="D", type=str, help="The domain to target (e.g. Runtime, Editor, etc.)")
        list_dep_parser.add_argument("module", metavar="M", type=str, help="The name of the module to check")
        list_dep_parser.add_argument("-r", "--recursive", action="store_true", help="An optional flag to get dependencies recurssively", required=False)

        # List module references

        list_usage_parser = list_subparsers.add_parser("ref", description="Lists the modules dependent on the specified module.")
        list_usage_parser.set_defaults(func=self.list_references)
        list_usage_parser.add_argument("domain", metavar="D", type=str, help="The domain to target (e.g. Runtime, Editor, etc.)")
        list_usage_parser.add_argument("module", metavar="M", type=str, help="The name of the module to check")
        list_usage_parser.add_argument("-r", "--recursive", action="store_true", help="An optional flag to check references recurssively", required=False)

    # --- Run Command ---

        args = argparser.parse_args()
        args.func(args)

### START ### --- Command Functions

    def add_class(self, args):
        from string import Template

        if not (self.__check_str_format(args.name)):
            print("ERROR: Invalid class name '" + args.name + "'. Exiting.")
            return
        if not (self.__check_str_format(args.module)):
            print("ERROR: Invalid module name '" + args.module + "'. Exiting.")
            return
        if not (self.__check_str_format(args.domain)):
            print("ERROR: Invalid domain name '" + args.domain + "'. Exiting.")
            return

        class_name = args.name
        class_name_upper = to_snake_case(args.name).upper()
        module_name = args.module
        module_name_upper = to_snake_case(args.module).upper()
        domain_name = args.domain
        domain_name_upper = to_snake_case(args.domain).upper()

        domain_path = self.__get_domain_path(args.domain)
        module_path = self.__get_module_path(args.domain, args.module)
        print("Creating class " + class_name + "...")

        subdir = ""
        relpath = ""
        if args.folder is not None:
            if not (self.__check_dir_format(args.folder)):
                print("ERROR: Invalid folder name '" + args.folder + "'. Skipping folder creation.")
            else:
                subdir = args.folder + "/"
                if not self.__check_module_subdir_exists(args.domain, args.module, args.folder, True):
                    self.__create_dir(self.__get_module_subdir_path(args.domain, args.module, args.folder, True))
                if not self.__check_module_subdir_exists(args.domain, args.module, args.folder, False):
                    self.__create_dir(self.__get_module_subdir_path(args.domain, args.module, args.folder, False))
                if args.access:
                    for c in subdir:
                        if c == '/' or c == '\\':
                            relpath = "../" + relpath

        values = {
            "CLASS_NAME":class_name,
            "CLASS_NAME_UPPER":class_name_upper,
            "MODULE_NAME":module_name,
            "MODULE_NAME_UPPER":module_name_upper,
            "DOMAIN_NAME":domain_name,
            "DOMAIN_NAME_UPPER":domain_name_upper,
            "SUBDIR":subdir,
            "RELPATH":relpath
        }

        values.update(self.PROJECT_DICT_CONSTANTS)

        header_success = -1
        if args.access:
            header_success = self.__generate_file_from_temp(
                module_path + self.PUBLIC_DIR + subdir + class_name + ".hpp",
                "ModuleAddClassHeader.tmp",
                values
            )
        else:
            header_success = self.__generate_file_from_temp(
                module_path + self.PRIVATE_DIR + subdir + class_name + ".hpp",
                "ModuleAddClassHeader.tmp",
                values
            )
        src_success = self.__generate_file_from_temp(
            module_path + self.PRIVATE_DIR + subdir + class_name + ".cpp",
            "ModuleAddClassSource.tmp",
            values
        )
        test_success = -1
        if args.access:
            test_success = self.__generate_file_from_temp(
                module_path + self.TEST_DIR + subdir + "Test" + domain_name + module_name + class_name + ".cpp",
                "ModuleAddClassTest.tmp",
                values
            )

        if header_success != -1 and src_success != -1 and test_success != -1:
            print("Class '" + class_name + "' created successfully.")
        else:
            print("Errors found when creating class '" + class_name + "'.")
            
        composite_result = self.__generate_module_header(domain_name, module_name)
        cmake_result = self.__generate_cmake(domain_name, module_name)

        if cmake_result == -1 or composite_result == -1:
            print("WARNING: Errors encountered when updating CMakeLists.txt or composite header.")
            return
        else:
            print("Module '" + module_name + "' CMakeLists.txt and composite header updated successfully.")
            return

    def add_header(self, args):
        from string import Template

        if not (self.__check_str_format(args.name)):
            print("ERROR: Invalid class name '" + args.name + "'. Exiting.")
            return
        if not (self.__check_str_format(args.module)):
            print("ERROR: Invalid module name '" + args.module + "'. Exiting.")
            return
        if not (self.__check_str_format(args.domain)):
            print("ERROR: Invalid domain name '" + args.domain + "'. Exiting.")
            return
            
        module_path = self.__get_module_path(args.domain, args.module)

        class_name = args.name
        class_name_upper = to_snake_case(args.name).upper()
        module_name = args.module
        module_name_upper = to_snake_case(args.module).upper()
        domain_name = args.domain
        domain_name_upper = to_snake_case(args.domain).upper()

        subdir = ""
        relpath = ""
        if args.folder is not None:
            if not (self.__check_dir_format(args.folder)):
                print("ERROR: Invalid folder name '" + args.folder + "'. Skipping folder creation.")
            else:
                subdir = args.folder + "/"
                if not self.__check_module_subdir_exists(args.domain, args.module, args.folder, args.access):
                    self.__create_dir(self.__get_module_subdir_path(args.domain, args.module, args.folder, args.access))
                if args.access:
                    for c in subdir:
                        if c == '/' or c == '\\':
                            relpath = "../" + relpath

        # The header file
        template_file = "ModuleAddHeader"
        if args.makeclass:
            print("Creating header only class " + class_name + "...")
            template_file = template_file + "Class"
        else:
            print("Creating header file " + class_name + "...")

        values = {
            "CLASS_NAME":class_name,
            "CLASS_NAME_UPPER":class_name_upper,
            "MODULE_NAME":module_name,
            "MODULE_NAME_UPPER":module_name_upper,
            "DOMAIN_NAME":domain_name,
            "DOMAIN_NAME_UPPER":domain_name_upper,
            "SUBDIR":subdir,
            "RELPATH":relpath
        }

        values.update(self.PROJECT_DICT_CONSTANTS)
        
        header_success = -1
        if args.access:
            header_success = self.__generate_file_from_temp(
                module_path + self.PUBLIC_DIR + subdir + class_name + ".hpp",
                template_file + ".tmp",
                values
            )
        else:
            header_success = self.__generate_file_from_temp(
                module_path + self.PRIVATE_DIR + subdir + class_name + ".hpp",
                template_file + ".tmp",
                values
            )

        if header_success != -1:
            print("Header '" + class_name + "' created successfully.")
        else:
            print("Failed to create header '" + class_name + "'.")

        composite_result = self.__generate_module_header(domain_name, module_name)
        cmake_result = self.__generate_cmake(domain_name, module_name)

        if cmake_result == -1 or composite_result == -1:
            print("WARNING: Errors encountered when updating CMakeLists.txt or composite header.")
            return
        else:
            print("Module '" + module_name + "' CMakeLists.txt and composite header updated successfully.")
            return

    def add_module(self, args):
        from string import Template

        # Check for input errors

        if not (self.__check_str_format(args.name)):
            print("ERROR: Invalid module name '" + args.name + "'. Exiting.")
            return
        if not (self.__check_str_format(args.domain)):
            print("ERROR: Invalid domain name '" + args.domain + "'. Exiting.")
            return
        
        # Get data from inputs

        domain_path = self.__get_domain_path(args.domain)
        module_path = self.__get_module_path(args.domain, args.name)
        
        module_name = args.name
        module_name_upper = to_snake_case(args.name).upper()
        domain_name = args.domain
        domain_name_upper = to_snake_case(args.domain).upper()

        # Set up dependency strings

        json_dependencies = ""

        json_dep_temp_str = "{\n\t\t\t\"Domain\": \"${DEPENDENCY_DOMAIN}\",\n\t\t\t\"Module\": \"${DEPENDENCY}\"\n\t\t}"
        json_dep_temp = Template(json_dep_temp_str)

        for dep in args.dependencies:
            if (dep.count(" ") != 1):
                print_error("Invalid dependency format '" + dep + "'. Exiting.")
                return
            dep_domain = dep.split()[0]
            dep_module = dep.split()[1]
            dep_domain_path = self.__get_domain_path(dep_domain)
            dep_module_path = self.__get_module_path(dep_domain, dep_module)
            if not (os.path.exists(dep_domain_path) and os.path.exists(dep_module_path)):
                print_error("Module '" + dep + "' does not exist. Exiting.")
                return

            ds={
                "MODULE_NAME":module_name,
                "MODULE_NAME_UPPER":module_name_upper,
                "DOMAIN_NAME":domain_name,
                "DOMAIN_NAME_UPPER":domain_name_upper,
                "DEPENDENCY":dep_module,
                "DEPENDENCY_DOMAIN":dep_domain
            }
            json_dependencies = json_dependencies + ("" if json_dependencies == "" else ",\n\t\t") + json_dep_temp.safe_substitute(ds)
        
        # Check if domain and module are valid

        if not self.__check_domain_exists(domain_name):
            print("Project domain does not exist. Check engine/source folder to see available domains.")
        else:
            if not self.__check_module_exists(domain_name, module_name):
                print("Creating " + domain_name + " module " + module_name + "...")
                self.__create_dir(module_path)
                self.__create_dir(module_path + self.PUBLIC_DIR)
                self.__create_dir(module_path + self.PRIVATE_DIR)
                self.__create_dir(module_path + self.INTERFACE_DIR)
                self.__create_dir(module_path + self.TEST_DIR)

                values = {
                    "MODULE_NAME":module_name,
                    "MODULE_NAME_UPPER":module_name_upper,
                    "DOMAIN_NAME":domain_name,
                    "DOMAIN_NAME_UPPER":domain_name_upper,
                    "BUILD_TARGET":args.target,
                    "JSON_DEPENDENCIES":json_dependencies
                }

                values.update(self.PROJECT_DICT_CONSTANTS)

                # Handle Executable entry point

                if args.target is BuildTarget.Executable:
                    # Executible entry file for module
                    self.__generate_file_from_temp(
                        module_path + self.PRIVATE_DIR + module_name + "Entry.cpp",
                        "ModuleEntry.tmp",
                        values
                    )

                # Generate module JSON file
                self.__generate_file_from_temp(
                    module_path + "Module.json",
                    "ModuleJson.tmp",
                    values
                )
                # Generate module test file
                self.__generate_file_from_temp(
                    module_path + self.TEST_DIR + "Test" + domain_name + module_name + ".cpp",
                    "ModuleTest.tmp",
                    values
                )

                print("Module '" + module_name + "' created successfully.")

                api_result = self.__generate_api_header(domain_name, module_name)
                composite_result = self.__generate_module_header(domain_name, module_name)
                cmake_result = self.__generate_cmake(domain_name, module_name)

                if cmake_result == -1 or api_result == -1 or composite_result == -1:
                    print("WARNING: Errors encountered when generating CMakeLists.txt, API header, or composite header.")
                    return
                else:
                    print("Module '" + module_name + "' CMakeLists.txt, API header, and composite header updated successfully.")
                    return

            else:
                print_error("Module '" + args.name + "' already exists.")

    def add_source(self, args):
        from string import Template

        if not (self.__check_str_format(args.name)):
            print("ERROR: Invalid class name '" + args.name + "'. Exiting.")
            return
        if not (self.__check_str_format(args.module)):
            print("ERROR: Invalid module name '" + args.module + "'. Exiting.")
            return
        if not (self.__check_str_format(args.domain)):
            print("ERROR: Invalid domain name '" + args.domain + "'. Exiting.")
            return

        source_name = args.name
        source_name_upper = to_snake_case(args.name).upper()
        module_name = args.module
        module_name_upper = to_snake_case(args.module).upper()
        domain_name = args.domain
        domain_name_upper = to_snake_case(args.domain).upper()

        domain_path = self.__get_domain_path(args.domain)
        module_path = self.__get_module_path(args.domain, args.module)

        # Create the source file
        print("Creating source file " + source_name + "...")

        subdir = ""
        relpath = ""
        if args.folder is not None:
            if not (self.__check_dir_format(args.folder)):
                print("ERROR: Invalid folder name '" + args.folder + "'. Skipping folder creation.")
            else:
                subdir = args.folder + "/"
                if not self.__check_module_subdir_exists(args.domain, args.module, args.folder, False):
                    self.__create_dir(self.__get_module_subdir_path(args.domain, args.module, args.folder, False))
                # for c in subdir:
                #     if c == '/' or c == '\\':
                #         relpath = "../" + relpath

        values = {
            "SOURCE_NAME":source_name,
            "SOURCE_NAME_UPPER":source_name_upper,
            "MODULE_NAME":module_name,
            "MODULE_NAME_UPPER":module_name_upper,
            "DOMAIN_NAME":domain_name,
            "DOMAIN_NAME_UPPER":domain_name_upper,
            "SUBDIR":subdir,
            "RELPATH":relpath
        }

        values.update(self.PROJECT_DICT_CONSTANTS)

        source_success = self.__generate_file_from_temp(
            module_path + self.PRIVATE_DIR + subdir + source_name + ".cpp",
            "ModuleAddSource.tmp",
            values
        )

        if source_success != -1:
            print("Source file '" + source_name + "' created successfully.")
        else:
            print("Failed to create source file '" + source_name + "'.")

        cmake_result = self.__generate_cmake(domain_name, module_name)

        if cmake_result == -1:
            print("WARNING: Errors encountered when updating CMakeLists.txt.")
            return
        else:
            print("Module '" + module_name + "' CMakeLists.txt updated successfully.")
            return

    def add_test(self, args):
        from string import Template

        if not (self.__check_str_format(args.name)):
            print("ERROR: Invalid test name '" + args.name + "'. Exiting.")
            return
        if not (self.__check_str_format(args.module)):
            print("ERROR: Invalid module name '" + args.module + "'. Exiting.")
            return
        if not (self.__check_str_format(args.domain)):
            print("ERROR: Invalid domain name '" + args.domain + "'. Exiting.")
            return

        class_name = args.name
        class_name_upper = to_snake_case(args.name).upper()
        module_name = args.module
        module_name_upper = to_snake_case(args.module).upper()
        domain_name = args.domain
        domain_name_upper = to_snake_case(args.domain).upper()

        domain_path = self.__get_domain_path(args.domain)
        module_path = self.__get_module_path(args.domain, args.module)
        print("Creating test " + domain_name + module_name + class_name + "...")

        subdir = ""
        relpath = ""
        if args.folder is not None:
            if not (self.__check_dir_format(args.folder)):
                print("ERROR: Invalid folder name '" + args.folder + "'. Skipping folder creation.")
            else:
                subdir = args.folder + "/"
                if not self.__check_module_test_subdir_exists(args.domain, args.module, args.folder):
                    self.__create_dir(self.__get_module_test_subdir_path(args.domain, args.module, args.folder))
                # for c in subdir:
                #     if c == '/' or c == '\\':
                #         relpath = "../" + relpath

        values = {
            "CLASS_NAME":class_name,
            "CLASS_NAME_UPPER":class_name_upper,
            "MODULE_NAME":module_name,
            "MODULE_NAME_UPPER":module_name_upper,
            "DOMAIN_NAME":domain_name,
            "DOMAIN_NAME_UPPER":domain_name_upper,
            "SUBDIR":subdir,
            "RELPATH":relpath
        }

        values.update(self.PROJECT_DICT_CONSTANTS)

        test_success = -1
        test_success = self.__generate_file_from_temp(
            module_path + self.TEST_DIR + subdir + "Test" + domain_name + module_name + class_name + ".cpp",
            "ModuleAddTest.tmp",
            values
        )

        if test_success != -1:
            print("Test '" + domain_name + module_name + class_name + "' created successfully.")
        else:
            print("Errors found when creating test '" + domain_name + module_name + class_name + "'.")

    def add_dependency(self, args):
        if not (self.__check_str_format(args.dep_domain)):
            print("ERROR: Invalid domain name '" + args.dep_domain + "'. Exiting.")
            return
        if not (self.__check_str_format(args.dep_module)):
            print("ERROR: Invalid module name '" + args.dep_module + "'. Exiting.")
            return
        if not (self.__check_str_format(args.module)):
            print("ERROR: Invalid module name '" + args.module + "'. Exiting.")
            return
        if not (self.__check_str_format(args.domain)):
            print("ERROR: Invalid domain name '" + args.domain + "'. Exiting.")
            return
        self.__add_module_dependency(args.domain, args.module, Dependency(args.dep_domain, args.dep_module))

        api_result = self.__generate_api_header(args.domain, args.module)
        cmake_result = self.__generate_cmake(args.domain, args.module)

        if cmake_result == -1 or api_result == -1:
            print("WARNING: Errors encountered when generating CMakeLists.txt, API header, or composite header.")
            return
        else:
            print("Module '" + args.module + "' CMakeLists.txt and API header updated successfully.")
            return

    def remove_dependency(self, args):
        if not (self.__check_str_format(args.dep_domain)):
            print("ERROR: Invalid domain name '" + args.dep_domain + "'. Exiting.")
            return
        if not (self.__check_str_format(args.dep_module)):
            print("ERROR: Invalid module name '" + args.dep_module + "'. Exiting.")
            return
        if not (self.__check_str_format(args.module)):
            print("ERROR: Invalid module name '" + args.module + "'. Exiting.")
            return
        if not (self.__check_str_format(args.domain)):
            print("ERROR: Invalid domain name '" + args.domain + "'. Exiting.")
            return
        self.__remove_module_dependency(args.domain, args.module, Dependency(args.dep_domain, args.dep_module))

        api_result = self.__generate_api_header(args.domain, args.module)
        cmake_result = self.__generate_cmake(args.domain, args.module)

        if cmake_result == -1 or api_result == -1:
            print("WARNING: Errors encountered when generating CMakeLists.txt, API header, or composite header.")
            return
        else:
            print("Module '" + args.module + "' CMakeLists.txt and API header updated successfully.")
            return

    def build(self, args):
        debug_ret = 0
        release_ret = 0
        if args.clean:
            self.__delete_dir(self.BINARY_PATH)
            self.__delete_dir(self.BUILD_PATH)
            self.__delete_dir(self.LIBRARY_PATH)
            self.__delete_dir(self.VS_PATH)
        if args.debug:
            if args.clean:
                os.system("cmake -S ./" + self.ENGINE_PATH + " -B " + self.BUILD_PATH + "Debug -DCMAKE_BUILD_TYPE=Debug")
            debug_ret = subprocess.call("cmake --build " + self.BUILD_PATH + "Debug --config Debug")
        if args.release:
            if args.clean:
                os.system("cmake -S ./" + self.ENGINE_PATH + " -B " + self.BUILD_PATH + "Release -DCMAKE_BUILD_TYPE=Release")
            release_ret = subprocess.call("cmake --build " + self.BUILD_PATH + "Release --config Release")
        if args.exec:
            if args.release and release_ret == 0:
                print()
                print("Executing program release binaries.")
                print()
                subprocess.call("./" + self.BINARY_PATH + "Release/seed-engine-editor.exe") #TODO: fix for linux users
            elif args.debug and debug_ret == 0:
                print()
                print("Executing program debug binaries.")
                print()
                subprocess.call("./" + self.BINARY_PATH + "Debug/seed-engine-editor.exe")
            else:
                print()
                print("Could not run program. Exiting.")
                print()
                return
        if args.test:
            if args.release and release_ret == 0:
                print()
                print("Executing program release tests.")
                print()
                subprocess.call("./" + self.BINARY_PATH + "Release/SeedEngine-0.0.1Tests.exe")
            elif args.debug and debug_ret == 0:
                print()
                print("Executing program debug tests.")
                print()
                subprocess.call("./" + self.BINARY_PATH + "Debug/SeedEngine-0.0.1Tests.exe")
            else:
                print()
                print("Could not run tests. Exiting.")
                print()
                return

    def todo(self, args):
        try:
            import ToDo
        except ImportError:
            print("Error while importing 'ToDo' library. Exiting.")
            pass

    def run(self, args):
        if args.test:
            if args.debug:
                print()
                print("Executing program debug tests.")
                print()
                subprocess.call("./" + self.BINARY_PATH + "Debug/seed-engine-core-tests.exe")
            else:
                print()
                print("Executing program release tests.")
                print()
                subprocess.call("./" + self.BINARY_PATH + "Release/seed-engine-core-tests.exe")
        else:
            if args.debug:
                print()
                print("Running project Debug executibles...")
                print()
                subprocess.call("./" + self.BINARY_PATH + "Debug/seed-engine-editor.exe")
            else:
                print()
                print("Running project Release executibles...")
                print()
                subprocess.call("./" + self.BINARY_PATH + "Release/seed-engine-editor.exe")

    def regen(self, args):
        self.__regen_module(args.domain, args.module)

    def regen_all(self, args):
        print("Testing regenall...")
        domain_path = self.__get_domain_path(args.domain)
        for module in os.listdir(domain_path):
            if os.path.isdir(domain_path + "/" + module):
                self.__regen_module(args.domain, module)

    def list_dependencies(self, args):
        
        if not self.__check_module_exists(args.domain, args.module):
            print_error("Module '" + args.domain + " " + args.module + "' does not exist.")
            return

        self.__list_module_dependencies(args.domain, args.module, args.recursive, 0)

    def list_references(self, args):
        
        if not self.__check_module_exists(args.domain, args.module):
            print_error("Module '" + args.domain + " " + args.module + "' does not exist.")
            return

        self.__list_module_references(args.domain, args.module, args.recursive, 0)

    def list_modules(self, args):
        if not self.__check_domain_exists(args.domain):
            print_error("Domain '" + args.domain + "' does not exist.")
            return

        module_list = self.__get_domain_modules(args.domain)

        for mod in module_list:
            print(mod.module)

    def list_domains(self, args):
        for domain in os.listdir(self.SOURCE_PATH):
            if os.path.isdir(os.path.join(self.SOURCE_PATH, domain)):
                print(domain)


### START ### --- File utility functions

    def __delete_dir(self, dir):
        try:
            if os.path.exists(dir) and os.path.isdir(dir):
                print("Removing directory '%s'" % (dir))
                shutil.rmtree(dir)
        except OSError as e:
            print_error("%s - %s." % (e.filename, e.strerror))
        print()
    
    def __create_dir(self, dir):
        try:
            if not (os.path.exists(dir) and os.path.isdir(dir)):
                print("Creating directory '%s'" % (dir))
                os.makedirs(dir)
        except OSError as e:
            print_error("%s - %s." % (e.filename, e.strerror))
        print()


### START ### --- Module utility functions

    def __get_domain_path(self, domain):
        return self.SOURCE_PATH + "/" + domain + "/"
    
    def __get_module_path(self, domain, module):
        return self.__get_domain_path(domain) + module + "/"

    def __get_module_subdir_path(self, domain, module, subdir, is_public):
        if is_public:
            return self.__get_module_path(domain, module) + "Public/" + subdir + "/"
        else:
            return self.__get_module_path(domain, module) + "Private/" + subdir + "/"

    def __get_module_test_subdir_path(self, domain, module, subdir):
        return self.__get_module_path(domain, module) + "Test/" + subdir + "/"

    def __check_domain_exists(self, domain):
        domain_path = self.__get_domain_path(domain)
        return os.path.exists(domain_path)

    def __check_module_exists(self, domain, module):
        module_path = self.__get_module_path(domain, module)
        return self.__check_domain_exists(domain) and os.path.exists(module_path)

    def __check_module_subdir_exists(self, domain, module, subdir, is_public):
        subdir_path = self.__get_module_subdir_path(domain, module, subdir, is_public)
        return self.__check_module_exists(domain, module) and os.path.exists(subdir_path)

    def __check_module_test_subdir_exists(self, domain, module, subdir):
        subdir_path = self.__get_module_test_subdir_path(domain, module, subdir)
        return self.__check_module_exists(domain, module) and os.path.exists(subdir_path)

    def __check_str_format(self, text):
        import re
        return re.match("^[A-Za-z_][A-Za-z0-9_]*$", text) != None

    def __check_dir_format(self, path):
        import re
        return re.match("^([A-Za-z_][A-Za-z0-9_]*)([/][A-Za-z_][A-Za-z0-9_]*)*$", path) != None

    def __check_module_has_dependency(self, domain, module, dep):

        if not self.__check_module_exists(domain, module):
            print_error("Module '" + domain + " " + module + "' does not exist. Exiting process.")
            return -1

        if not self.__check_module_exists(dep.domain, dep.module):
            print_error("Module '" + dep.domain + " " + dep.module + "' does not exist. Exiting process.")
            return -1

        # Read in JSON data
        json_data = self.__get_json_data(domain, module)
        if json_data == None:
            print("Encountered an error when getting JSON data, exiting dependency check.")
            return -1

        count = 0
        for d in json_data.dependencies:
            if d.equals(dep):
                count = count + 1

        return count > 0

    def __add_module_dependency(self, domain, module, dep):

        if not self.__check_module_exists(domain, module):
            print_error("Module '" + domain + " " + module + "' does not exist. Exiting generation.")
            return -1

        if not self.__check_module_exists(dep.domain, dep.module):
            print_error("Module '" + dep.domain + " " + dep.module + "' does not exist. Exiting generation.")
            return -1

        print("Getting module info...")

        # Read in JSON data
        json_data = self.__get_json_data(domain, module)
        if json_data == None:
            print("Encountered an error when getting JSON data, exiting dependency add.")
            return -1

        count = 0
        for d in json_data.dependencies:
            if d.equals(dep):
                count = count + 1

        if count != 0:
            print("Module '" + domain + " " + module + "' is already dependent on module '" + dep.domain + " " + dep.module + "'. Exiting process.")
            return -1

        print("Adding dependency '" + dep.domain + " " + dep.module + "' to " + domain + " module '" + module + "'...")

        json_data.dependencies.append(dep)

        self.__write_json_data(domain, module, json_data)

        print("Finished adding dependency to " + domain + " module '" + module + "'.")
        return 1

    def __remove_module_dependency(self, domain, module, dep):

        if not self.__check_module_exists(domain, module):
            print_error("Module '" + domain + " " + module + "' does not exist. Exiting process.")
            return -1

        if not self.__check_module_exists(dep.domain, dep.module):
            print_error("Module '" + dep.domain + " " + dep.module + "' does not exist. Exiting process.")
            return -1

        print("Getting module info...")

        # Read in JSON data
        json_data = self.__get_json_data(domain, module)
        if json_data == None:
            print("Encountered an error when getting JSON data, exiting dependency removal.")
            return -1

        count = 0
        for d in json_data.dependencies:
            if d.equals(dep):
                count = count + 1

        if count == 0:
            print("Module '" + domain + " " + module + "' is not dependent on module '" + dep.domain + " " + dep.module + "'. Exiting process.")
            return -1

        print("Removing dependency '" + dep.domain + " " + dep.module + "' from " + domain + " module '" + module + "'...")

        for d in json_data.dependencies:
            if d.equals(dep):
                json_data.dependencies.remove(d)

        self.__write_json_data(domain, module, json_data)

        print("Finished adding dependency to " + domain + " module '" + module + "'.")
        return 1

    def __get_domain_modules(self, domain):
        domain_path = self.__get_domain_path(domain)

        module_list = []

        for module in os.listdir(domain_path):
            if os.path.isdir(os.path.join(domain_path, module)):
                module_list.append(Dependency(domain, module))

        return module_list

    def __list_module_dependencies(self, domain, module, recursive, level):

        data = self.__get_json_data(domain, module)

        indent = "\t" * level

        for dep in data.dependencies:
            print(indent + dep.domain + " " + dep.module)
            if recursive:
                self.__list_module_dependencies(dep.domain, dep.module, recursive, level + 1)

    def __list_module_references(self, domain, module, recursive, level):
        
        module_list = self.__get_domain_modules(domain)

        indent = "\t" * level

        for mod in module_list:
            # print("Checking module '" + mod.domain + " " + mod.module + "' for dependency '" + domain + " " + module + "'...")
            # print(self.__check_module_has_dependency(mod.domain, mod.module, Dependency(domain, module)))
            if self.__check_module_has_dependency(mod.domain, mod.module, Dependency(domain, module)):
                print(indent + mod.domain + " " + mod.module)
                if recursive:
                    self.__list_module_references(mod.domain, mod.module, recursive, level + 1)


### START ### --- File generation utility functions

    def __generate_file_from_temp(self, destination_path, template_path, values={}):
        from string import Template
        try:
            dest = open(destination_path, "w")
            temp = open(self.TEMPLATE_PATH + template_path, "r")
            src = Template(temp.read())
            result = src.safe_substitute(values)
            temp.close()
            dest.write(result)
            dest.close()
            return 1
        except OSError as e:
            print_error("Error thrown when generating file from template:")
            print_error("%s - %s." % (e.filename, e.strerror))
            return -1
    
    def __generate_cmake(self, domain, module):
        from string import Template

        if not self.__check_module_exists(domain, module):
            print_error("Module '" + domain + " " + module + "' does not exist. Exiting generation.")
            return -1

        module_path = self.__get_module_path(domain, module)

        print("Generating CMakeLists.txt for " + domain + " module '" + module + "'...")

        # Read in JSON data
        json_data = self.__get_json_data(domain, module)
        if json_data == None:
            print("Encountered an error when getting JSON data, exiting CMakeLists.txt generation.")
            return -1

        # -- Check if GenerateCMake is enabled, exit with message if not
        if not json_data.generate_cmake:
            print("CMakeLists.txt generation is disabled for " + domain + " module " + module + "'.")
            return 0

        # -- Read in build target

        build_target = json_data.build_target

        build_instruction = ""

        if build_target == BuildTarget.Executable:
            build_instruction = "add_executable(${LIBRARY_NAME} ${${LIBRARY_NAME_UPPER}_SRC})"
        elif build_target == BuildTarget.Shared:
            build_instruction = "add_library(${LIBRARY_NAME} SHARED ${${LIBRARY_NAME_UPPER}_SRC})"
            pass
        elif build_target == BuildTarget.Static:
            build_instruction = "add_library(${LIBRARY_NAME} STATIC ${${LIBRARY_NAME_UPPER}_SRC})"
            pass
        else:
            print_error("Invalid build target, exiting CMakeLists.txt generation.")
            return -1

        # -- Read in dependencies from JSON

        dependencies = json_data.dependencies

        dep_temp_str = "add_dependencies(${LIBRARY_NAME} ${DEPENDENCY_DOMAIN}${DEPENDENCY})\n"
        dep_temp_str = dep_temp_str + "target_link_libraries(${LIBRARY_NAME} ${LIBRARY_SCOPE} ${DEPENDENCY_DOMAIN}${DEPENDENCY})\n"
        dep_temp = Template(dep_temp_str)

        dependency_str = ""

        for dep in dependencies:
            if not self.__check_module_exists(dep.domain, dep.module):
                print_error("Module '" + dep.domain + " " + dep.module + "' does not exist. Skipping.")
            else:
                dep_values = {
                    "DEPENDENCY_DOMAIN": dep.domain,
                    "DEPENDENCY": dep.module
                }
                dependency_str = dependency_str + dep_temp.safe_substitute(dep_values)

        # -- Read in custom instructions from JSON

        # TODO: Apply compilation condition field (think os + framework dependency)

        custom_instruction = ""

        for instruction in json_data.custom_cmake_instructions:
            custom_instruction = custom_instruction + instruction + "\n"

        # Create source file lists

        sources = []
        headers = []
        src_path = module_path + self.PRIVATE_DIR
        header_path = module_path + self.PUBLIC_DIR

        for root, dirs, files in os.walk(src_path):
            for source in files:
                if source.endswith(".cpp"):
                    _dir = os.path.relpath(root, src_path)
                    if not (_dir == "."):
                        _dir = _dir + "/"
                    else:
                        _dir = ""
                    sources.append("${CMAKE_CURRENT_LIST_DIR}/" + self.PRIVATE_DIR + _dir + source)
        for root, dirs, files in os.walk(header_path):
            for header in files:
                if header.endswith(".hpp"):
                    _dir = os.path.relpath(root, header_path)
                    if not (_dir == "."):
                        _dir = _dir + "/"
                    else:
                        _dir = ""
                    headers.append("${CMAKE_CURRENT_LIST_DIR}/" + self.PUBLIC_DIR + _dir + header)

        sources_str = ""
        headers_str = ""

        for src in sources:
            sources_str = sources_str + "\n\t" + src
        for h in headers:
            headers_str = headers_str + "\n\t" + h

        # Generate file from template

        values = {
            "MODULE_NAME":module,
            "MODULE_NAME_UPPER":to_snake_case(module).upper(),
            "DOMAIN_NAME":domain,
            "DOMAIN_NAME_UPPER":to_snake_case(domain).upper(),
            "CMAKE_DEPENDENCIES":dependency_str,
            "SOURCES":sources_str,
            "HEADERS":headers_str,
            "BUILD_INSTRUCTION":build_instruction,
            "CMAKE_CUSTOM_INSTRUCTIONS":custom_instruction,
            "BUILD_TARGET":build_target.name,
            "BUILD_TARGET_TYPE":build_target.value,
            "BUILD_SHARED_LIBS_B":"1" if build_target is BuildTarget.Shared else "0"
        }

        values.update(self.PROJECT_DICT_CONSTANTS)

        self.__generate_file_from_temp(
            module_path + "CMakeLists.txt",
            "ModuleCMake.tmp",
            values
        )

        print("Finished generating CMakeLists.txt for " + domain + " module '" + module + "'.")
        return 1

    def __generate_api_header(self, domain, module):
        from string import Template

        if not self.__check_module_exists(domain, module):
            print_error("Module '" + domain + " " + module + "' does not exist. Exiting generation.")
            return -1

        print("Generating module API header for " + domain + " module '" + module + "'...")

        # Read in JSON data
        json_data = self.__get_json_data(domain, module)
        if json_data == None:
            print("Encountered an error when getting JSON data, exiting API header generation.")
            return -1

        # -- Check if GenerateAPI is enabled, exit with message if not
        if not json_data.generate_api:
            print("API header generation is disabled for " + domain + " module '" + module + "'.")
            return 0

        # -- Read in dependencies from JSON

        dependencies = json_data.dependencies

        dep_temp_str = "#include \"${DEPENDENCY}.hpp\"\n"
        dep_temp = Template(dep_temp_str)

        dependency_str = ""

        for dep in dependencies:
            if not self.__check_module_exists(dep.domain, dep.module):
                print_error("Module '" + dep.domain + " " + dep.module + "' does not exist. Skipping.")
            else:
                dep_values = {
                    "DEPENDENCY_DOMAIN": dep.domain,
                    "DEPENDENCY": dep.module
                }
                dependency_str = dependency_str + dep_temp.safe_substitute(dep_values)

        # Generate file from template

        values = {
            "MODULE_NAME":module,
            "MODULE_NAME_UPPER":to_snake_case(module).upper(),
            "DOMAIN_NAME":domain,
            "DOMAIN_NAME_UPPER":to_snake_case(domain).upper(),
            "API_DEPENDENCIES":dependency_str
        }

        values.update(self.PROJECT_DICT_CONSTANTS)

        self.__generate_file_from_temp(
            self.__get_module_path(domain, module) + self.PUBLIC_DIR + module + "API.hpp",
            "ModuleHeaderAPI.tmp",
            values
        )
            
        print("Finished generating API header for " + domain + " module '" + module + "'.")
        return 1

    def __generate_module_header(self, domain, module):
        from string import Template

        if not self.__check_module_exists(domain, module):
            print_error("Module '" + domain + " " + module + "' does not exist. Exiting generation.")
            return -1

        print("Generating module composite header for " + domain + " module '" + module + "'...")

        
        # Read in JSON data
        json_data = self.__get_json_data(domain, module)
        if json_data == None:
            print("Encountered an error when getting JSON data, exiting composite header generation.")
            return -1

        # -- Check if GenerateAPI is enabled, exit with message if not
        if not json_data.generate_composite_h:
            print("composite header generation is disabled for " + domain + " module '" + module + "'.")
            return 0

        # Create header file lists

        headers = []
        header_path = self.__get_module_path(domain, module) + self.PUBLIC_DIR
        
        for root, dirs, files in os.walk(header_path):
            for header in files:
                if header.endswith(".hpp"):
                    if not (header == (module + ".hpp") or header == (module + "API.hpp")):
                        _dir = os.path.relpath(root, header_path)
                        if not (_dir == "."):
                            _dir = _dir + "/"
                        else:
                            _dir = ""
                        headers.append("#include \"" + _dir + header + "\"")

        headers_str = ""

        for h in headers:
            headers_str = headers_str + "\n" + h

        # Generate file from template

        values = {
            "MODULE_NAME":module,
            "MODULE_NAME_UPPER":to_snake_case(module).upper(),
            "DOMAIN_NAME":domain,
            "DOMAIN_NAME_UPPER":to_snake_case(domain).upper(),
            "HEADER_FILES":headers_str
        }

        values.update(self.PROJECT_DICT_CONSTANTS)
            
        # Generate module header file
        self.__generate_file_from_temp(
            self.__get_module_path(domain, module) + self.PUBLIC_DIR + module + ".hpp",
            "ModuleHeader.tmp",
            values
        )
            
        print("Finished generating composite header for " + domain + " module '" + module + "'.")
        return 1

    def __generate_interface(self, domain, module):
        # Generates the interface header and source files for the specified module
        pass

    def __regen_module(self, domain, module):
        composite_result = self.__generate_module_header(domain, module)
        api_result = self.__generate_api_header(domain, module)
        cmake_result = self.__generate_cmake(domain, module)
        if cmake_result == -1:
            print("Failed to update CMakeLists.txt")
        elif cmake_result == 0:
            print("WARNING: CMakeLists.txt generation is disabled for this module")
        elif cmake_result == 1:
            print("Regenerated CMakeLists.txt using updated source and dependency lists for module '" + domain + " " + module + "'.")
        else:
            print("UNKNOWN ERROR: Failed to update CMakeLists.txt")
        if api_result == -1:
            print("Failed to update API header")
        elif api_result == 0:
            print("WARNING: API header generation is disabled for this module")
        elif api_result == 1:
            print("Regenerated " + module + "API.hpp using updated source and dependency lists for module '" + domain + " " + module + "'.")
        else:
            print("UNKNOWN ERROR: Failed to update API header")
        if composite_result == -1:
            print("Failed to update composite header")
        elif composite_result == 0:
            print("WARNING: Composite header generation is disabled for this module")
        elif composite_result == 1:
            print("Regenerated " + module + ".hpp using the updated header list for module '" + domain + " " + module + "'.")
        else:
            print("UNKNOWN ERROR: Failed to update API header")
        return


### START ### --- JSON utility functions

    def __get_json_data(self, domain, module):

        try:
            json_file = open(self.__get_module_path(domain, module) + "Module.json", "r")

            json_src = json_file.read()
            json_dct = json.loads(json_src)
            data = self.__decode_module(json_dct)

            json_file.close()

            return data
        
        except OSError as e:
            print_error("Error thrown when getting json data:")
            print_error("%s - %s." % (e.filename, e.strerror))
            return None

    def __write_json_data(self, domain, module, data):
        
        try:
            json_file = open(self.__get_module_path(domain, module) + "Module.json", "w")

            json.dump(self.__encode_module(data), json_file, indent=4)

            json_file.close()

            return True
        
        except OSError as e:
            print_error("Error thrown when writing json data:")
            print_error("%s - %s." % (e.filename, e.strerror))
            return False

    def __decode_module(self, dct):
        return Module(
            dct["Domain"],
            dct["Name"],
            BuildTarget[dct["BuildTarget"]],
            self.__decode_dependencies(dct),
            dct["GenerateCMake"] == "True",
            dct["GenerateAPI"] == "True",
            dct["GenerateCompositeHeader"] == "True",
            dct["CustomCMakeInstructions"]
            )

    def __encode_module(self, module):
        data = {
            "Domain": module.domain,
            "Name": module.name,
            "BuildTarget": str(module.build_target),
            "Dependencies": self.__encode_dependencies(module),
            "GenerateCMake": str(module.generate_cmake),
            "GenerateAPI": str(module.generate_api),
            "GenerateCompositeHeader": str(module.generate_composite_h),
            "CustomCMakeInstructions": module.custom_cmake_instructions
        }
        return data

    def __decode_dependencies(self, dct):
        dependencies = []
        for dep in dct["Dependencies"]:
            dependencies.append(Dependency(dep["Domain"], dep["Module"]))
        return dependencies

    def __encode_dependencies(self, module):
        dependencies = []
        for dep in module.dependencies:
            dependencies.append( { "Domain": dep.domain, "Module": dep.module } )
        return dependencies


# Main execution

if __name__ == '__main__':
    SeedEngineCLI()