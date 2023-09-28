#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <ctime>
#include <iomanip>

enum class LogLevel
{
    NOTHING,  // To disable all logs. Do not use for logging anything
    ERROR,
    WARNING,
    INFO,
    INIT,
    DEBUG,
    DEBUG1,
    DEBUG2,
    DEBUG3,
    DEBUG4,
    DEBUG5,
    DEBUG6,
    DEBUG7,
    DEBUG8,
    DEBUG9
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

#define LOGGER_ASSERT(condition, fail_desc) \
if(condition) {} \
else { LOGGER(LogLevel::ERROR) << fail_desc; throw std::runtime_error(fail_desc); }

#define LOGGER_ASSERT_NO_THROW(condition, fail_desc) \
if(condition) {} \
else { LOGGER(LogLevel::ERROR) << fail_desc; }

#define LOGGER_ASSERT_TRY(expression, exception_type, fail_desc) \
try { expression; } \
catch(exception_type) \
{ LOGGER(LogLevel::ERROR) << fail_desc; throw std::runtime_error(fail_desc); }

#define LOGGER_THROW(fail_desc) \
{ LOGGER(LogLevel::ERROR) << fail_desc; throw std::runtime_error(fail_desc); }

#endif