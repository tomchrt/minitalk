NAME = so_long

CC = cc

CFLAGS = -Wall -Werror -Wextra

LIB = -Lmlx -lmlx_Linux -Llibft -lft -Imlx -L/usr/lib -lXext -lX11 -lm -lz

ifdef BONUS
	INC = so_long_bonus.h get_next_line.h libft/libft.h
else
	INC = so_long.h get_next_line.h libft/libft.h
endif

SRCS = main.c \
	   get_next_line.c \
	   get_next_line_utils.c \
	   errors.c \
	   parse_map.c \
	   free_utils.c \
	   check_map.c \
	   check_map_utils.c \
	   image_to_map.c \
	   image_to_map_utils.c \
	   moves.c \
	   moves_utils.c\
	   get_next_line.c\
	   get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -I/usr/include -Imlx -c $< -o $@

$(NAME): $(OBJS) Makefile libft mlx $(INC)
	$(MAKE) -C mlx
	$(CC) -g $(CFLAGS) $(OBJS) $(LIB) -o $@

all: $(NAME)

FORCE:

mlx: FORCE
	$(MAKE) -C mlx

libft: FORCE
	$(MAKE) -C libft

clean:
	$(MAKE) clean -C mlx
	$(MAKE) clean -C libft
	rm -rf $(OBJS) $(OBJSB)

fclean:
	$(MAKE) clean -C mlx
	$(MAKE) fclean -C libft
	rm -rf $(OBJS) $(OBJSB)
	rm -f $(NAME)

re: fclean all

normi:
	norminette $(SRCS) $(SRCSB) libft/*.* so_long.h so_long_bonus.h get_next_line.c get_next_line_utils.c get_next_line.h

.PHONY: all clean fclean re normi
