#include <pch>

#include "logger.hpp"

using namespace std;


map<message_type, string> type_style = {
      {message_type::done, foreground(232)+background(40)+set_reset(1)}
    , {message_type::warning, foreground(232)+background(220)+set_reset(1)}
    , {message_type::error, foreground(251)+background(160)+set_reset(1)}
    , {message_type::wait, foreground(252)+background(208)+set_reset(1)}

    , {message_type::other, foreground(250)+background(57)+set_reset(1)}
};


string message(const string &message_, const string &message_header_, message_type type_)
{
    return string(    type_style[type_] 
                +     ' '+message_header_+' ' 
                +     set_reset(0)+foreground(68) 
                +     " "+message_ 
                +     set_reset(0)
                );
}

resultState result_state(const std::string &str_)
{
    resultState state = str_.find("error") != string::npos ? resultState::error : resultState::none;
    state = str_.find("warning") != string::npos ? state | resultState::warning : state;

    return state == resultState::none ? resultState::done : state;
}

static mutex& shared_mutex()
{
    static mutex guard;
    return guard;
}

void log(const std::string & str_)
{
    lock_guard lock_stdout(shared_mutex());

    cout << str_ << endl;
}


void log_head_sub(const std::string & head_, const std::string & str_)
{
    lock_guard lock_stdout(shared_mutex());

    cout << head_ << endl;

    auto iter = str_.begin();
    if(iter == str_.end()) goto Exit;

    // cout << foreground(99)+set_reset(1) << " ↑  " << set_reset(0);
    cout << '\t';

    do{
        if(*iter == '\n')
        {
            if(++iter == str_.end()) break;
            // cout << foreground(99)+set_reset(1) << "\n |  " << set_reset(0);
            cout <<  "\n\t";
            continue;
        }
        cout << *iter++;
    }while(iter != str_.end()); 

 Exit:
    cout << '\n' << endl;
}
