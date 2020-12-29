NAME = avm

CXX = clang++
CXXFLAGS = -Wall -Werror -Wextra -std=c++11

SRC_DIR = ./srcs
SRC = AbstractVmStack.cpp \
	  CommandList.cpp \
	  main.cpp \
	  utilities.cpp \
	  Operand/OperandExceptions.cpp \
	  Operand/OperandFactory.cpp \
	  Parse/Lexer.cpp \
	  Parse/Parser.cpp
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))

OBJ_DIR = ./objs
PARSE_OBJ_DIR = ./objs/Parse
OPERAND_OBJ_DIR = ./objs/Operand
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

INCLUDE_DIRS = -Isrcs \
			   -Isrcs/Operand \
			   -Isrcs/Parse

INCLUDES = srcs/*.hpp \
		   srcs/Operand/*.hpp \
		   srcs/Parse/*.hpp

all: $(NAME)

$(NAME): $(OBJ_DIR) $(PARSE_OBJ_DIR) $(OPERAND_OBJ_DIR) $(INCLUDES) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -o $@ -c $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(PARSE_OBJ_DIR):
	mkdir -p $(PARSE_OBJ_DIR)

$(OPERAND_OBJ_DIR):
	mkdir -p $(OPERAND_OBJ_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
