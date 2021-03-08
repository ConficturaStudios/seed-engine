/**
 * Log.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "Log.hpp"

namespace seedengine {

    Logger::Logger(const char *name, const char *pattern = "%^[%T] %n: %v%$ [Thread %t]",
                   Logger::Level level = Logger::Level::Trace) {
        m_inst = spdlog::stdout_color_mt(name);
        m_inst->set_pattern(pattern);
        m_inst->set_level(static_cast<spdlog::level::level_enum>(level));
    }
}