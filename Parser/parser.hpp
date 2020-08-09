#pragma once

#include <pch>
#include "flag.hpp"

class Parser
{
    Parser() = delete;
    Parser(const Parser&) = delete;
    Parser(Parser&&) = delete;
    Parser& operator=(const Parser&) = delete;
    Parser& operator=(Parser&&) = delete;

public:
    static void parse(int argc, char** argv) noexcept;

private:
    static map<string,string> get_aliases() noexcept;

public:
    static map<string,string> flags;

private:
    static vector<flag> supported_flags;
};