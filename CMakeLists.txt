cmake_minimum_required(VERSION 3.10)
project(make10 CXX)
set(CMAKE_CXX_STANDARD 20)
add_executable(
    main 
    ./main.cpp
    ./FormulaConverter/FormulaConverter.cpp
    ./Fraction/Fraction.cpp
    ./RpnCalculator/RpnCalculator.cpp
    ./Tokenizer/Tokenizer.cpp
)