NAME	=	cub3d

CC		=	cc
CFLAGS	=	-g -O3
# CFLAGS	+=	-Wall -Werror -Wextra
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
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/gamestate/init_game.c \
			$(SRCDIR)/gamestate/init/init_game_images.c \
			$(SRCDIR)/gamestate/init_player.c \
			$(SRCDIR)/gamestate/init_weapon.c \
			$(SRCDIR)/gamestate/init/read_elements.c \
			$(SRCDIR)/gamestate/init/read_map.c \
			$(SRCDIR)/gamestate/init_window.c \
			$(SRCDIR)/hud/init/new_images_bigmap.c \
			$(SRCDIR)/hud/init/new_images_menu.c \
			$(SRCDIR)/hud/init/new_images_minimap.c \
			$(SRCDIR)/hud/init_hud.c \
			$(SRCDIR)/hud/init_menu.c \
			$(SRCDIR)/hud/update_bigmap.c \
			$(SRCDIR)/hud/update_minimap.c \
			$(SRCDIR)/render/draw_texture_column.c \
			$(SRCDIR)/render/raycast.c \
			$(SRCDIR)/user_interface/arrowkey_turn.c \
			$(SRCDIR)/user_interface/frametime_variables.c \
			$(SRCDIR)/user_interface/keyhooks.c \
			$(SRCDIR)/user_interface/select_button.c \
			$(SRCDIR)/user_interface/view_manager.c \
			$(SRCDIR)/user_interface/wasd_move.c \
			$(SRCDIR)/user_interface/weapon_animation.c \
			$(SRCDIR)/utils/arithmetic_float.c \
			$(SRCDIR)/utils/arithmetic_int.c \
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
	$(CC) $(CFLAGS) -o $@ -c $< -I ./MLX42/include -I ./src/_include -I ./libft -I ./

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