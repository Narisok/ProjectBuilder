#!/bin/bash
echo -e "\e[1;35m>>=================================>BUILD START<=================================<<
⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋\e[0m\n"
ts=$(date +%s%N)

pre_build_tasks=(
    #insert prebuild tast below ⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋
    
    #insert prebuild tast above ⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊
)

#=======================FLAGS====================
flags=(
    #insert flags below ⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋
    
    #insert flags above ⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊
)
if [ ${#flags[@]} != 0 ]; then
echo -e "\e[1;34mActive flags:\e[0m" "\e[4;34m"${flags[@]} "\e[0m\n"
fi

#======================INCLUDE PATH====================
include_path=(
    #insert inculde path below ⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋
    
    #insert inculde path above ⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊
)
if [ ${#include_path[@]} != 0 ]; then
echo -e "\e[1;34mInclude path:\e[0m" "\e[4;34m"${include_path[@]} "\e[0m\n"
tmp=0
for i in "${include_path[@]}"; do  include_path[$tmp]=-I$i; tmp=$(($tmp+1)); done
fi

#===========================LIBRARY PATH=======================
lib_path=(
    #insert lib path below ⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋

    #insert lib path above ⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊
)
if [ ${#lib_path[@]} != 0 ]; then
echo -e "\e[1;34mLibrary path:\e[0m" "\e[4;34m"${lib_path[@]} "\e[0m\n"
tmp=0
for i in "${lib_path[@]}"; do  lib_path[$tmp]=-L$i; tmp=$(($tmp+1)); done
fi

#===========================LIBRARY===========================
libs=(
    #insert libs below ⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋
    pthread
    #insert libs above ⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊
)
if [ ${#libs[@]} != 0 ]; then
echo -e "\e[1;34mUsed libs:\e[0m" "\e[4;34m"${libs[@]} "\e[0m\n"
tmp=0
for i in "${libs[@]}"; do  libs[$tmp]=-l$i; tmp=$(($tmp+1)); done
fi

#==============================FILES TO BUILD=============
build_files=(
    #insert build files below ⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋⤋
    ./*.cpp
    #insert build files above ⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊⤊
)

#========================OUTPUT PATH=============
output_path='./builder.app'

#=========================C++ STANDART=================
cpp_standart=c++2a
#c++2a
#c++17
#c++14
#c++11

${pre_build_tasks[@]}
g++ -std=$cpp_standart  ${flags[@]} ${lib_path[@]} ${include_path[@]}  ${build_files[@]} ${libs[@]} -o ${output_path}
echo -e "\e[4;32m\nElapsed time in seconds:\e[0m\e[1;31m $((($(date +%s%N) - $ts)/1000000000)),$(((($(date +%s%N) - $ts)/1000000)%1000))\e[0m"

