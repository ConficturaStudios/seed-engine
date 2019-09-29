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

            virtual ~Parser();

            /** Prints the contents of this file to the console. */
            virtual void print() const = 0;

            /** The file being parsed. */
            std::ifstream file_;
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
            void print() const override;

        protected:

            /**
             * @brief Parses the file at filepath.
             * 
             * @param filepath The path of the file to parse.
             */
            void parse(string filepath);

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

        /** The values stored in defaults.ini. */
        extern IniParser DEFAULTS;


        /**
         * @brief A parser for binary files.
         * @details
         */
        class BinaryParser final : public Parser {

        public:

            /** Removed default Binary Parser constructor. */
            BinaryParser() = delete;
            /**
             * @brief Constructs a new Binary Parser.
             *
             * @param filepath The path of the file to parse.
             * @param byte_order The byte order used in the file to parse.
             */
            BinaryParser(string filepath);

            virtual ~BinaryParser() = default;

            /**
             * @brief Gets the next requesed value from the binary file.
             * @details
             *
             * @param out A pointer to the output variable to store the value in.
             * @return true If the request is successful.
             * @return false If the request fails.
             */
            bool getNext(uint32_t* out);
            /**
             * @brief Gets the next requesed value from the binary file.
             * @details
             *
             * @param out A pointer to the output variable to store the value in.
             * @return true If the request is successful.
             * @return false If the request fails.
             */
            bool getNext(uint16_t* out);
            /**
             * @brief Gets the next requesed value from the binary file.
             * @details
             *
             * @param out A pointer to the output variable to store the value in.
             * @return true If the request is successful.
             * @return false If the request fails.
             */
            bool getNext(uint8_t* out);
            /**
             * @brief Gets the next requesed value from the binary file.
             * @details
             *
             * @param out A pointer to the output variable to store the value in.
             * @return true If the request is successful.
             * @return false If the request fails.
             */
            bool getNext(float* out);

            /**
             * @brief Gets the requesed byte buffer from the binary file.
             * @details
             *
             * @param start The point in the file to start the buffer.
             * @param end The point in the file to end the buffer.
             * @return std::vector<char> The requested buffer. Empty on failure.
             */
            std::vector<char> getBuffer(const std::streampos& start, const std::streampos& end);
            /**
             * @brief Gets the requesed byte buffer from the binary file.
             * @details
             *
             * @param size The size of the byte buffer to gather.
             * @return std::vector<char> The requested buffer. Empty on failure.
             */
            std::vector<char> getNextBuffer(const std::streamoff& size);

            /** Prints the contents of this binary file to the console as a stream of bytes. */
            void print() const override;

        protected:

        private:

            /** The position in the parsed file. */
            std::streampos pos_;
            /** The length of the binary file. */
            std::streampos length_;

        };
    }
}

#endif