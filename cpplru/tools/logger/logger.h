#pragma once
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

enum class LogLevel
{
  INFO,
  WARNING,
  ERROR,
  DEBUG
};

class Logger
{
 public:
  static Logger& instance();

  void setLogFile(const std::string& filename);
  void log(LogLevel level, const std::string& message);

 private:
  std::ofstream fileStream;
  Logger() = default;
  ~Logger();

  std::string timestamp();
};

inline void logInfo(const std::string& msg)
{
  Logger::instance().log(LogLevel::INFO, msg);
}

inline void logWarning(const std::string& msg)
{
  Logger::instance().log(LogLevel::WARNING, msg);
}

inline void logError(const std::string& msg)
{
  Logger::instance().log(LogLevel::ERROR, msg);
}

inline void logDebug(const std::string& msg)
{
  Logger::instance().log(LogLevel::DEBUG, msg);
}
