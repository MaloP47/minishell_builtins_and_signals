# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/12 17:13:34 by mpeulet           #+#    #+#              #
#    Updated: 2023/11/13 13:23:26 by mpeulet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Colors / base 16 / Bright

DEF_COLOR		= \033[0;39m
GREY			= \033[0;90m
RED				= \033[0;91m
GREEN			= \033[0;92m
YELLOW			= \033[0;93m
BLUE			= \033[0;94m
MAGENTA			= \033[0;95m
CYAN			= \033[0;96m
WHITE			= \033[0;97m
ORANGE			= \033[38;5;214m

#Libft

LIBFT_DIR		= libft/
LIBFT_NAME		= libft.a
LIBFT			= $(LIBFT_DIR)$(LIBFT_NAME)

#Variables

NAME			= minishell
CC				= cc
FLAGS			= -Wall -Werror -Wextra -g3 
LFLAGS			= -lreadline
RM				= rm -rf
TXT				= *txt
VMINI			= valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes\
					 --suppressions=/mnt/nfs/homes/mpeulet//Cursus42/minishell/minishell.supp
					# --suppressions=/root/ProjetsCode/for_github/minishell_group/minishell.supp
ERR				= 2>> error.txt
MESS			= 3>> message.txt
AR				= ar rcs
NORM			= ./includes
INCLUDE			= 	-I ./includes/\
					-I ./libft/include/

#Sources

OBJ_DIR_M 		= obj/
SRC_DIR_M		= src/
SRC_FUNCTIONS_M	= cd echo env exit export export_noargs pwd sigaction_utils signals unset unset_utils utils 

MINI_SRC		= $(addprefix $(SRC_DIR_M), $(addsuffix .c, $(SRC_FUNCTIONS_M)))
MINI_OBJ		= $(addprefix $(OBJ_DIR_M), $(addsuffix .o, $(SRC_FUNCTIONS_M)))

IFMAKE_DIR_M	= .cache_exists

all:			$(NAME)

$(IFMAKE_DIR_M):
					@mkdir -p $(OBJ_DIR_M)

$(LIBFT):
					@echo "$(GREY)Getting libft ready...$(DEF_COLOR)"
					@make -sC $(LIBFT_DIR)

$(OBJ_DIR_M)%.o: $(SRC_DIR_M)%.c | $(IFMAKE_DIR_M)
					@echo "$(ORANGE)Loading... $< $(DEF_COLOR)"
					@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(NAME): 		$(LIBFT) $(MINI_OBJ)
					@echo "$(GREY)Compiling minishell...$(DEF_COLOR)"
					@$(CC) $(FLAGS) -o $(NAME) src/main.c $(MINI_OBJ) $(LIBFT) $(INCLUDE) $(LFLAGS)
					@echo "$(GREEN)minishell ready.$(DEF_COLOR)"

clean:
					@echo "$(MAGENTA)minishell objects files cleaned!$(DEF_COLOR)"
					@$(RM) $(OBJ_DIR_M)
					
fclean:			clean
					@echo "$(RED)minishell removed.$(DEF_COLOR)"
					@$(RM) $(NAME)
					@$(RM) $(TXT)
					@make fclean -sC $(LIBFT_DIR)

re:				fclean all
					@echo "$(BLUE)Cleaned and rebuilt everything for minishell$(DEF_COLOR)"

rlleaks:		$(NAME)
					$(VMINI) ./minishell

main:
					@$(CC) $(FLAGS) -o $(NAME) src/main.c $(MINI_OBJ) $(LIBFT) $(INCLUDE) $(LFLAGS)

norm:
					@norminette $(SRC_DIR_M) $(NORM) | grep -A1 -B1 Error | grep -v 'OK!' || true
					@echo "$(RED)Norminet $(ORANGE)the $(YELLOW)cat $(GREEN)says$(CYAN): $(RED)M$(ORANGE)e$(YELLOW)o$(GREEN)w$(CYAN) !$(BLUE)!$(MAGENTA)!$(DEF_COLOR)"

.PHONY: all clean fclean re rlleaks main norm
