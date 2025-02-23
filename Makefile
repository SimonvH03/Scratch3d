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

HEADERS =	./cub3d.h \
			./gamestate.h \
			./hud.h \
			./paths.h \
			./player.h \
			./render.h

SRCDIR	=	./src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/modlx.c \
			$(SRCDIR)/hud/draw_map_player.c \
			$(SRCDIR)/hud/draw_minimap_walls.c \
			$(SRCDIR)/initialise/draw_game_images.c \
			$(SRCDIR)/initialise/draw_menu_images.c \
			$(SRCDIR)/initialise/init_game_images.c \
			$(SRCDIR)/initialise/init_game_structs.c \
			$(SRCDIR)/initialise/init_menu_images.c \
			$(SRCDIR)/initialise/init_menu_structs.c \
			$(SRCDIR)/initialise/read_cub_elements.c \
			$(SRCDIR)/initialise/read_map_init_camera.c \
			$(SRCDIR)/user_interface/arrowkey_turn.c \
			$(SRCDIR)/user_interface/keyhooks.c \
			$(SRCDIR)/user_interface/up_down_select.c \
			$(SRCDIR)/user_interface/view_manager.c \
			$(SRCDIR)/user_interface/wasd_move.c \
			$(SRCDIR)/render/arithmetic.c \
			$(SRCDIR)/render/raycast.c \
			$(SRCDIR)/render/draw_texture_column.c \
			$(SRCDIR)/test.c

OBJDIR	=	./obj
OBJ		=	$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all:  $(NAME)

$(LIBMLX):
	cmake $(LMLXDIR) -B $(LMLXDIR)/build \
			-DCMAKE_BUILD_TYPE=Debug \
			-DDEBUG=ON \
			-DCMAKE_C_FLAGS="-g" \
			-DCMAKE_CXX_FLAGS="-g" \
			-DGLFW_FETCH=ON \
			-DBUILD_TESTS=OFF
	make -C $(LMLXDIR)/build -j4

$(LIBFT):
	make -C $(LFTDIR) all -s

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< -I MLX42/include libft

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