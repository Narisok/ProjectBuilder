#include "pch.hpp"
#include "fileBuilder.hpp"
#include "systemCall.hpp"

using namespace std;
namespace fs = filesystem;


atomic<bool> & has_error_files(){static atomic<bool> has_error(false); return has_error;}
atomic<bool> & has_warning_files(){static atomic<bool> has_warning(false); return has_warning;}

pair<resultState,int64_t> build_file(fs::path file_, fs::path path_, std::string & stream_)
{
    auto time_start = high_resolution_clock::now();

    for(auto &a : file_.parent_path())
        path_ /= a;
    
    path_ /= file_.stem().string() + ".o";

    if(fs::exists(path_))
    {
        if(!force_rebuild() && fs::last_write_time(path_) > fs::last_write_time(file_))
            goto EXIT;
    }
    else 
    {
        fs::create_directories(path_.parent_path());
    }

    system_call(sysCallType::compiling, path_, {file_}, stream_ );


 EXIT:
    auto time_end = high_resolution_clock::now();
    auto elapsed_time = (time_end - time_start).count();
    auto state = result_state(stream_);
    return pair(state,elapsed_time);
}


void thread_build_file(const vector<fs::path> * files_pool, fs::path build_path)
{
    static atomic<size_t> cur_idx(0u);
    thread_local string my_stream;

    for(size_t my_idx = cur_idx++; my_idx < files_pool->size(); my_idx = cur_idx++)
    {
        auto file_ = files_pool->at(my_idx);
        string mess = " file \"" + set_reset(1) + set_reset(4) + foreground(61)  + file_.string() + set_reset(24) + set_reset(22) + '"';

        log(message("Compiling"+mess+" ...\n","WAIT",message_type::wait));
        auto[state,elapsed_time] = build_file(file_,build_path, my_stream);

        string head;
        if(state==resultState::error)
        {
            has_error_files() = true;
            head += message("Compiled"+mess+" in "+time_to_string(elapsed_time),"FAIL",message_type::error);
        }
        else if(state==resultState::warning)
            {
                has_warning_files() = true;
                head += message("Compiled"+mess+" in "+time_to_string(elapsed_time),"DONE",message_type::warning);
            }
            else  head += message("Compiled"+mess+" in "+time_to_string(elapsed_time),"DONE",message_type::done);

        log_head_sub(head,my_stream);
    }
}

pair<resultState,int64_t> link_all_files(fs::path build_path_, fs::path out_file_path_, std::string & stream_)
{
    auto time_start = high_resolution_clock::now();

    vector<fs::path> files_to_link;
    for(auto &p : fs::recursive_directory_iterator(build_path_))
        if(p.path().extension() == ".o")
           files_to_link.push_back( p.path());

    if(!out_file_path_.parent_path().empty())
        fs::create_directories(out_file_path_.parent_path());

    system_call(sysCallType::linking, out_file_path_.string(), files_to_link, stream_);

    auto time_end = high_resolution_clock::now();
    auto elapsed_time = (time_end - time_start).count();
    auto state = result_state(stream_);
    return pair(state,elapsed_time);
}