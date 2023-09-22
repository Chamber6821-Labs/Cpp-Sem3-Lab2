#pragma once

#include <chrono>
#include <string>

class BadTask {
public:
  using time_point =
    std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>;

  BadTask(const time_point &creationTime, std::string prompt);

  [[nodiscard]] time_point creationTime() const;

  void creationTime(const time_point &time);

  [[nodiscard]] std::string prompt() const;

  void prompt(std::string text);

  auto operator<=>(const time_point &other) const {
    return _creationTime <=> other;
  }

  auto operator<=>(const BadTask &other) const = default;

private:
  time_point _creationTime;
  std::string _prompt;
};
