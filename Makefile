# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 17:24:07 by chanhpar          #+#    #+#              #
#    Updated: 2023/01/14 05:36:09 by chanhpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL	:= all

CXX				:= c++
RM				:= rm -f

ifdef STD
	CXXFLAGS		:= -Wall -Wextra -Werror -std=c++98 -pedantic -O3 -MMD -MP -DSTD
else
	CXXFLAGS		:= -Wall -Wextra -Werror -std=c++98 -pedantic -O3 -MMD -MP -DFT
endif
CPPFLAGS		:= -I./include -I./test

ifdef DEBUG
	CXXFLAGS += -fsanitize=address -g
endif

SRCS			:= main.cpp
OBJS			:= $(SRCS:.cpp=.o)
DEPS			:= $(SRCS:.cpp=.d)
-include $(DEPS)

INCS			:= type_traits.hpp \
				   iterator.hpp \
				   utility.hpp \
				   algorithm.hpp  \
				   memory.hpp \
				   vector.hpp \
				   stack.hpp \
				   tree__.hpp \
				   map.hpp \
				   set.hpp \

SHELL			:= /bin/bash
SEED			:= $$RANDOM

NAME			:= result.log

NAME_STD		:= std.out
NAME_FT			:= ft.out

OUTPUT_STD		:= std_output.log
OUTPUT_FT		:= ft_output.log


.PHONY: all
all: $(NAME)

$(NAME): | $(addprefix ./include/, $(INCS))
	@echo "seed: $(SEED)"
	$(MAKE) ft
	clean
	STD=1
	$(MAKE) std
	diff $(OUTPUT_STD) $(OUTPUT_FT) > $@

.PHONY: std
std: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME_STD)
	./$(NAME_STD) > $(OUTPUT_STD)

.PHONY: ft
ft: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME_FT)
	./$(NAME_FT) > $(OUTPUT_FT)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPS)
	@echo "clean done!"

.PHONY: fclean
fclean: clean
	$(RM) $(NAME) $(OUTPUT_STD) $(OUTPUT_FT) $(NAME_STD) $(NAME_FT)
	@echo "fclean done!"

.PHONY: re
re: fclean
	$(MAKE) all
