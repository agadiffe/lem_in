# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/14 20:31:10 by agadiffe          #+#    #+#              #
#    Updated: 2017/02/23 12:04:31 by agadiffe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----------------------------------------------------------------------------
# VARIABLES ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
# ----------------------------------------------------------------------------
NAME = lem-in

CC = gcc
CFLAGS += -Wall -Werror -Wextra

SRC_PATH = ./srcs/
SRC_NAME = main.c

OBJ_PATH = ./obj/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))


INC_PATH = ./includes/
INC = $(addprefix -I,$(INC_PATH))
INC_FILE = $(INC_PATH)$(NAME).h


LIBFT_PATH = ./libft/
LIBFT_NAME = libft.a
LIBFT_INC_PATH = ./libft/includes/
LIBFT = $(addprefix -L,$(LIBFT_PATH))
LIBFT_INC = $(addprefix -I,$(LIBFT_INC_PATH))

# ----------------------------------------------------------------------------
# MISC |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
# ----------------------------------------------------------------------------
$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_FILE)
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(LIBFT_INC) $(INC) -o $@ -c $<

# ----------------------------------------------------------------------------
# RULES ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
# ----------------------------------------------------------------------------
all: $(NAME)

$(NAME): $(LIBFT_PATH)$(LIBFT_NAME) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIBFT) -lft

$(LIBFT_PATH)$(LIBFT_NAME):
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_PATH)

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
