#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <sstream>
#include <string>

enum LogLevel
{
    LOG_NOTHING,  // To disable all logs. Do not use for logging anything
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
    LOG_INIT,
    LOG_DEBUG
};

class Logger
{
    public:

    static LogLevel loglevel;

    Logger(LogLevel _loglevel);

    ~Logger();

    Logger& operator<<(const std::string& value);

    private:

    std::ostringstream _buffer;

    std::string GetLogLevelLabel(LogLevel _loglevel);
};

#define LOGGER(level) \
if (level > Logger::loglevel) ; \
else Logger(level)

#endif