#include <Log.hpp>

namespace seedengine {

    std::shared_ptr<spdlog::logger> Log::engine_logger_ = spdlog::stdout_color_mt("Seed Engine");
    std::shared_ptr<spdlog::logger> Log::client_logger_ = spdlog::stdout_color_mt("Client");

    void Log::init() {
        spdlog::set_pattern("%^[%T] %n: %v%$ [Thread %t]");
        
        Log::engine_logger_->set_level(spdlog::level::trace);
        
        Log::client_logger_->set_level(spdlog::level::trace);
        
    }
}