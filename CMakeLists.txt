cmake_minimum_required(VERSION 3.15)
project(abstract_vm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_STANDARD 11)

################################################################################
# abstract_vm_lib target
################################################################################
set(ABSTRACT_VM_LIB "${PROJECT_NAME}_lib")
add_library(${ABSTRACT_VM_LIB}
        srcs/AbstractVmLib/AbstractVmStack.cpp
        srcs/AbstractVmLib/Operand/OperandFactory.cpp
        srcs/AbstractVmLib/Operand/OperandExceptions.cpp
        srcs/AbstractVmLib/Parse/Lexer.cpp
        srcs/AbstractVmLib/Parse/Parser.cpp
        srcs/AbstractVmLib/utilities.cpp
        srcs/AbstractVmLib/CommandList.cpp
        )
target_include_directories(${ABSTRACT_VM_LIB} PUBLIC
        srcs/AbstractVmLib
        srcs/AbstractVmLib/Operand
        srcs/AbstractVmLib/Parse)

################################################################################
# project target
################################################################################
add_executable(${PROJECT_NAME}
        srcs/main.cpp
        )
target_link_libraries(${PROJECT_NAME} ${ABSTRACT_VM_LIB})
target_include_directories(${PROJECT_NAME} PUBLIC
        srcs/AbstractVmLib
        srcs/AbstractVmLib/Operand
        srcs/AbstractVmLib/Parse)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )

################################################################################
# tests
################################################################################
set(ABSTRACT_VM_TESTS ${PROJECT_NAME}_tests)
add_executable(${ABSTRACT_VM_TESTS}
        tests/main.cpp
        tests/Operand_Factory_Tests.cpp
        tests/Operand_Calculation_Tests.cpp
        tests/Abstract_Vm_Stack_Tests.cpp
        tests/Command_List_Tests.cpp
        )
target_link_libraries(${ABSTRACT_VM_TESTS} ${ABSTRACT_VM_LIB})
target_include_directories(${ABSTRACT_VM_TESTS} PUBLIC
        srcs/AbstractVmLib
        srcs/AbstractVmLib/Operand
        srcs/AbstractVmLib/Parse)
set_target_properties(${ABSTRACT_VM_TESTS}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )
