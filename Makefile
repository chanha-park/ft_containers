# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 17:24:07 by chanhpar          #+#    #+#              #
#    Updated: 2023/01/12 18:47:32 by chanhpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL	:= all

CXX				:= c++
RM				:= rm -f
# DEPDIR			:= .deps

CXXFLAGS		:= -MMD -Wall -Wextra -Werror -std=c++98 -pedantic -O3 -MMD -MP
CPPFLAGS		:= -I.
# DEPFLAGS		:= -MMD -MP #$(DEPDIR)/$(DEPS)
# CXXFLAGS		+= $(DEPFLAGS)

# OUTPUT_OPTION	:= -o $@

SRCS			:= main.cpp
OBJS			:= $(SRCS:.cpp=.o)
DEPS			:= $(SRCS:.cpp=.d)
-include $(DEPS)

# INC_FILE		:= type_traits.hpp \
#                    utility.hpp \
#                    iterator.hpp \
#                    memory.hpp \
#                    algorithm.hpp \
#                    vector.hpp \
#                    stack.hpp \
#                    tree__.hpp \
#                    map.hpp \
#                    set.hpp

# INC_DIR			:= ./include
# INC				:= $(addprefix $(INC_DIR), $(INC_FILE))

NAME			:= test.out

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# $(DEPDIR):
#     mkdir -p $@

.PHONY: clean
clean:
	@$(RM) $(OBJS) $(DEPDIR)/$(DEPS)
	@echo "clean done!"

.PHONY: fclean
fclean: clean
	@$(RM) $(NAME)
	@echo "fclean done!"

.PHONY: re
re: fclean
	$(MAKE) all
