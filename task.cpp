#include "task.h"

BadTask::BadTask(const BadTask::time_point &creationTime, std::string prompt)
    : _creationTime(creationTime), _prompt(std::move(prompt)) {}

BadTask::time_point BadTask::creationTime() const { return _creationTime; }

void BadTask::creationTime(const BadTask::time_point &time) {
  _creationTime = time;
}

std::string BadTask::prompt() const { return _prompt; }

void BadTask::prompt(std::string text) { _prompt = std::move(text); }
