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

    std::shared_ptr<spdlog::logger> Log::engine_logger_ = spdlog::stdout_color_mt("Seed Engine");
    std::shared_ptr<spdlog::logger> Log::client_logger_ = spdlog::stdout_color_mt("Client");

    void Log::init() {
        spdlog::set_pattern("%^[%T] %n: %v%$ [Thread %t]");
        
        Log::engine_logger_->set_level(spdlog::level::trace);
        
        Log::client_logger_->set_level(spdlog::level::trace);
        
    }

    std::shared_ptr<spdlog::logger> Log::getEngineLogger() {
        return engine_logger_;
    }
    
    std::shared_ptr<spdlog::logger> Log::getClientLogger() {
        return client_logger_;
    }

}