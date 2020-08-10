#pragma once

// #include <PBheader>

struct flag
{
    string                            name;
    vector<string>                    aliases;
    vector<string>                    default_values{};
    unsigned                          max_count{1};
    function<string(vector<string>&)> get_flags = [](vector<string>& args)->string 
                                                {
                                                    string result;
                                                    for(auto a : args)
                                                        result += '-' + a + ' ';
                                                    return result;
                                                };
};