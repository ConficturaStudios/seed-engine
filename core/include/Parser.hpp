#ifndef SEEDENGINE_INCLUDE_PARSER_H_
#define SEEDENGINE_INCLUDE_PARSER_H_

#include "Core.hpp"

namespace seedengine {
    namespace util {

        /**
         * @brief The base class for all file parsers.
         * @details
         */
        class Parser {

        protected:
            /** Removed default Parser constructor. */
            Parser() = delete;
            /**
             * @brief Constructs a new Parser object.
             * 
             * @param filepath The path of the file to parse.
             */
            Parser(string filepath);

            /**
             * @brief Parses the file at filepath.
             * 
             * @param filepath The path of the file to parse.
             */
            virtual void parse(string filepath) = 0;

        };

        /**
         * @brief A parser for .ini files.
         * @details
         */
        class IniParser final : public Parser {

        public:
            /** Removed default INI Parser constructor. */
            IniParser() = delete;
            /**
             * @brief Constructs a new INI Parser.
             * 
             * @param filepath The path of the file to parse.
             */
            IniParser(string filepath);

            /**
             * @brief Gets the value associated with the section and key provided.
             * 
             * @param section The section of the .ini file to check.
             * @param key The key associated with the value to get.
             * @param out A reference that is passed the requested value.
             * @return int The requested value.
             */
            int    get(const string& section, const string& key, int&    out) const;
            /**
             * @brief Gets the value associated with the section and key provided.
             * 
             * @param section The section of the .ini file to check.
             * @param key The key associated with the value to get.
             * @param out A reference that is passed the requested value.
             * @return float The requested value.
             */
            float  get(const string& section, const string& key, float&  out) const;
            /**
             * @brief Gets the value associated with the section and key provided.
             * 
             * @param section The section of the .ini file to check.
             * @param key The key associated with the value to get.
             * @param out A reference that is passed the requested value.
             * @return bool The requested value.
             */
            bool   get(const string& section, const string& key, bool&   out) const;
            /**
             * @brief Gets the value associated with the section and key provided.
             * 
             * @param section The section of the .ini file to check.
             * @param key The key associated with the value to get.
             * @param out A reference that is passed the requested value.
             * @return string The requested value.
             */
            string get(const string& section, const string& key, string& out) const;

            /**
             * @brief Gets the integer value associated with the section and key provided.
             * 
             * @param section The section of the .ini file to check.
             * @param key The key associated with the value to get.
             * @return int The requested value.
             */
            int    getInt(   const string& section, const string& key) const;
            /**
             * @brief Gets the float value associated with the section and key provided.
             * 
             * @param section The section of the .ini file to check.
             * @param key The key associated with the value to get.
             * @return float The requested value.
             */
            float  getFloat( const string& section, const string& key) const;
            /**
             * @brief Gets the boolean value associated with the section and key provided.
             * 
             * @param section The section of the .ini file to check.
             * @param key The key associated with the value to get.
             * @return bool The requested value.
             */
            bool   getBool(  const string& section, const string& key) const;
            /**
             * @brief Gets the string value associated with the section and key provided.
             * 
             * @param section The section of the .ini file to check.
             * @param key The key associated with the value to get.
             * @return string The requested value.
             */
            string getString(const string& section, const string& key) const;

            /** Prints the contents of this .ini file to the console. */
            void print() const;

        protected:

            /**
             * @brief Parses the file at filepath.
             * 
             * @param filepath The path of the file to parse.
             */
            void parse(string filepath) override;

        private:

            typedef std::map<string, const int> ints;
            typedef std::map<string, const float> floats;
            typedef std::map<string, const string> strings;
            typedef std::map<string, const bool> bools;

            /** A section of an .ini file. */
            struct section {
                ints int_data;
                floats float_data;
                strings string_data;
                bools bool_data;
            };

            typedef std::map<string, section> ini_data;

            /** The data contained within the parsed file. */
            ini_data parsed_data;

        };

        extern IniParser DEFAULTS;
    }
}

#endif