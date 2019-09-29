#include "Parser.hpp"

namespace seedengine {
    namespace util {

        IniParser DEFAULTS(CORE_PATH("data/defaults.ini"));

        // Parser

        Parser::Parser(string filepath) {
            //file_ = std::ifstream();
        }

        Parser::~Parser() {
            if (file_.is_open()) file_.close();
        }

        void Parser::print() const {
            ENGINE_INFO("Printing parser contents...");
        }

        // INI Parser

        IniParser::IniParser(string filepath) : Parser(filepath) {
            parsed_data = ini_data();
            parse(filepath);
        }

        void IniParser::parse(string filepath) {

            // Regex templates in ECMAScript format

            std::regex white_regex("^[\\s]*$");
            std::regex section_regex("^[\\s]*(\\[\\s*([a-zA-Z][\\w]*(?:\\.[\\w]+)?)\\s*\\])\\s*$");
            std::regex int_regex("^[\\s]*([a-zA-Z][\\w]*)\\s*=\\s*(-?[0-9]+)\\s*$");
            std::regex float_regex("^[\\s]*([a-zA-Z][\\w]*)\\s*=\\s*(-?[0-9]*\\.(?:[0-9]*)?)\\s*$");
            std::regex bool_regex("^[\\s]*([a-zA-Z][\\w]*)\\s*=\\s*([Tt]rue|TRUE|[Ff]alse|FALSE)\\s*$");
            std::regex string_regex("^[\\s]*([a-zA-Z][\\w]*)\\s*=\\s*(?:\"([^\"]*)\"|'([^\']*)')\\s*$");

            // Read the passed file

            file_.open(filepath, std::ios::in);

            if (file_.is_open()) {

                // The name of the active section
                string active_section;

                std::string line;
                int line_num = 0;

                while (std::getline(file_, line)) {

                    std::smatch m;

                    ENGINE_DEBUG(line);

                    // Remove comments
                    string no_comment_line = line.substr(0, line.find(";", 0));
                    no_comment_line = no_comment_line.substr(0, no_comment_line.find("#", 0));

                    if (std::regex_match(no_comment_line, m, white_regex)) {
                        // Skip line
                    }
                    else if (std::regex_match(no_comment_line, m, section_regex)) {
                        active_section = m[2];
                        // Check if section exists
                        if (parsed_data.find(active_section) == parsed_data.end()) {

                            // Create storage for this section
                            ints int_data = ints();
                            floats float_data = floats();
                            bools bool_data = bools();
                            strings string_data = strings();

                            section s = {
                                int_data,
                                float_data,
                                string_data,
                                bool_data
                            };

                            parsed_data.insert(std::pair<string, section>(active_section, s));
                        }
                        // Note: allows repeating a header, will append additional data. key value pairs will however overwrite if repeated
                    }
                    else if (active_section.empty()) {
                        ENGINE_ERROR("Error in ini file \"" + filepath + "\" at line " + std::to_string(line_num) + ": no section header defined.");
                    }
                    else if (std::regex_match(no_comment_line, m, int_regex)) {
                        const int v = std::stoi(m[2]);
                        parsed_data.at(active_section).int_data.insert(std::pair<string, const int>(m[1], v));
                    }
                    else if (std::regex_match(no_comment_line, m, float_regex)) {
                        const float v = std::stof(m[2]);
                        parsed_data.at(active_section).float_data.insert(std::pair<string, const float>(m[1], v));
                    }
                    else if (std::regex_match(no_comment_line, m, bool_regex)) {
                        const bool v = (m[2] == "true" || m[2] == "True" || m[2] == "TRUE");
                        parsed_data.at(active_section).bool_data.insert(std::pair<string, const bool>(m[1], v));
                    }
                    else if (std::regex_match(no_comment_line, m, string_regex)) {
                        const string v = (m[2].str().empty()) ? m[3] : m[2];
                        parsed_data.at(active_section).string_data.insert(std::pair<string, const string>(m[1], v));
                    }
                    else {
                        ENGINE_ERROR("Error in ini file \"" + filepath + "\" at line " + std::to_string(line_num));
                    }

                    line_num++;
                }

                file_.close();
                
            }


        }

        int IniParser::get(const string& section, const string& key, int& out) const {
            return out = parsed_data.at(section).int_data.at(key);
        }

        float IniParser::get(const string& section, const string& key, float& out) const {
            return out = parsed_data.at(section).float_data.at(key);
        }

        bool IniParser::get(const string& section, const string& key, bool& out) const {
            return out = parsed_data.at(section).bool_data.at(key);
        }

        string IniParser::get(const string& section, const string& key, string& out) const {
            return out = parsed_data.at(section).string_data.at(key);
        }

        int IniParser::getInt(const string& section, const string& key) const {
            return parsed_data.at(section).int_data.at(key);
        }

        float IniParser::getFloat(const string& section, const string& key) const {
            return parsed_data.at(section).float_data.at(key);
        }

        bool IniParser::getBool(const string& section, const string& key) const {
            return parsed_data.at(section).bool_data.at(key);
        }

        string IniParser::getString(const string& section, const string& key) const {
            return parsed_data.at(section).string_data.at(key);
        }

        void IniParser::print() const {
            Parser::print();
            if (parsed_data.empty()) {
                ENGINE_INFO("Parser is empty.");
                return;
            }
            for (auto it = parsed_data.begin(); it != parsed_data.end(); ++it) {
                ENGINE_INFO("Section: " + it->first);
                for (auto i = parsed_data.at(it->first).int_data.begin(); i != parsed_data.at(it->first).int_data.end(); ++i) {
                    ENGINE_INFO("Int: [" + i->first + "]");
                }
                for (auto i = parsed_data.at(it->first).float_data.begin(); i != parsed_data.at(it->first).float_data.end(); ++i) {
                    ENGINE_INFO("Float: [" + i->first + "]");
                }
                for (auto i = parsed_data.at(it->first).bool_data.begin(); i != parsed_data.at(it->first).bool_data.end(); ++i) {
                    ENGINE_INFO("Bool: [" + i->first + "]");
                }
                for (auto i = parsed_data.at(it->first).string_data.begin(); i != parsed_data.at(it->first).string_data.end(); ++i) {
                    ENGINE_INFO("String: [" + i->first + "]");
                }
            }
        }

        // Binary Parser

        BinaryParser::BinaryParser(string filepath) : Parser(filepath) {
            file_.open(filepath, std::ios::in | std::ios::binary);
            file_.seekg(0, file_.end);
            length_ = file_.tellg();
            file_.seekg(0, file_.beg);
            pos_ = 0;
        }


        bool BinaryParser::getNext(uint32_t* out) {
            if ((unsigned int)pos_ + sizeof(*out) > length_) return false;
            // Navigate to current file location
            file_.seekg(pos_);
            // Read in bytes in Big Endian Format (Network byte order)
            file_.read(reinterpret_cast<char*>(out), sizeof(*out));
            *out = ntohl(*out); // Convert to host byte order
            pos_ += sizeof(*out); // Iterate file position
            return true;
        }

        bool BinaryParser::getNext(uint16_t* out) {
            if ((unsigned int)pos_ + sizeof(*out) > length_) return false;
            // Navigate to current file location
            file_.seekg(pos_);
            // Read in bytes in Big Endian Format (Network byte order)
            file_.read(reinterpret_cast<char*>(out), sizeof(*out));
            *out = ntohs(*out); // Convert to host byte order
            pos_ += sizeof(*out); // Iterate file position
            return true;
        }

        bool BinaryParser::getNext(uint8_t* out) {
            if ((unsigned int)pos_ + sizeof(*out) > length_) return false;
            // Navigate to current file location
            file_.seekg(pos_);
            file_.read(reinterpret_cast<char*>(out), sizeof(*out));
            pos_ += sizeof(*out); // Iterate file position
            return true;
        }

        bool BinaryParser::getNext(float* out) {
            if ((unsigned int)pos_ + sizeof(*out) > length_) return false;
            // Navigate to current file location
            file_.seekg(pos_);
            uint32_t buffer = 0;
            // Read in bytes in Big Endian Format (Network byte order)
            file_.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
            *out = ntohf(buffer); // Convert to host byte order
            pos_ += sizeof(*out); // Iterate file position
            return true;
        }

        std::vector<char> BinaryParser::getBuffer(const std::streampos& start, const std::streampos& end) {
            if (start >= end) {
                ENGINE_WARN("Invalid buffer range provided.");
                return {};
            }
            if (start + end > length_) {
                ENGINE_WARN("Reguested byte buffer exceeds file bounds.");
                return {};
            }
            file_.seekg(start);
            std::streamoff size = end - start;
            std::vector<char> values{};
            values.reserve((unsigned int)size);
            file_.read(values.data(), size);
            file_.seekg(pos_);
            return values;
        }

        std::vector<char> BinaryParser::getNextBuffer(const std::streamoff& size) {
            if (pos_ + size > length_) {
                ENGINE_WARN("Reguested byte buffer exceeds file bounds.");
                return {};
            }
            file_.seekg(pos_);
            std::vector<char> values{};
            values.reserve((unsigned int)size);
            file_.read(values.data(), size);
            pos_ += size; // Iterate file position
            return values;
        }

        void BinaryParser::print() const {
            Parser::print();
            ENGINE_WARN("Printing is not implemented for binary parser.");
        }
    }
}