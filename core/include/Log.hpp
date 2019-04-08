#ifndef SEEDENGINE_INCLUDE_LOG_H_
#define SEEDENGINE_INCLUDE_LOG_H_

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Engine {

    // Used for all debugging and message logging
    class Log {

    public:
        
        static void init();

        inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return engine_logger_; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return client_logger_; }

    private:

        static std::shared_ptr<spdlog::logger>& engine_logger_;
        static std::shared_ptr<spdlog::logger>& client_logger_;

    };
}

//TODO: Modify code to check for ENGINE_COMPILE_DEBUG

#define ENGINE_TRACE(...) Engine::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define ENGINE_DEBUG(...) Engine::Log::GetEngineLogger()->debug(__VA_ARGS__)
#define ENGINE_INFO(...) Engine::Log::GetEngineLogger()->info(__VA_ARGS__)
#define ENGINE_WARN(...) Engine::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define ENGINE_ERROR(...) Engine::Log::GetEngineLogger()->error(__VA_ARGS__)
#define ENGINE_CRIT(...) Engine::Log::GetEngineLogger()->critical(__VA_ARGS__)

#define CLIENT_TRACE(...) Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CLIENT_DEBUG(...) Engine::Log::GetClientLogger()->debug(__VA_ARGS__)
#define CLIENT_INFO(...) Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define CLIENT_WARN(...) Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CLIENT_ERROR(...) Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define CLIENT_CRIT(...) Engine::Log::GetClientLogger()->critical(__VA_ARGS__)

#endif