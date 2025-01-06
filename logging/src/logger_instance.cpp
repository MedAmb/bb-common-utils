#include "logger_instance.hpp"

#include "logger_adapter.hpp"

namespace {
bool IsAppIdValid(std::string_view app_id) {
  return !app_id.empty() && (app_id.size() <= 4);
}
}  // namespace

namespace common::logging {

Instance::Instance(std::string_view app_id, std::string_view app_description)
    : Instance{app_id, app_description, false} {}

Instance::Instance(std::string_view app_id, std::string_view app_description,
                   bool verify_version) {
  if (IsAppIdValid(app_id)) {
    is_valid_ = ::logging::adapter::LoggerRegisterApp(app_id, app_description,
                                                      verify_version);
  } else {
    is_valid_ = false;
  }
}

Instance::~Instance() {
  if (is_valid_) {
    ::logging::adapter::LoggerUnregisterApp();
  }
}

}  // namespace common::logging
