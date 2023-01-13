# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 17:24:07 by chanhpar          #+#    #+#              #
#    Updated: 2023/01/13 17:15:55 by chanhpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL	:= all

CXX				:= c++
RM				:= rm -f

CXXFLAGS		:= -Wall -Wextra -Werror -std=c++98 -pedantic -O3 -MMD -MP
CPPFLAGS		:= -I./include -I./test

ifdef DEBUG
	CXXFLAGS += -fsanitize=address -g
endif

ifdef STD
	CXXFLAGS += -DSTD
endif

SRCS			:= main.cpp
OBJS			:= $(SRCS:.cpp=.o)
DEPS			:= $(SRCS:.cpp=.d)
-include $(DEPS)

NAME			:= a.out

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
	$(RM) $(NAME) "std_output.txt" "ft_output.txt"
	@echo "fclean done!"

.PHONY: re
re: fclean
	$(MAKE) all
