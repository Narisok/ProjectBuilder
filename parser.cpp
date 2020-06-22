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
    ignore_paths,
    
    none
};

typedef vector<string> flag_container;

map<flags,flag_container> Flags_Values = {
      {flags::output_build_path,{}}
    , {flags::output_exec_path,{}}

    , {flags::compiler_flags,{}}
    , {flags::files_to_build,{}}
    , {flags::folders_to_build,{}}
    , {flags::libs,{}}
    , {flags::libs_path,{}}
    , {flags::include_path,{}}

    , {flags::force_rebuild,{}}
    , {flags::ignore_paths,{}}
};

map<flags, flag_container> Default_Parameters = {
      {flags::folders_to_build, {fs::path("./")}}
    , {flags::compiler_flags, { "std=c++2a"
                              , "g"
                              , "Wall"
                              , "Wextra"
                              , "Wpedantic"
                              , "Wsign-promo"
                              , "Wold-style-cast"
                              , "Woverloaded-virtual" 
                              , "Wnon-virtual-dtor" 
                              , "Wfloat-equal" 
                              , "Wshadow=compatible-local" 
                              , "Wno-dangling-else"
                              , "Wno-unused"}
                              }
    , {flags::ignore_paths, {"Build"}}
};

map<string,flags> Flag_Names = {
      {"-output_folder",    flags::output_build_path}
    , {"-out_build",        flags::output_build_path}
    , {"-out",              flags::output_build_path}
    , {"-o",                flags::output_build_path}

    //second argument in -o flag
    //-o my/build/folder my/exec/folder/file_name.out  IS SAME e -o my/build/folder -oe my/exec/folder/file_name.out
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

    , {"-ignore",           flags::ignore_paths}
    , {"-i",                flags::ignore_paths}
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

static flag_container & get_parsed_flags(flags flag_)
{
    flag_container & con = Flags_Values[flag_];

    //If the compiler flags are not specified, get the default flags
    if(con.empty()) return Default_Parameters[flag_];
    else return con;
}

const set<string>& get_compiler_flags()
{
    static set<string> compiler_flags{};
    static bool compiler_flags_parsed = false;

    if(compiler_flags_parsed) return compiler_flags;

    for(auto a : get_parsed_flags(flags::compiler_flags))
        compiler_flags.insert(move( a.insert(0,1,'-') ));
    
    compiler_flags_parsed = true;
    return compiler_flags;
}


const pair<fs::path, fs::path>& get_output_path_and_name()
{
    static pair<fs::path, fs::path> result{};
    static bool get_out_path_parsed = false;

    if(get_out_path_parsed) return result;


    auto o_count = get_parsed_flags(flags::output_build_path).size();
    auto oe_count = get_parsed_flags(flags::output_exec_path).size();

    fs::path out_build = 
            o_count > 0 
            ? fs::path(get_parsed_flags(flags::output_build_path)[0]) 
            : fs::path("Build") / (get_compiler_flags().contains("-g") ? "Debug" : "Release");

    fs::path out_exec = 
            oe_count > 0 
            ? fs::path(get_parsed_flags(flags::output_exec_path)[0]) 
            :   o_count > 1 
                ? fs::path(get_parsed_flags(flags::output_build_path)[1])
                : out_build / "exec.app";
    
    //WARNING output
    if(oe_count > 1) cout << "WARNING: Rest of arguments(1<) are ignored (-out_exec)" << endl;
    auto ignored = oe_count > 0u ? 1u : 2u;
    if(o_count > ignored) cout << "WARNING: Rest of argument(" << to_string(ignored) << "<) are ignored (-out_build)" << endl;

    result = pair(move(out_build), move(out_exec));
    get_out_path_parsed = true;
    return result;
}

const vector<fs::path>& get_files_to_build()
{
    static vector<fs::path> Files_to_Build = {};
    static bool Files_to_Build_parsed = false;

    if(Files_to_Build_parsed) return Files_to_Build;

    for(auto &file_ : Flags_Values[flags::files_to_build])
        Files_to_Build.emplace_back(file_);

    //If the folder to build and the files to build are not specified, add the default folders to build
    if(Files_to_Build.empty() && Flags_Values[flags::folders_to_build].empty())
        for(auto &folders_ : Default_Parameters[flags::folders_to_build])
            Flags_Values[flags::folders_to_build].push_back(std::move(folders_));
    

    for(auto &folder_ : Flags_Values[flags::folders_to_build])
        if(!fs::exists(folder_))
            cerr << "WARNING: folder doen't exist (-folders_to_build) >>" + folder_;
        else for(auto &entry_ : fs::recursive_directory_iterator(folder_))
             {
                auto extension_ = entry_.path().extension();
                if(extension_ == ".c" || extension_ == ".cpp")
                    Files_to_Build.emplace_back(entry_.path());
             }



    Files_to_Build_parsed = true;
    return Files_to_Build;
}

const vector<string>& get_libs()
{
    static vector<string> libs = {};
    static bool get_libs_parsed = false;

    if(get_libs_parsed) return libs;
    
    for(auto a : get_parsed_flags(flags::libs))
        libs.push_back("-l" + move(a));
    
    get_libs_parsed = true;
    return libs;
}

const vector<fs::path>& get_libs_path()
{
    static vector<fs::path> libs_path = {};
    static bool get_libs_path_parsed = false;

    if(get_libs_path_parsed) return libs_path;
    
    for(auto a : get_parsed_flags(flags::libs_path))
        libs_path.push_back("-L" + move(fs::path(a).lexically_normal().string()));
    
    get_libs_path_parsed = true;
    return libs_path;
}

const vector<fs::path>& get_include_path()
{
    static vector<fs::path> incl_path = {};
    static bool get_incl_path_parsed = false;

    if(get_incl_path_parsed) return incl_path;
    
    for(auto &a : get_parsed_flags(flags::include_path))
        incl_path.push_back("-I" + move(fs::path(a).lexically_normal().string()));
    
    get_incl_path_parsed = true;
    return incl_path;
}

bool force_rebuild()
{
    return Enabled_Flags[flags::force_rebuild];
}