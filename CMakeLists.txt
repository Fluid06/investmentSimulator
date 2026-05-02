cmake_minimum_required(VERSION 3.10)

project(InvestmentSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(investmentSimulator
        src/main.cpp
        src/Bond.cpp
        src/Client.cpp
        src/Commodity.cpp
        src/Contract.cpp
        src/Cryptocurrency.cpp
        src/Instrument.cpp
        src/Market.cpp
        src/Portfolio.cpp
        src/Stock.cpp
        src/World.cpp
        src/Logger.cpp
        src/SaveManager.cpp
        include/SaveManager.hpp
)

target_compile_options(investmentSimulator PRIVATE -Wall -Wextra -fsanitize=address)
target_link_options(investmentSimulator PRIVATE -fsanitize=address)
target_include_directories(investmentSimulator PRIVATE include)