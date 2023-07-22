#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>

enum LogLevel
{
    LOG_NOTHING,  // To disable all logs. Do not use for logging anything
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
    LOG_INIT,
    LOG_DEBUG,
    LOG_DEBUG2,
    LOG_DEBUG3,
    LOG_DEBUG4,
    LOG_DEBUG5,
    LOG_DEBUG6,
    LOG_DEBUG7,
    LOG_DEBUG8,
    LOG_DEBUG9
};

class Logger
{
    public:

    static LogLevel loglevel;

    Logger(LogLevel _loglevel);

    ~Logger();

    Logger& operator<<(const std::string& value);
    Logger& operator<<(const std::vector<uint32_t> value_vector);
    Logger& operator<<(const uint64_t value);

    private:

    std::ostringstream _buffer;

    std::string GetLogLevelLabel(LogLevel _loglevel);
};

#define LOGGER(level) \
if (level > Logger::loglevel) ; \
else Logger(level)

#endif