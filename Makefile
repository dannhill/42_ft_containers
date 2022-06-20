NAME	=	ft_containers

SRCS	:=	$(wildcard *.cpp)

INCL	:=	$(wildcard *.hpp)

OBJS	:=	$(SRCS:.cpp=.o)

CC		:=	clang++

CFLAGS	:=	-std=c++98 -Wall -Wextra -Werror

RM		:=	rm -rf

all:	$(NAME)

debug:	fclean apnd $(NAME)

$(NAME):	$(OBJS) $(INCL)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o:%.cpp
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)
		@$(RM) $(NAME)_DEBUG

re:	fclean all

apnd:
		$(eval CFLAGS += -ggdb3 -fsanitize=address -g)
		$(eval NAME = ft_containers_DEBUG)

.PHONY: all, debug, clean, fclean, re, apnd