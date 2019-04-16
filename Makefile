# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/09 15:57:06 by cuzureau          #+#    #+#              #
#    Updated: 2019/02/18 16:26:27 by jayache          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

CC= gcc
TEST= ok

ifeq ($(TEST),ok)
CFLAGS+= -Wall -Wextra -Werror
else
CFLAGS+=	-g3 -fsanitize=address \
 			-fno-omit-frame-pointer \
			-fsanitize-address-use-after-scope
endif

NOC=\033[0m
OKC=\033[32m
ERC=\033[31m
WAC=\033[33m

INC_PATH = inc/
LFT_PATH = lib/
OBJ_PATH = obj/
SRC_PATH = src/

NAME= lem-in
INC_NAME= lemin.h
OBJ_NAME= $(SRC_NAME:.c=.o)
SRC_NAME= main.c tools.c parse.c algo.c \
		  ft_graph_add_link.c ft_graph_add_node.c ft_graph_new.c \
		  ft_graph_node_new.c ft_graph_node_search.c ft_graph_node_search_type.c \
		  ft_graph_edge_new.c sender.c pathbundle.c best_bundle.c edmond_karps.c \
		  ft_graph_find_reverse.c bfs.c buffer.c int_memset.c


INC= $(addprefix $(INC_PATH), $(INC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))

all:	$(NAME)

$(NAME): $(OBJ) $(INC)
		@echo "$(OKC)lemin$(NOC)	+ obj	$(OKC)[OK]$(NOC)"
		@make -C $(LFT_PATH) --no-print-directory
		@$(CC) $(CFLAGS) -o $@ $(OBJ) -L $(LFT_PATH) -lft
		@echo "$(OKC)lemin$(NOC)	+ exe	$(OKC)[OK]$(NOC)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(DEPDIR) 2> /dev/null || true
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(DEPFLAGS) -o $@ -c $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;

clean:
		@make -C $(LFT_PATH) clean --no-print-directory
		@rm -rf $(OBJ_PATH)
		@rm -rf $(DEPDIR)
		@echo "$(OKC)lemin$(NOC)	- obj	$(OKC)[OK]$(NOC)"

fclean: clean
		@make -C $(LFT_PATH) fclean --no-print-directory
		@rm -rf $(NAME)
		@echo "$(OKC)lemin$(NOC)	- exe	$(OKC)[OK]$(NOC)"

re: fclean all

norme:
	@norminette $(SRC_PATH) $(INC_PATH)

.PHONY: all clean fclean re norme
.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRC_NAME))))
