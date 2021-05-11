cmake_minimum_required(VERSION 3.15)
project(abstract_vm)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        srcs
        srcs/Parse
        srcs/Operand
)

set(PROJECT_SOURCES
        srcs/AbstractVmStack.cpp
        srcs/Operand/OperandFactory.cpp
        srcs/Operand/OperandExceptions.cpp
        srcs/Parse/Lexer.cpp
        srcs/Parse/Parser.cpp
        srcs/utilities.cpp
        srcs/CommandList.cpp
        )

add_executable(abstract_vm
        srcs/main.cpp
        ${PROJECT_SOURCES}
        )

add_executable(abstract_vm_tests
        ${PROJECT_SOURCES}
        tests/main.cpp
        tests/Operand_Factory_Tests.cpp
        tests/Operand_Calculation_Tests.cpp
        tests/Abstract_Vm_Stack_Tests.cpp
        tests/Command_List_Tests.cpp
        )

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )
