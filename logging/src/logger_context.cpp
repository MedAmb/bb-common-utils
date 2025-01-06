#include "logger_context.hpp"

#include "logger_adapter.hpp"

namespace {
bool IsCtxIdValid(std::string_view app_id) {
  return !app_id.empty() && (app_id.size() <= 4);
}
}  // namespace

namespace common::logging {

Context::Context(std::string_view context_id,
                 std::string_view context_description)
    : context_id_{context_id} {
  if (IsCtxIdValid(context_id)) {
    is_valid_ = ::logging::adapter::LoggerRegisterContext(context_id,
                                                          context_description);
  } else {
    is_valid_ = false;
  }
}

Context::~Context() {
  if (is_valid_) {
    ::logging::adapter::LoggerUnregisterContext(context_id_);
  }
}

void Context::Debug_(std::string &&message) {
  ::logging::adapter::LoggerLog(
      context_id_, ::logging::adapter::LogLevel::kDebug, std::move(message));
}

void Context::Info_(std::string &&message) {
  ::logging::adapter::LoggerLog(
      context_id_, ::logging::adapter::LogLevel::kInfo, std::move(message));
}

void Context::Warn_(std::string &&message) {
  ::logging::adapter::LoggerLog(
      context_id_, ::logging::adapter::LogLevel::kWarn, std::move(message));
}

void Context::Error_(std::string &&message) {
  ::logging::adapter::LoggerLog(
      context_id_, ::logging::adapter::LogLevel::kError, std::move(message));
}

}  // namespace common::logging
