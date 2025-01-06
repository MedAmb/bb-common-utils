#ifndef LOGGING_LOGGER_CONTEXT_HPP
#define LOGGING_LOGGER_CONTEXT_HPP

#include <fmt/format.h>

#include <string>
#include <string_view>

namespace common::logging {

class Context {
 public:
  Context(std::string_view context_id, std::string_view context_description);
  ~Context();

  Context(const Context &) = delete;
  Context &operator=(const Context &) = delete;
  Context(Context &&) = delete;
  Context &operator=(Context &&) = delete;

  [[nodiscard]] bool IsValid() const { return is_valid_; }

  template <typename... Args>
  void Debug(std::string_view message, Args &&...args) {
    if (is_valid_) {
      Debug_(fmt::format(message, std::forward<Args>(args)...));
    }
  }

  template <typename... Args>
  void Info(std::string_view message, Args &&...args) {
    if (is_valid_) {
      Info_(fmt::format(message, std::forward<Args>(args)...));
    }
  }

  template <typename... Args>
  void Warn(std::string_view message, Args &&...args) {
    if (is_valid_) {
      Warn_(fmt::format(message, std::forward<Args>(args)...));
    }
  }

  template <typename... Args>
  void Error(std::string_view message, Args &&...args) {
    if (is_valid_) {
      Error_(fmt::format(message, std::forward<Args>(args)...));
    }
  }

 private:
  const std::string context_id_;
  bool is_valid_;

  void Debug_(std::string &&message);
  void Info_(std::string &&message);
  void Warn_(std::string &&message);
  void Error_(std::string &&message);
};
}  // namespace common::logging

#endif  // LOGGING_LOGGER_CONTEXT_HPP
