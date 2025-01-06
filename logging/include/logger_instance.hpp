#ifndef LOGGING_LOGGER_INSTANCE_HPP
#define LOGGING_LOGGER_INSTANCE_HPP

#include <string_view>

namespace common::logging {

class Instance {
 public:
  Instance(std::string_view app_id, std::string_view app_description,
           bool verify_version);
  Instance(std::string_view app_id, std::string_view app_description);
  ~Instance();

  Instance(const Instance &) = delete;
  Instance &operator=(const Instance &) = delete;
  Instance(Instance &&) = delete;
  Instance &operator=(Instance &&) = delete;

  [[nodiscard]] bool IsValid() const { return is_valid_; }

 private:
  bool is_valid_;
};
}  // namespace common::logging

#endif  // LOGGING_LOGGER_INSTANCE_HPP
