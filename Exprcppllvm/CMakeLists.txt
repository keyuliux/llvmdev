cmake_minimum_required(VERSION 3.5)
project(Expr)

find_package(LLVM REQUIRED CONFIG)
set(CMAKE_CXX_STANDARD 14)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.
SET(CMAKE_CXX_FLAGS "-std=c++0x")

include_directories(
        ${PROJECT_SOURCE_DIR}/generated/
        ${PROJECT_SOURCE_DIR}/third_party/
        ${PROJECT_SOURCE_DIR}/third_party/antlr4-cpp-runtime-4.7.2/src
        ${PROJECT_SOURCE_DIR}/src/
        ${LLVM_INCLUDE_DIRS}/
)
set(src_dir
        ${PROJECT_SOURCE_DIR}/generated/LabeledExprLexer.cpp
        ${PROJECT_SOURCE_DIR}/generated/LabeledExprParser.cpp
        ${PROJECT_SOURCE_DIR}/generated/LabeledExprVisitor.cpp
        ${PROJECT_SOURCE_DIR}/generated/LabeledExprBaseVisitor.cpp
        ${PROJECT_SOURCE_DIR}/src/EvalVisitor.cpp

 )
file(GLOB antlr4-cpp-src
    ${PROJECT_SOURCE_DIR}/third_party/antlr4-cpp-runtime-4.7.2/src/*.cpp
    ${PROJECT_SOURCE_DIR}/third_party/antlr4-cpp-runtime-4.7.2/src/atn/*.cpp
    ${PROJECT_SOURCE_DIR}/third_party/antlr4-cpp-runtime-4.7.2/src/dfa/*.cpp
    ${PROJECT_SOURCE_DIR}/third_party/antlr4-cpp-runtime-4.7.2/src/misc/*.cpp
    ${PROJECT_SOURCE_DIR}/third_party/antlr4-cpp-runtime-4.7.2/src/support/*.cpp
    ${PROJECT_SOURCE_DIR}/third_party/antlr4-cpp-runtime-4.7.2/src/tree/*.cpp
    ${PROJECT_SOURCE_DIR}/third_party/antlr4-cpp-runtime-4.7.2/src/tree/pattern/*.cpp
    ${PROJECT_SOURCE_DIR}/third_party/antlr4-cpp-runtime-4.7.2/src/tree/xpath/*.cpp
)
add_definitions(${LLVM_DEFINITIONS})
add_library (antlr4-cpp-runtime ${antlr4-cpp-src})
add_executable(Expr ${src_dir} src/main.cpp)
# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader )

target_link_libraries(Expr antlr4-cpp-runtime ${llvm_libs})