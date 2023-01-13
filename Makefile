# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 17:24:07 by chanhpar          #+#    #+#              #
#    Updated: 2023/01/13 15:21:15 by chanhpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL	:= all

CXX				:= c++
RM				:= rm -f

CXXFLAGS		:= -Wall -Wextra -Werror -std=c++98 -pedantic -O3 -MMD -MP
CPPFLAGS		:= -I./include

ifdef DEBUG
	CXXFLAGS += -fsanitize=address -g
endif

SRCS			:= main.cpp
OBJS			:= $(SRCS:.cpp=.o)
DEPS			:= $(SRCS:.cpp=.d)
-include $(DEPS)

NAME			:= test.out

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPS)
	@echo "clean done!"

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	@echo "fclean done!"

.PHONY: re
re: fclean
	$(MAKE) all
