#include "Parser.hpp"

namespace Engine {
    namespace Util {

        Parser::iniFile Parser::parseINI(std::string filepath) {

            // Regex templates in ECMAScript format

            std::regex white_regex("^[\\s]*$");
            std::regex section_regex("^[\\s]*(\\[\\s*([a-zA-Z][\\w]*)\\s*\\])\\s*$");
            std::regex int_regex("^[\\s]*([a-zA-Z][\\w]*)\\s*=\\s*(-?[0-9]+)\\s*$");
            std::regex float_regex("^[\\s]*([a-zA-Z][\\w]*)\\s*=\\s*(-?[0-9]*\\.(?:[0-9]*)?)\\s*$");
            std::regex bool_regex("^[\\s]*([a-zA-Z][\\w]*)\\s*=\\s*([Tt]rue|TRUE|[Ff]alse|FALSE)\\s*$");
            std::regex string_regex("^[\\s]*([a-zA-Z][\\w]*)\\s*=\\s*(?:\"([^\"]*)\"|'([^\']*)')\\s*$");

            // All sections of this file
            std::map<std::string, iniSection> sections;

            // The name of the active section
            std::string active_section;

            // Read the passed file
            std::ifstream file(filepath);

            std::string line;
            int line_num = 1;
            while (std::getline(file, line)) {
                std::smatch m;

                std::string ncomment_line = line.substr(0, line.find(";", 0));
                ncomment_line = ncomment_line.substr(0, line.find("#", 0));

                if (std::regex_match(ncomment_line, m, white_regex)) {
                    // Skip line
                }
                else if (std::regex_match(ncomment_line, m, section_regex)) {
                    active_section = m[2];
                    // Check if section exists
                    if (sections.find(active_section) != sections.end()) {

                        // Create storage for this section
                        std::map<std::string, int> int_data;
                        std::map<std::string, float> float_data;
                        std::map<std::string, bool> bool_data;
                        std::map<std::string, std::string> string_data;

                        sections[active_section] = {
                            int_data,
                            float_data,
                            bool_data,
                            string_data
                        };
                    }
                    // Note: allows repeating a header, will append additional data. key value pairs will however overwrite if repeated
                }
                else if (active_section.empty()) {
                    ENGINE_ERROR("Error in ini file \"" + filepath + "\" at line " + std::to_string(line_num) + ": no section header defined.");
                }
                else if (std::regex_match(ncomment_line, m, int_regex)) {
                    sections[active_section].int_data[m[1]] = std::stoi(m[2]);
                }
                else if (std::regex_match(ncomment_line, m, float_regex)) {
                    sections[active_section].float_data[m[1]] = std::stof(m[2]);
                }
                else if (std::regex_match(ncomment_line, m, bool_regex)) {
                    sections[active_section].bool_data[m[1]] = (m[2] == "true" || m[2] == "True" || m[2] == "TRUE");
                }
                else if (std::regex_match(ncomment_line, m, string_regex)) {
                    sections[active_section].string_data[m[1]] = (m[3].str().empty()) ? m[4] : m[3];
                }
                else {
                    ENGINE_ERROR("Error in ini file \"" + filepath + "\" at line " + std::to_string(line_num));
                }

                line_num++;
            }

            iniFile ini_file = {
                filepath,
                sections
            };

            return ini_file;

        }

    }
}