#include <pch>

#include "Parser/parser.hpp"


using namespace std;
namespace fs = filesystem;

using namespace chrono;

int main(int args_count, char**args_values)
{
    auto start = high_resolution_clock::now();
    // log(message("Building ...\n","BUILD START",message_type::wait));

    Parser::parse(args_count,  args_values);

    // parse_arguments(args_count, args_values);

    // vector<thread> threads;
    // auto threads_count = std::thread::hardware_concurrency();
    // threads_count = threads_count > 0 ? threads_count - 1u : 0u;

    // auto files_count = get_files_to_build().size();

    // auto &[out_build_path,out_exec_path] = get_output_path_and_name();

    // if(files_count > 1u)
    // {
    //     threads_count = (files_count-1)/threads_count > 0 ? threads_count : (files_count-1);
    //     for(auto i = 0u; i < threads_count; ++i)
    //         try{
    //             threads.emplace_back(thread(thread_build_file, &get_files_to_build(), out_build_path));
    //         }catch(const std::exception & exept) {message(string("Can't create thread ") + exept.what(), "ERROR", message_type::error);}
    // }

    // thread_build_file(&get_files_to_build(), out_build_path);

    // for(auto &thread_ : threads)
    //     try{
    //         if(thread_.joinable()) thread_.join();
    //     }catch(const std::exception &exept) {message(string("Can't join thread ") + exept.what(), "ERROR", message_type::error);}
         
    // if(!has_error_files())
    //     try{
    //         string stream_;

    //         log(message("Linking files ...\n","WAIT",message_type::wait));
    //         auto[state_,elapsed_time_] = link_all_files(out_build_path,out_exec_path,stream_);

    //         string head;
    //         if(state_==resultState::error)
    //         {
    //             has_error_files() = true;
    //             head += message("Linked in "+time_to_string(elapsed_time_),"FAIL",message_type::error);
    //         }
    //         else if(state_==resultState::warning)
    //             {
    //                 has_warning_files() = true;
    //                 head += message("Linked in "+time_to_string(elapsed_time_),"DONE",message_type::warning);
    //             }
    //             else  head += message("Linked in "+time_to_string(elapsed_time_),"DONE",message_type::done);

    //         log_head_sub(head,stream_);
            
    //     }catch(string str) {cerr << str << endl;}catch(const std::exception &ex){cerr << ex.what() << endl;}
    

    auto end = high_resolution_clock::now();
    auto time_count = (end - start).count();
    
    // log(message("Build tooks: "+time_to_string(time_count),has_error_files() ? "BUILD FAILED" : "BUILD SUCCESS",has_error_files() ? message_type::error : message_type::done));
    
    return 0;
}