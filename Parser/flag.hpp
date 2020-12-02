#pragma once

#include <PBheader>

namespace parser
{

    enum class additionBehavior
    {
        replace = '=',
        insert = '+',
        remove = '-',
        always_replace = 'r',
        use_default = 'd'
    };

    namespace flag
    {
        template<class T>
        concept Flag = 
            requires(T t) {
                { t.getArgumentsMaxCount() } -> unsigned;

                { *t.getAliases().begin() } -> string;
                { *t.getAliases().end() } -> string;

                { *t.getArgumentsDefault().begin() } -> string;
                { *t.getArgumentsDefault().end() } -> string;
            }
             &&
            requires(typename decay_t<T>::return_type return_type) {
                { return_type } -> auto;
            };

        template<class T>
        concept HasAliases = 
            requires(T t) {
                { *t.aliases.begin() } -> string;
                { *t.aliases.end() } -> string;
                ++t.aliases.begin();
                t.aliases.begin() != t.aliases.end();
            };

        template<class T>
        concept HasArgumentsDefault = 
            requires(T t) {
                { *t.argumentsDefault.begin() } -> string;
                { *t.argumentsDefault.end() } -> string;
                ++t.argumentsDefault.begin();
                t.argumentsDefault.begin() != t.argumentsDefault.end();
            };


        template<class T_ReturnType, 
                template<typename> class T_Container = vector>
        class FlagAbstract
        {
        public:
         using container_type  = T_Container<string>;
         using return_type     = T_ReturnType;
         


        //constructors
        public:
            inline FlagAbstract() 
                : aliases{}
                , arguments_default{}
                , arguments_max_count{0}
            {}

            virtual inline ~FlagAbstract() {}

            inline FlagAbstract(const FlagAbstract& other)
                : aliases(other.aliases)
                , arguments_default(other.arguments_default)
                , arguments_max_count(other.arguments_max_count)
            {}

            inline FlagAbstract(FlagAbstract && other)
                : aliases(move(other.aliases))
                , arguments_default(move(other.arguments_default))
                , arguments_max_count(move(other.arguments_max_count))
            {}

        //operators overload
        public:
            inline FlagAbstract& operator=(const FlagAbstract& other) {
                aliases = other.aliases;
                arguments_default = other.arguments_default;
                arguments_max_count = other.arguments_max_count;
                return *this;
            }

            inline FlagAbstract& operator=(FlagAbstract && other) {
                aliases = move(other.aliases);
                arguments_default = move(other.arguments_default);
                arguments_max_count = move(other.arguments_max_count);
                return *this;
            }

            template<class T>
            inline FlagAbstract& operator+=(T modificator) {
                addModificator(forward<T>(modificator));
                return *this;
            }

        //public methods
        public:
            template<class T>
            inline void addModificator(T t) 
            {
                if constexpr( HasAliases<T> ) {
                    for(auto a : t.aliases)
                        aliases.insert(aliases.end(), move(a));
                }
                if constexpr( HasArgumentsDefault<T> ) {
                    for(auto a : t.aliases)
                        aliases.insert(aliases.end(), move(a));
                }
            }

        //virtual methods
        public:
            virtual inline container_type& getAliases() {
                return aliases;
            }

            virtual inline container_type& getArgumentsDefault() {
                return arguments_default;
            }

            virtual inline unsigned getArgumentsMaxCount() {
                return arguments_max_count;
            }

        //protected fields
        protected:
            container_type aliases;
            container_type arguments_default;
            unsigned arguments_max_count;
        };
    }

    // struct Flag
    // {
    //  using proccessType = function<any(string)>;

    //     string              name;
    //     vector<string>      aliases;
    //     vector<string>      default_values{};
    //     unsigned            max_count{0};
    //     additionBehavior    default_behavior{'='};
    //     proccessType        process = [](string arg)->any {
    //                             return make_any<string>(move(arg));
    //                         };
    // };

    // template<class T>
    // concept IsFlag =
    //     requires(T t) {
    //         { t.getMaxCount() } -> unsigned;
    //         { t.getAdditionBehavior() } -> additionBehavior;
    //         { t.getAliases() } -> vector<string>;
    //         { t.proccessFlag() } -> T::return_type;
    //     };

    // template<class T>
    // concept Flag = 
    //     T::Max_Size > 0UL
    //      &&
    //     T::Addition_Behavior != additionBehavior::use_default
    //      &&
    //     requires(typename T::return_type return_type) {
    //         { return_type } -> auto;
    //     }
    //      &&
    //     requires {
    //         { T::Aliases } -> constexpr array<string>;
    //         { T::DefaultFlags } -> constexpr array<string>;
    //         { T::ProccessFlag(string) } -> typename T::return_type;
    //     };

    
}