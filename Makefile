# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 09:20:53 by hzakharc          #+#    #+#              #
#    Updated: 2024/10/16 15:16:05 by hzakharc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR			=	src/

SRC				=	$(SRC_DIR)/main.c $(SRC_DIR)/util.c $(SRC_DIR)/philo.c

OBJS			=	$(SRC:.c=.o)

BLUE		=	\033[0;94m
RED 		=	\033[0;91m
GREEN		=	\033[0;92m
YELLOW		=	\e[0;33m
CYAN		=	\033[0;96m
COLOR		=	\033[0m

CC				=	@cc -Wall -Werror -Wextra
RM				=	@rm -f

NAME			=	philo

ASCII			=	@./ascii.sh

%.o:			%.c
					$(CC) -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(OBJS) -o $(NAME)
				$(ASCII) 1

clean:
					$(RM) $(OBJS)

fclean:			clean
					$(RM) $(NAME)
					$(ASCII) 2

re:				fclean all

spongebob:			
				@firefox https://www.youtube.com/watch?v=GEVsRCQLugw


.PHONY:			all clean fclean re spongebob