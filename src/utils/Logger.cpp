#include "Logger.hpp"

LogLevel Logger::loglevel = LogLevel::LOG_INFO;

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

Logger& Logger::operator<<(const std::vector<uint32_t> value_vector)
{
    _buffer << "vector (size " << std::to_string(value_vector.size()) << "): [ ";
    for(auto value : value_vector)
    {
        _buffer << std::to_string(value);
        _buffer << " ";
    }
    _buffer << "]";
    return *this;
}

Logger& Logger::operator<<(const uint64_t value)
{
    _buffer << std::to_string(value);
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
        case LOG_DEBUG2:
            return "DEBUG2";
            break;
        case LOG_DEBUG3:
            return "DEBUG3";
            break;
        case LOG_DEBUG4:
            return "DEBUG4";
            break;
        case LOG_DEBUG5:
            return "DEBUG5";
            break;
        case LOG_DEBUG6:
            return "DEBUG6";
            break;
        case LOG_DEBUG7:
            return "DEBUG7";
            break;
        case LOG_DEBUG8:
            return "DEBUG8";
            break;
        case LOG_DEBUG9:
            return "DEBUG9";
            break;
        default:
            return "";
            break;
    }
}
