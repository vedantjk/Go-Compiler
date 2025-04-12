# Minimum required CMake version
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Compiler must be at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_BUILD_TYPE Debug)

# Required if linking to the static ANTLR4 library
add_definitions(-DANTLR4CPP_STATIC)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(ANTLR4_WITH_STATIC_CRT OFF)

# Specify the version of the ANTLR4 library
set(ANTLR4_TAG 4.11.1)
set(ANTLR4_ZIP_REPOSITORY https://github.com/antlr/antlr4/archive/refs/tags/4.11.1.zip)

# Add external build for ANTLR4 C++ runtime
include(ExternalAntlr4Cpp)

# Add ANTLR4 C++ artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

# Set variable pointing to the ANTLR tool that supports C++
set(ANTLR_EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/grammars/antlr-4.11.1-complete.jar)

# Define output directory for generated lexer files
set(GENERATED_DIR "${CMAKE_SOURCE_DIR}/lexer")

# Ensure the directory exists
file(MAKE_DIRECTORY ${GENERATED_DIR})

# Add macros to generate ANTLR C++ code from grammar
find_package(ANTLR REQUIRED)
antlr_target(GoliteLexer grammars/GoliteLexer.g4 LEXER
             PACKAGE GoliteLexer
             OUTPUT_DIRECTORY ${GENERATED_DIR})

# Include necessary directories
include_directories(${GENERATED_DIR})   
include_directories(${CMAKE_SOURCE_DIR}/lexer)
include_directories(${CMAKE_SOURCE_DIR}/parser)
include_directories(${CMAKE_SOURCE_DIR}/utilities) 
include_directories(${CMAKE_SOURCE_DIR}/ast)
include_directories(${CMAKE_SOURCE_DIR}/types)
include_directories(${CMAKE_SOURCE_DIR}/symboltable)
include_directories(${CMAKE_SOURCE_DIR}/cfg)
include_directories(${CMAKE_SOURCE_DIR}/llvm)
include_directories(${CMAKE_SOURCE_DIR}/codegen)

# Collect all source files
set(SOURCES
        golite/main.cpp
    lexer/lexer.cpp
        parser/GoliteParser.cpp
    ${ANTLR_GoliteLexer_CXX_OUTPUTS}
        parser/parser.cpp
        parser/ASTBuilderVisitor.cpp
        symboltable/symboltable.h
        types/types.cpp
        ast/astNodes/ASTNode.cpp
        cfg/CFG.cpp
        cfg/CFG.h
        llvm/LLVM.h
        llvm/LLVM.cpp
        codegen/codegen.h
        codegen/codegen.cpp
)

# Add executable
add_executable(golite ${SOURCES})

# Link against ANTLR static runtime and pthreads
target_link_libraries(golite antlr4_static Threads::Threads)

# Copy the benchmarks folder to the build directory
add_custom_command(
    TARGET golite POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/benchmarks  # Source folder
        ${CMAKE_BINARY_DIR}/benchmarks  # Destination folder inside build
    COMMENT "Copying benchmarks folder to build directory..."
)
