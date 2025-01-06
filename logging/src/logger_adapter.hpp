#ifndef LOGGING_LOGGER_ADAPTER_HPP
#define LOGGING_LOGGER_ADAPTER_HPP

#include <string>
#include <string_view>

namespace logging::adapter {

enum class LogLevel { kDebug = 0, kInfo = 1, kWarn = 2, kError = 3 };

bool LoggerRegisterApp(std::string_view app_id,
                       std::string_view app_description,
                       bool verify_version = false);

void LoggerUnregisterApp();

bool LoggerRegisterContext(std::string_view context_id,
                           std::string_view context_description);

void LoggerUnregisterContext(const std::string &context_id);

void LoggerLog(std::string_view context_id, LogLevel level,
               std::string &&message);

}  // namespace logging::adapter

#endif  // LOGGING_LOGGER_ADAPTER_HPP
