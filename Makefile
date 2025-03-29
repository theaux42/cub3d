COMPILER = cc
CFLAGS = -Wall -Wextra -Werror -g3
OUTPUT = cub3d

LIBFT_DIR = ./libs/libft
MLX_DIR = ./libs/minilibx-linux
INCLUDES = -I./includes -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

MAIN_FILE = main.c
UTILS_FILES = colors.c free.c get_dir.c
PARSING_FILES = parser.c parser_settings.c parser_texture.c parser_utils.c \
		parser_map.c parser_player.c init.c
PLAYER_FILES = player.c player_raycast.c 
VISUAL_FILES = draw_utils.c

PARSING = $(addprefix src/parsing/, $(PARSING_FILES))
VISUAL = $(addprefix src/visual/, $(VISUAL_FILES))
PLAYER = $(addprefix src/player/, $(PLAYER_FILES))
UTILS = $(addprefix src/utils/, $(UTILS_FILES))
MAIN = $(addprefix src/, $(MAIN_FILE))

SRCS = $(PARSING) $(UTILS) $(MAIN) $(VISUAL) $(PLAYER)
OBJS = $(SRCS:.c=.o)

all: $(OUTPUT)

$(OUTPUT): $(OBJS)
	make -C $(LIBFT_DIR)
	make -C $(MLX_DIR)
	$(COMPILER) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

%.o: %.c
	$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fcleanlib:
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean

sre: 
	rm -f $(OBJS)
	rm -f $(OUTPUT)
	all

fclean: clean
	rm -f $(OUTPUT)
	make -C $(LIBFT_DIR) fclean

re: fclean all