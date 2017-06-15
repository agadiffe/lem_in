# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/14 20:31:10 by agadiffe          #+#    #+#              #
#    Updated: 2017/06/15 18:47:01 by agadiffe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----------------------------------------------------------------------------
# VARIABLES ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
# ----------------------------------------------------------------------------
NAME = lem-in

CC = clang
CFLAGS += -Wall -Werror -Wextra

SRC_PATH = ./srcs/
SRC_NAME = main.c						\
		   print_map.c					\
		   add_pipe.c					\
		   add_pipe_to_room_list.c		\
		   command.c					\
		   is_room.c					\
		   get_functions.c				\
		   handle_data.c				\
		   print_ants_path.c			\
		   add_room.c					\
		   find_path.c					\
		   print_functions_lstiter.c	\
		   free_functions_lstdel.c

OBJ_PATH = ./obj/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))


INC_PATH = ./includes/
INC = $(addprefix -I,$(INC_PATH))
INC_FILE = $(INC_PATH)lem_in.h


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
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lft

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
