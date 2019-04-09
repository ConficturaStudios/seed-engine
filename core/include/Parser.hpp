#ifndef SEEDENGINE_INCLUDE_PARSER_H_
#define SEEDENGINE_INCLUDE_PARSER_H_

#include "Core.hpp"

namespace seedengine {
    namespace util {

        // A parser for processing files for the program.
        // Note: Does not include .lua support, use the Lua class for this.
        class Parser {

        public:

            // A struct that contains relevant data within a single section of an ini file
            struct iniSection {
                
                // All integers within this section
                std::map<std::string, const int> int_data;
                // All floats within this section
                std::map<std::string, const float> float_data;
                // All booleans within this section
                std::map<std::string, const bool> bool_data;
                // All strings within this section
                std::map<std::string, const std::string&> string_data;

            };

            // A structure to encapsulate ini files.
            struct iniFile {
                // The absolute path to this file
                std::string filepath;
                // All sections mapped to their header
                std::map<std::string, iniSection> sections;

            };

            // Parses an ini file and returns a data structure that can access all key value pairs from the file.
            // @param(std::string) filepath: The file path to the ini file to parse.
            // @returns: An iniFile data structure with the parsed data.
            static iniFile parseINI(std::string);

        private:



        };

    }
}

#endif