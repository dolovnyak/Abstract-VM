cmake_minimum_required(VERSION 3.17)
project(abstract_vm)

set(CMAKE_CXX_STANDARD 11)

include_directories(srcs)

set(PROJECT_SOURCES
        srcs/AbstractVmStack.cpp
        srcs/OperandFactory.cpp
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
        )
