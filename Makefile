SRCS	= main.c all_the_parsing_is_here_part_two.c cub3d_utils.c \
		get_textures.c cub3d.c key_hooks.c printworld.c minimap.c \
		cub3d_utils2.c sprites.c sprites_utils.c get_textures2.c \
		free.c minimap2.c cub3d2.c time_utils.c key_hooks2.c

OBJS	= ${SRCS:.c=.o}

NAME	= cub3D

MINILIB	= mlx/libmlx.a

PATHMLIB	= mlx/

PATHLIB	= libft/

LIBFT	= libft/libft.a

CC	= gcc

RM	= rm -f

CFLAGS	= -I. -Wall -Wextra -Werror -Imlx #-g3 -fsanitize=address

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
				@make -C ${PATHLIB}
				@make -C ${PATHMLIB}
				${CC} ${CFLAGS} ${MINILIB} ${LIBFT} ${OBJS} -L./mlx -lmlx -framework OpenGL -framework AppKit -L. -o ${NAME}

all:		${NAME}

clean:
				@make clean -C ${PATHLIB}
				@make clean -C ${PATHMLIB}
				${RM} ${OBJS}

fclean: 	clean
				@make clean
				${RM} ${LIBFT}
				${RM} ${MINILIB}
				${RM} ${NAME}

re: 		fclean all

.PHONY:		all clean fclean re
