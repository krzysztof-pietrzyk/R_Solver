#include "Logger.hpp"

LogLevel Logger::loglevel = LogLevel::LOG_DEBUG;

Logger::Logger(LogLevel _loglevel)
{
    _buffer << std::string(_loglevel, '-') << GetLogLevelLabel(_loglevel) << " : ";
}

Logger::~Logger()
{
    _buffer << std::endl;
    std::cerr << _buffer.str();
}

Logger& Logger::operator<<(const std::string& value)
{
    _buffer << value;
    return *this;
}

std::string Logger::GetLogLevelLabel(LogLevel _loglevel)
{
    switch(_loglevel)
    {
        case LOG_ERROR:
            return "ERROR";
            break;
        case LOG_WARNING:
            return "WARNING";
            break;
        case LOG_INFO:
            return "INFO";
            break;
        case LOG_INIT:
            return "INIT";
            break;
        case LOG_DEBUG:
            return "DEBUG";
            break;
        default:
            return "";
            break;
    }
}
