#include "parser.hpp"


using namespace std;
namespace fs = filesystem;

enum class flags
{
    output_build_path,
    output_exec_path,

    compiler_flags,
    files_to_build,
    folders_to_build,
    libs,
    libs_path,
    include_path,

    force_rebuild,
    
    none
};

map<flags,vector<string>> Flags_Values = {
      {flags::output_build_path,{}}
    , {flags::output_exec_path,{}}

    , {flags::compiler_flags,{}}
    , {flags::files_to_build,{}}
    , {flags::folders_to_build,{}}
    , {flags::libs,{}}
    , {flags::libs_path,{}}
    , {flags::include_path,{}}

    , {flags::force_rebuild,{}}
};

map<string,flags> Flag_Names = {
      {"-output_folder",    flags::output_build_path}
    , {"-out_build",        flags::output_build_path}
    , {"-out",              flags::output_build_path}
    , {"-o",                flags::output_build_path}

    , {"-out_exec",         flags::output_exec_path}
    , {"-oe",               flags::output_exec_path}

    , {"-flags",            flags::compiler_flags}

    , {"-files",            flags::files_to_build }

    , {"-folders",          flags::folders_to_build}

    , {"-libs",             flags::libs}
    , {"-l",                flags::libs}

    , {"-libs_path",        flags::libs_path}
    , {"-L",                flags::libs_path}

    , {"-include_path",     flags::include_path}
    , {"-I",                flags::include_path}

    , {"-force_rebuild",    flags::force_rebuild}
    , {"-f",                flags::force_rebuild}
};

map<flags,bool> Enabled_Flags = {
      {flags::force_rebuild, false}
};


void parse_arguments(int argc, char ** argv)
{
    flags selected_flag{flags::none};
    for(int i = 1; i < argc; ++i)
    {
        string cur_arg = argv[i];
        if(*cur_arg.begin() == '-')
        {
            if(Flag_Names.contains(cur_arg)) selected_flag = Flag_Names[cur_arg];
            else {selected_flag = flags::none; cerr << "Bad flag \">" << cur_arg << "<\"" << endl;}
            if(Enabled_Flags.contains(selected_flag)) Enabled_Flags[selected_flag] = true;
        }
        else
        {
            if(selected_flag != flags::none) Flags_Values[selected_flag].push_back(cur_arg);
            else cerr << "Bad option \">" << cur_arg << "<\"" << endl;
        }
    }
}

const set<string>& get_compiler_flags()
{
    static set<string> compiler_flags{};
    static bool compiler_flags_parsed = false;

    if(compiler_flags_parsed) return compiler_flags;


    for(auto &a : Flags_Values[flags::compiler_flags])
        compiler_flags.insert(std::move( a.insert(0,1,'-') ));

    compiler_flags_parsed = true;
    return compiler_flags;
}


static pair<fs::path, fs::path> parse_output_flags()
{
    pair<fs::path, fs::path> result{};

    int size = Flags_Values[flags::output_build_path].size();
    if( size > 1)
    {
        //YELLOW
        cout << "WARNING: rest of arguments are ignored (-out_build)" << endl;
    }
    else
    {
        if(size == 1)
            result.first = *Flags_Values[flags::output_build_path].begin();
    }

    size = Flags_Values[flags::output_exec_path].size();
    if( size > 1)
    {
        //YELLOW
        cout << "WARNING: rest of arguments are ignored (-out_exec)" << endl;
    }
    else
    {
        if(size == 1)
            result.second = *Flags_Values[flags::output_exec_path].begin();
    }

    return result;
}

const pair<fs::path, fs::path>& get_output_path_and_name()
{
    static pair<fs::path, fs::path> result{};
    static bool get_out_path_parsed = false;

    if(get_out_path_parsed) return result;

    result = parse_output_flags();

    string out_file_name;
    if(result.second.empty())
        out_file_name = result.first.filename();

    result.first.remove_filename() /= "Build";
    bool isDebug = get_compiler_flags().contains("-g");
    result.first /= isDebug ? "Debug" : "Release";

    if(result.second.empty())
        result.second = result.first / (out_file_name.empty() ? string("exec.app") : out_file_name);

    get_out_path_parsed = true;
    return result;
}

const vector<fs::path>& get_files_to_build()
{
    static vector<fs::path> Files_to_Build = {};
    static bool Files_to_Build_parsed = false;

    if(Files_to_Build_parsed) return Files_to_Build;

    for(auto &file_ : Flags_Values[flags::files_to_build])
    {
        Files_to_Build.emplace_back(file_);
    }

    for(auto &folder_ : Flags_Values[flags::folders_to_build])
    {
        if(!fs::exists(folder_)) throw string("Error: folder doen't exist >>") + folder_;

        for(auto &entry_ : fs::recursive_directory_iterator(folder_))
        {
            // if(entry_.is_regular_file())
            // {
            auto extension_ = entry_.path().extension();
            if(extension_ == ".c" || extension_ == ".cpp")
                Files_to_Build.emplace_back(entry_.path());
            // }
        }
    }

    Files_to_Build_parsed = true;
    return Files_to_Build;
}

const vector<string>& get_libs()
{
    static vector<string> libs = {};
    static bool get_libs_parsed = false;

    if(get_libs_parsed) return libs;
    
    for(auto &a : Flags_Values[flags::libs])
        libs.push_back("-l" + move(a));
    
    get_libs_parsed = true;
    return libs;
}

bool force_rebuild()
{
    return Enabled_Flags[flags::force_rebuild];
}