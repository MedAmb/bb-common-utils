#include <dlt/dlt.h>

#include <map>

#include "logger_adapter.hpp"

namespace {
constexpr std::string_view kDltVersionMajor = "2";
constexpr std::string_view kDltVersionMinor = "18";
constexpr std::size_t kMaxAllowedContexts = 256;
}  // namespace

namespace logging::adapter {

namespace {
struct LoggingHandle {
  std::map<std::string, DltContext> contexts;
};

LoggingHandle logging_handle;
}  // namespace

bool LoggerRegisterApp(std::string_view app_id,
                       std::string_view app_description, bool verify_version) {
  if (verify_version &&
      DLT_RETURN_OK != dlt_check_library_version(kDltVersionMajor.data(),
                                                 kDltVersionMinor.data())) {
    return false;
  }

  return DLT_RETURN_OK ==
         dlt_register_app(app_id.data(), app_description.data());
}

void LoggerUnregisterApp() { (void)dlt_unregister_app(); }

bool LoggerRegisterContext(std::string_view context_id,
                           std::string_view context_description) {
  if ((logging_handle.contexts.find(context_id.data()) !=
       logging_handle.contexts.end()) &&
      (logging_handle.contexts.size() >= kMaxAllowedContexts)) {
    return false;
  }

  DltContext dlt_context;
  if (DLT_RETURN_OK != dlt_register_context(&dlt_context, context_id.data(),
                                            context_description.data())) {
    return false;
  }

  logging_handle.contexts[context_id.data()] = dlt_context;
  return true;
}

void LoggerUnregisterContext(const std::string &context_id) {
  if (logging_handle.contexts.find(context_id) ==
      logging_handle.contexts.end()) {
    return;
  }

  (void)dlt_unregister_context(&logging_handle.contexts[context_id.data()]);
  logging_handle.contexts.erase(context_id);
}

void LoggerLog(std::string_view context_id, LogLevel level,
               std::string &&message) {
  if (logging_handle.contexts.find(context_id.data()) ==
      logging_handle.contexts.end()) {
    return;
  }

  DltLogLevelType dlt_level{DLT_LOG_DEFAULT};
  switch (level) {
    case LogLevel::kDebug:
      dlt_level = DLT_LOG_DEBUG;
      break;
    case LogLevel::kInfo:
      dlt_level = DLT_LOG_INFO;
      break;
    case LogLevel::kWarn:
      dlt_level = DLT_LOG_WARN;
      break;
    case LogLevel::kError:
      dlt_level = DLT_LOG_ERROR;
      break;
    default:
      dlt_level = DLT_LOG_DEFAULT;
      break;
  }

  DLT_LOG(logging_handle.contexts[context_id.data()], dlt_level,
          DLT_CSTRING(message.data()));
}

}  // namespace logging::adapter
