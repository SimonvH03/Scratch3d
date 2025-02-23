NAME	=	cub3d

CC		=	gcc
CFLAGS	=	-g -O3 -flto -g
# CFLAGS	=	-O3
# CFLAGS	+=	-Wall -Werror -Wextra -g
MLXFLAGS=	-ldl -lglfw -pthread -lm

LMLXDIR	=	./MLX42
LIBMLX	=	$(LMLXDIR)/build/libmlx42.a

LFTDIR	=	./libft
LIBFT	=	$(LFTDIR)/libft.a

INCLUDE	=	./src/_include
HEADERS =	$(INCLUDE)/cub3d.h \
			$(INCLUDE)/gamestate.h \
			$(INCLUDE)/hud.h \
			$(INCLUDE)/paths.h \
			$(INCLUDE)/player.h \
			$(INCLUDE)/render.h

SRCDIR	=	./src
SRC		=	$(SRCDIR)/TESTmain.c \
			$(SRCDIR)/gamestate/init_game.c \
			$(SRCDIR)/gamestate/init/init_game_images.c \
			$(SRCDIR)/gamestate/init_player.c \
			$(SRCDIR)/gamestate/init/read_elements.c \
			$(SRCDIR)/gamestate/init/read_map.c \
			$(SRCDIR)/gamestate/init_window.c \
			$(SRCDIR)/utils/image_iteration.c \
			$(SRCDIR)/utils/modlx.c \
			$(SRCDIR)/utils/test.c 

OBJDIR	=	./obj
OBJ		=	$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all:  $(NAME)

$(LIBMLX):
	cmake $(LMLXDIR) -B $(LMLXDIR)/build && make -C $(LMLXDIR)/build -j4

$(LIBFT):
	make -C $(LFTDIR) all -s

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< -I ./MLX42/include -I ./src/_include -I ./libft

$(NAME): $(LIBMLX) $(LIBFT) $(OBJDIR) $(OBJ)
	$(CC) $(OBJ) $(LIBMLX) $(MLXFLAGS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C $(LFTDIR) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJDIR)
	rm -f $(LIBFT)
	rm -rf $(LMLXDIR)/build

re: clean all

.PHONY: all clean fclean re