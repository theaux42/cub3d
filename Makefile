###############################################################################
#                                 Variables                                   #
###############################################################################

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -O3
OUTPUT  = cub3d

LIBFT_DIR = ./libs/libft
MLX_DIR   = ./libs/minilibx-linux
COMMON_INC = -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS       = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

MODE ?= classic            # « make bonus » ou « make MODE=bonus »

###############################################################################
#                          Fichiers (listes sans wildcard)                    #
###############################################################################

### ---- fichiers communs / groupés ------------------------------------------
UTILS_FILES      = utils/colors.c utils/free.c
CHECK_FILES      = checks/check.c checks/check_floodfill.c checks/check_other.c
PARSING_BASE     = parsing/init.c parsing/parser.c parsing/parser_checker.c \
                   parsing/parser_map.c parsing/parser_player.c parsing/parser_settings.c \
                   parsing/parser_texture.c parsing/parser_utils.c
PLAYER_BASE      = player/player.c player/player_movement.c
VISUAL_BASE      = visual/dda.c visual/draw_utils.c visual/render.c

### ---- classic --------------------------------------------------------------
CLASSIC_SRC_DIR  = src/classic
CLASSIC_SRCS = \
$(CLASSIC_SRC_DIR)/main.c \
$(addprefix $(CLASSIC_SRC_DIR)/, \
    $(UTILS_FILES) \
    $(PARSING_BASE) \
    $(CHECK_FILES) \
    $(PLAYER_BASE) \
    $(VISUAL_BASE) )

### ---- bonus (ajouts spécifiques à bonus) -----------------------------------
BONUS_SRC_DIR    = src/bonus

# extra parsing / player / visual files propres au bonus
PARSING_BONUS_XTRA = parsing/init_2.c
PLAYER_BONUS_XTRA  = player/player_doors.c player/player_keys.c
VISUAL_BONUS_XTRA  = visual/crosshair.c visual/dda_utils.c visual/draw_floor.c \
                     visual/draw_minimap.c visual/draw_sky.c

BONUS_SRCS = \
$(BONUS_SRC_DIR)/main.c \
$(addprefix $(BONUS_SRC_DIR)/, \
    $(UTILS_FILES) \
    $(PARSING_BASE) $(PARSING_BONUS_XTRA) \
    $(CHECK_FILES) \
    $(PLAYER_BASE) $(PLAYER_BONUS_XTRA) \
    $(VISUAL_BASE) $(VISUAL_BONUS_XTRA) )

###############################################################################
#                       Sélection des sources / includes                      #
###############################################################################

ifeq ($(MODE),bonus)
    SRC_LIST := $(BONUS_SRCS)
    INC_BASE := -I./includes/bonus
else
    SRC_LIST := $(CLASSIC_SRCS)
    INC_BASE := -I./includes/classic
endif

INCLUDES = $(INC_BASE) $(COMMON_INC)
OBJS     = $(SRC_LIST:.c=.o)
CLASSIC_OBJS = $(CLASSIC_SRCS:.c=.o)
BONUS_OBJS   = $(BONUS_SRCS:.c=.o)

###############################################################################
#                                   Règles                                    #
###############################################################################

.PHONY: all bonus clean fclean fcleanlib re sre

all: $(OUTPUT)

bonus:
	$(MAKE) MODE=bonus $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ----------------- nettoyage -------------------------------------------------
clean:
	rm -f $(CLASSIC_OBJS) $(BONUS_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fcleanlib:
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

sre:
	rm -f $(CLASSIC_OBJS) $(BONUS_OBJS) $(OUTPUT)
	$(MAKE) all

fclean: clean
	rm -f $(OUTPUT)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
