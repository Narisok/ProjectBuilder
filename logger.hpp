#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include "pch.hpp"


inline std::string foreground(int color_){return std::string("\033[38;5;" + std::to_string(color_) + "m");}
inline std::string background(int color_){return std::string("\033[48;5;" + std::to_string(color_) + "m");}
inline std::string set_reset(int code_){return std::string("\033[") + std::to_string(code_) + "m";}

enum class message_type
{
    done,
    error,
    warning,
    wait,

    other
};

enum class resultState
{
    none        = 0,

    done        = 1 << 0,
    warning     = 1 << 1,
    error       = 1 << 2
};
inline resultState operator &(resultState lhs, resultState rhs) noexcept
    {return static_cast<resultState>(static_cast<int>(lhs) & static_cast<int>(rhs));}
inline resultState operator |(resultState lhs, resultState rhs) noexcept
    {return static_cast<resultState>(static_cast<int>(lhs) | static_cast<int>(rhs));}
inline bool operator ==(resultState lhs, resultState rhs) noexcept
    {return static_cast<bool>(static_cast<int>(lhs) & static_cast<int>(rhs));}

void log(const std::string & str_);

void log_head_sub(const std::string & head_, const std::string & sub_);

std::string message(const std::string &message_, const std::string &message_header_, message_type type_);

resultState result_state(const std::string &str_);

#endif //_LOGGER_HPP_