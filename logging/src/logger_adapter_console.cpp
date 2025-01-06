#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <iostream>
#include <memory>
#include <string>

#include "logger_adapter.hpp"

namespace logging::adapter {

namespace {
std::shared_ptr<spdlog::logger> Logger;
}  // namespace

bool LoggerRegisterApp(std::string_view app_id,
                       [[maybe_unused]] std::string_view app_description,
                       [[maybe_unused]] bool verify_version) {
  Logger = spdlog::stdout_color_mt<spdlog::async_factory>(app_id.data());
  Logger->set_level(spdlog::level::trace);
  Logger->set_pattern(
      "[%Y-%m-%d %H:%M:%S.%e] [TID:%P] [%^%-8l%$] [APPID:%n] %v");
  return true;
}

void LoggerUnregisterApp() {}

bool LoggerRegisterContext(std::string_view context_id,
                           std::string_view context_description) {
  (void)context_id;
  (void)context_description;
  return true;
}

void LoggerUnregisterContext(const std::string &context_id) {
  (void)context_id;
}

void LoggerLog(std::string_view context_id, LogLevel level,
               std::string &&message) {
  if (!Logger) {
    Logger = spdlog::stdout_color_mt<spdlog::async_factory>("UNKW");
    Logger->set_level(spdlog::level::trace);
    Logger->set_pattern(
        "[%Y-%m-%d %H:%M:%S.%e] [TID:%P] [%^%l%$] [APPID:%n] %v]");
  }
  switch (level) {
    case LogLevel::kDebug:
      Logger->debug("[CTXID:{}] [{}]", context_id, message);
      break;
    case LogLevel::kInfo:
      Logger->info("[CTXID:{}] [{}]", context_id, message);
      break;
    case LogLevel::kWarn:
      Logger->warn("[CTXID:{}] [{}]", context_id, message);
      break;
    case LogLevel::kError:
      Logger->error("[CTXID:{}] [{}]", context_id, message);
      break;
    default:
      break;
  }
}

}  // namespace logging::adapter
