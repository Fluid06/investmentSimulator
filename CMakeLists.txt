cmake_minimum_required(VERSION 3.10)

project(InvestmentSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(investmentSimulator
    src/main.cpp
)

target_compile_options(investmentSimulator PRIVATE -Wall -Wextra -fsanitize=address)
target_link_options(investmentSimulator PRIVATE -fsanitize=address)
target_include_directories(investmentSimulator PRIVATE include)