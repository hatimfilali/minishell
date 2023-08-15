src = echo.c ft_split.c env.c cd.c pwd.c ft_begin.c handl_signals.c

main = main.c
NAME = minishell

obj = ${src:.c=.o}
main_obj = ${main:.c=.o}

# CFLAGS = -Wall -Wextra -Werror
libreadline = -lreadline -L/Users/hfilali/homebrew/opt/readline/lib
incldlib = -I/Users/hfilali/homebrew/opt/readline/include

all : $(NAME)

$(NAME) : $(main_obj) $(obj)
	@gcc-11 $(main_obj) $(obj) $(libreadline) -o $(NAME)
	@echo "MINISHELL IS READY✅✅"

%.o : %.c
	@gcc-11 $(CFLAGS) -c $< -o $@
clean :
	@rm -rf $(main_obj) $(obj) 
	@echo "OBJECT FILES HAS BEEN DELETED🚮🚮"

fclean : clean
	@rm -rf $(NAME)
	@echo "MINISHELL HAS BEEN DELETED🚮🚮"

re : fclean $(NAME)
