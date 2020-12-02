#include <PBheader>

#include "parser.hpp"

namespace parser
{

    Parser::Parser(const vector<string>& args)
        // : files{false, {} }
        // , build_path{false, {} }
        // , output_path{false, {} }
        // , compiler_flags{false, {} }
        // , linker_flags{false, {} }
        // , raw_arguments{}
    {
        // additionBehavior behavior = additionBehavior::use_default;
        // string selectedFlag{};
        // for(auto &arg : args) {
        //     if(arg[0] == '-') {
        //         size_t substrTo = arg.size();
        //         if(arg.back() == '-' || arg.back() == '+' || arg.back() == '=') {
        //             behavior = additionBehavior(arg.back());
        //             substrTo -= 2;
        //         } else {
        //             behavior = additionBehavior::use_default;
        //             substrTo -= 1;
        //         }
        //         selectedFlag = arg.substr(1, substrTo);
        //         raw_arguments[selectedFlag].first = behavior;
        //     } else {
        //         raw_arguments[selectedFlag].second.push_back(arg);
        //     }
        // }

        // decltype(raw_arguments) unused_arguments;
        // for(auto & a : raw_arguments) {
        //     if(!Global::Parser::AliasHasName(a.first)) {
        //         unused_arguments[a.first];
        //     }
        // }
        // for(auto & [key, value] : unused_arguments) {
        //     value = raw_arguments.extract(key).mapped();
        // }
        // if(unused_arguments.size() > 0) {
        //     //unused arguments
        // }
    }

    // const vector<string>& Parser::getCompilerFlags() noexcept
    // {
    //     if(!compiler_flags.first) {
    //         auto flag = Global::Parser::FlagFromName("complier flags");
    //         for(auto &alias : flag.aliases) {
    //             auto iter = raw_arguments.find(alias);
    //             if (iter != raw_arguments.end()) {
    //                 auto node = raw_arguments.extract(iter);
    //                 if (node.mapped().first == parser::additionBehavior::use_default) {
    //                     node.mapped().first = flag.default_behavior;
    //                 }
    //                 switch (node.mapped().first)
    //                 {
    //                 case parser::additionBehavior::replace:
    //                     compiler_flags.second.clear();
                        
    //                     break;

    //                 case parser::additionBehavior::insert:
    //                     break;

    //                 case parser::additionBehavior::remove:
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    //     return compiler_flags.second;
    // }

}