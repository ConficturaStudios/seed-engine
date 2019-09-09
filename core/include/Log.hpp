#ifndef SEEDENGINE_INCLUDE_LOG_H_
#define SEEDENGINE_INCLUDE_LOG_H_

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace seedengine {

    /*
     * @brief Used for all debugging and message logging.
     * @details
     */
    class Log {

    public:
        
        /** Initializes the logger. */
        static void init();

        /**
         * @brief Returns the logger for the engine core.
         * 
         * @return std::shared_ptr<spdlog::logger> The logger for the engine core.
         */
        inline static std::shared_ptr<spdlog::logger> getEngineLogger() { return engine_logger_; }
        
        /**
         * @brief Returns the logger for the client software.
         * 
         * @return std::shared_ptr<spdlog::logger> The logger for the client software.
         */
        inline static std::shared_ptr<spdlog::logger> getClientLogger() { return client_logger_; }

    private:

        /** The engine core logger. */
        static std::shared_ptr<spdlog::logger> engine_logger_;
        /** The client side logger. */
        static std::shared_ptr<spdlog::logger> client_logger_;

    };
}

#define ENGINE_TRACE(...) seedengine::Log::getEngineLogger()->trace(__VA_ARGS__)
#ifdef ENGINE_COMPILE_DEBUG
    #define ENGINE_DEBUG(...) seedengine::Log::getEngineLogger()->debug(__VA_ARGS__)
#else
    #define ENGINE_DEBUG(...)
#endif
#define ENGINE_INFO(...) seedengine::Log::getEngineLogger()->info(__VA_ARGS__)
#define ENGINE_WARN(...) seedengine::Log::getEngineLogger()->warn(__VA_ARGS__)
#define ENGINE_ERROR(...) seedengine::Log::getEngineLogger()->error(__VA_ARGS__)
#define ENGINE_CRIT(...) seedengine::Log::getEngineLogger()->critical(__VA_ARGS__)

#define CLIENT_TRACE(...) seedengine::Log::getClientLogger()->trace(__VA_ARGS__)
#define CLIENT_DEBUG(...) seedengine::Log::getClientLogger()->debug(__VA_ARGS__)
#define CLIENT_INFO(...) seedengine::Log::getClientLogger()->info(__VA_ARGS__)
#define CLIENT_WARN(...) seedengine::Log::getClientLogger()->warn(__VA_ARGS__)
#define CLIENT_ERROR(...) seedengine::Log::getClientLogger()->error(__VA_ARGS__)
#define CLIENT_CRIT(...) seedengine::Log::getClientLogger()->critical(__VA_ARGS__)

#endif