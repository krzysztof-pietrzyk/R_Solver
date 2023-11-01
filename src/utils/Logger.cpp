// implemented header
#include "Logger.hpp"

// project includes

// std includes
#include <ctime>
#include <iomanip>
#include <iostream>


LogLevel Logger::loglevel = LogLevel::INFO;

Logger::Logger(LogLevel _loglevel)
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    _buffer << std::string(int(_loglevel), '-') << GetLogLevelLabel(_loglevel) 
        << " " << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << " : ";
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
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::INIT:
            return "INIT";
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::DEBUG1:
            return "DEBUG1";
        case LogLevel::DEBUG2:
            return "DEBUG2";
        case LogLevel::DEBUG3:
            return "DEBUG3";
        case LogLevel::DEBUG4:
            return "DEBUG4";
        case LogLevel::DEBUG5:
            return "DEBUG5";
        case LogLevel::DEBUG6:
            return "DEBUG6";
        case LogLevel::DEBUG7:
            return "DEBUG7";
        case LogLevel::DEBUG8:
            return "DEBUG8";
        case LogLevel::DEBUG9:
            return "DEBUG9";
        default:
            return "";
    }
}
