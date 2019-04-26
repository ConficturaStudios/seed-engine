#ifndef SEEDENGINE_INCLUDE_LOG_H_
#define SEEDENGINE_INCLUDE_LOG_H_

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace seedengine {

    // Used for all debugging and message logging
    class Log {

    public:
        
        // Initializes the logger.
        static void init();

        // Returns the logger for the engine core.
        // @returns: The logger for the engine core.
        inline static std::shared_ptr<spdlog::logger> GetEngineLogger() { return engine_logger_; }
        // Returns the logger for the client software.
        // @returns: The logger for the client software.
        inline static std::shared_ptr<spdlog::logger> GetClientLogger() { return client_logger_; }

    private:

        // The engine core logger.
        static std::shared_ptr<spdlog::logger> engine_logger_;
        // The client side logger.
        static std::shared_ptr<spdlog::logger> client_logger_;

    };
}

//TODO: Modify code to check for ENGINE_COMPILE_DEBUG

#define ENGINE_TRACE(...) seedengine::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define ENGINE_DEBUG(...) seedengine::Log::GetEngineLogger()->debug(__VA_ARGS__)
#define ENGINE_INFO(...) seedengine::Log::GetEngineLogger()->info(__VA_ARGS__)
#define ENGINE_WARN(...) seedengine::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define ENGINE_ERROR(...) seedengine::Log::GetEngineLogger()->error(__VA_ARGS__)
#define ENGINE_CRIT(...) seedengine::Log::GetEngineLogger()->critical(__VA_ARGS__)

#define CLIENT_TRACE(...) seedengine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CLIENT_DEBUG(...) seedengine::Log::GetClientLogger()->debug(__VA_ARGS__)
#define CLIENT_INFO(...) seedengine::Log::GetClientLogger()->info(__VA_ARGS__)
#define CLIENT_WARN(...) seedengine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CLIENT_ERROR(...) seedengine::Log::GetClientLogger()->error(__VA_ARGS__)
#define CLIENT_CRIT(...) seedengine::Log::GetClientLogger()->critical(__VA_ARGS__)

#endif