#include "logger.h"

// Singleton instance
Logger& Logger::instance()
{
  static Logger logger;
  return logger;
}

void Logger::setLogFile(const std::string& filename)
{
  fileStream.open(filename, std::ios::app);
  if (!fileStream.is_open()) {
    std::cerr << "Failed to open log file: " << filename << std::endl;
  }
}

void Logger::log(LogLevel level, const std::string& message)
{
  std::string levelStr;
  switch (level) {
    case LogLevel::INFO:
      levelStr = "INFO";
      break;
    case LogLevel::WARNING:
      levelStr = "WARNING";
      break;
    case LogLevel::ERROR:
      levelStr = "ERROR";
      break;
    case LogLevel::DEBUG:
      levelStr = "DEBUG";
      break;
  }

  std::string output = timestamp() + " [" + levelStr + "] " + message + "\n";

  // Print to console
  std::cout << output;

  // Save to file if open
  if (fileStream.is_open()) {
    fileStream << output;
  }
}

Logger::~Logger()
{
  if (fileStream.is_open()) {
    fileStream.close();
  }
}

std::string Logger::timestamp()
{
  std::time_t now = std::time(nullptr);
  char buf[20];
  std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
  return buf;
}
