#ifndef SEEDENGINE_INCLUDE_PARSER_H_
#define SEEDENGINE_INCLUDE_PARSER_H_

#include "Core.hpp"

namespace seedengine {
    namespace util {
        namespace parser {
            namespace ini {
                // A struct that contains relevant data within a single section of an *.ini file
                struct section {

                    // All integers within this section
                    std::map<string, const int> int_data;
                    // All floats within this section
                    std::map<string, const float> float_data;
                    // All booleans within this section
                    std::map<string, const bool> bool_data;
                    // All strings within this section
                    std::map<string, const string> string_data;

                };

                // A structure to encapsulate *.ini files.
                struct filedata {
                    // The absolute path to this file
                    string filepath;
                    // All sections mapped to their header
                    std::map<string, section> sections;

                };

                // Parses an ini file and returns a data structure that can access all key value pairs from the file.
                // @param(string) filepath: The file path to the ini file to parse.
                // @returns: An iniFile data structure with the parsed data.
                filedata parse(string);

                // Data from the defaults.ini file found in ~/seed-engine/core/data.
                extern filedata DEFAULTS;
            }
        }
    }
}

#endif