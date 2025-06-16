cmake_minimum_required(VERSION 3.31...4.0)
project(
    Pseudoku
    VERSION 0.124
    LANGUAGES CXX)
add_executable(pdk main.cpp kmd.cpp binit.cpp bparse.cpp draw.cpp sudokonst.h transformers.cpp)
