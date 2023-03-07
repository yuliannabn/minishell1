##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## makefile
##

NAME = mysh

TARGET =	src/main.c										\
			src/builtins/builtin_misc.c						\
			src/builtins/unset_env.c						\
			src/builtins/set_env.c							\
			src/builtins/cd.c								\
			src/builtins/cd_misc.c							\
			src/builtins/env.c								\
			src/builtins/exit.c								\
			src/toolkit_parsing/parse_arguments.c			\
			src/toolkit_parsing/prompt_check.c	  			\
			src/toolkit_parsing/define_binary.c				\
			src/toolkit_parsing/execute_binary.c			\
			src/toolkit_parsing/misc_tools.c	  			\
			src/toolkit_parsing/prompt_wait.c	  			\

FLAGS = -W -Wall -Wpedantic -Wno-long-long -g -Werror

INCLUDE = -I include/

all = $(NAME)

$(NAME):
	cd lib; make
	gcc -o $(NAME) $(TARGET) $(INCLUDE) $(FLAGS) -L lib/ -lmy

clean:
	cd lib; make clean
	rm -f *#
	rm -f *~

fclean: clean
	cd lib; make fclean
	rm -f $(NAME)

re: fclean $(NAME)
