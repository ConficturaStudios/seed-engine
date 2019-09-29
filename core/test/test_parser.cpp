// test_parser.cpp

#include <iostream>
#include <gtest/gtest.h>
#include "Parser.hpp"

TEST(ParserTest, GeneralTest) {
    using namespace seedengine;

    util::IniParser parser(CORE_PATH("data/defaults.ini"));

    float ups, upsd;
    parser.get("Engine", "target_ups", ups);
    util::DEFAULTS.get("Engine", "target_ups", upsd);
    EXPECT_EQ(30.0f, ups);
    EXPECT_EQ(30.0f, upsd);
    EXPECT_EQ(upsd, ups);
    
}