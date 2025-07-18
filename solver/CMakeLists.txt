cmake_minimum_required(VERSION 3.31...4.0)
project(
    Pseudoku
    VERSION 0.127
    LANGUAGES CXX)
add_executable(
    pdk 
    main.cpp
    kmd.cpp
    binit.cpp
    bparse.cpp
    draw.cpp 
    eval_utils.cpp
    solver_caller.cpp
    general_utils.cxx
    sudokonst.h)

