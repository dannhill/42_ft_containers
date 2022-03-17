NAME	:=	ft_containers

SRCS	:=	$(wildcard ./*.cpp)

INCL	:=	$(wildcard ./*.hpp)

OBJS	:=	$(SRCS:.cpp=.o)

CC		:=	clang++

CFLAGS	:=	-std=c++98 -Wall -Wextra -Werror

RM		:=	rm -rf

all:	$(NAME)

$(NAME):	$(OBJS) $(INCL)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o:%.c
		$(CC) $(CFLAGS) -c $@ -o $<

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:	fclean all

.PHONY: all, clean, fclean, re