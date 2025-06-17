cmake_minimum_required(VERSION 3.31...4.0)
project(
    Pseudoku
    VERSION 0.126
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
    sudokonst.h)

