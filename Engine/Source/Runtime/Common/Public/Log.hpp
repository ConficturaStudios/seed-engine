/**
 * Log.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COMMON_LOG_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COMMON_LOG_H_

#include "CommonAPI.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace seedengine {

    // TODO: Create Logger instances for System library or other global sources

    /**
     * @brief A logger capable of printing to the standard output and standard error streams.
     * @details This is the logging utility used for debugging and console output.
     * 
     */
    class ENGINE_API Logger final {

        public:

            // TODO: Document Logger class

            /**
             * The importance level of a message or logger.
             */
            enum class Level : int {
                Trace = spdlog::level::level_enum::trace,
                Debug = spdlog::level::level_enum::debug,
                Info = spdlog::level::level_enum::info,
                Warn = spdlog::level::level_enum::warn,
                Error = spdlog::level::level_enum::err,
                Critical = spdlog::level::level_enum::critical,
                Off = spdlog::level::level_enum::off
            };
            
            explicit Logger(const char* name, const char *pattern = "%^[%T] %n: %v%$ [Thread %t]",
                    Logger::Level level = Logger::Level::Trace);

            template <typename FormatString, typename... Args>
            inline void log(Level level, const FormatString& fmt, const Args&... args) {
                m_inst->log(static_cast<spdlog::level::level_enum>(level), fmt, args...);
            }

            template <typename FormatString, typename... Args>
            inline void log(const FormatString& fmt, const Args&... args) {
                m_inst->log(fmt, args...);
            }

            template <typename FormatString, typename... Args>
            inline void trace(const FormatString& fmt, const Args&... args) {
                m_inst->trace(fmt, args...);
            }

            template <typename FormatString, typename... Args>
            inline void debug(const FormatString& fmt, const Args&... args) {
                #ifdef ENGINE_COMPILE_DEBUG
                    m_inst->debug(fmt, args...);
                #endif
            }

            template <typename FormatString, typename... Args>
            inline void info(const FormatString& fmt, const Args&... args) {
                m_inst->info(fmt, args...);
            }

            template <typename FormatString, typename... Args>
            inline void warn(const FormatString& fmt, const Args&... args) {
                m_inst->warn(fmt, args...);
            }

            template <typename FormatString, typename... Args>
            inline void error(const FormatString& fmt, const Args&... args) {
                m_inst->error(fmt, args...);
            }

            template <typename FormatString, typename... Args>
            inline void critical(const FormatString& fmt, const Args&... args) {
                m_inst->critical(fmt, args...);
            }

        private:

            std::shared_ptr<spdlog::logger> m_inst;
    };

}

// TODO: Replace macro logging calls with calls to a logger within system or other global source

#define ENGINE_TRACE(...)
#ifdef ENGINE_COMPILE_DEBUG
    #define ENGINE_DEBUG(...)
#else
    #define ENGINE_DEBUG(...)
#endif
#define ENGINE_INFO(...)
#define ENGINE_WARN(...)
#define ENGINE_ERROR(...)
#define ENGINE_CRIT(...)

#define CLIENT_TRACE(...)
#define CLIENT_DEBUG(...)
#define CLIENT_INFO(...)
#define CLIENT_WARN(...)
#define CLIENT_ERROR(...)
#define CLIENT_CRIT(...)

#endif