#ifndef SEEDENGINE_INCLUDE_PARSER_H_
#define SEEDENGINE_INCLUDE_PARSER_H_

#include "Core.hpp"

namespace seedengine {
    namespace util {

        class Parser {

        protected:

            Parser() = delete;
            Parser(string filepath);

            virtual void parse(string filepath) = 0;

        };

        class IniParser final : public Parser {

        public:

            IniParser() = delete;
            IniParser(string filepath);


            int    get(const string& section, const string& key, int&    out) const;
            float  get(const string& section, const string& key, float&  out) const;
            bool   get(const string& section, const string& key, bool&   out) const;
            string get(const string& section, const string& key, string& out) const;

            int    getInt(   const string& section, const string& key) const;
            float  getFloat( const string& section, const string& key) const;
            bool   getBool(  const string& section, const string& key) const;
            string getString(const string& section, const string& key) const;

            void print() const;

        protected:

            void parse(string filepath) override;

        private:

            typedef std::map<string, const int> ints;
            typedef std::map<string, const float> floats;
            typedef std::map<string, const string> strings;
            typedef std::map<string, const bool> bools;

            struct section {
                ints int_data;
                floats float_data;
                strings string_data;
                bools bool_data;
            };

            typedef std::map<string, section> ini_data;

            ini_data parsed_data;

        };

        extern IniParser DEFAULTS;
    }
}

#endif