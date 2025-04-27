/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/02/07 23:10:25 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/07 23:10:25 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifndef DEFINE_H
# define DEFINE_H

typedef enum e_texture
{
	NO_TEXTURE = 0,
	SO_TEXTURE = 1,
	WE_TEXTURE = 2,
	EA_TEXTURE = 3,
	DOOR_TEXTURE = 4,
	FLOOR_TEXTURE = 5,
	CEILING_TEXTURE = 6,
} t_texture;

typedef enum e_facing
{
    NORTH,
    SOUTH,
    WEST,
    EAST,
	DOOR
}   t_facing;

typedef enum e_colors
{
	FLOOR = 0,
	CEILING = 1
} t_colors;

# define WIDTH 1500
# define HEIGHT 844

# define BLOCK 128
# define MINIMAP_SCALE 10

# define TEXTURE_AMOUNT 7

# define PLAYER_SPEED 0.1
# define CAMERA_SPEED 0.04

# define VALID_CHARS " 10NSWEDd"

# define CROSSHAIR_SIZE 6

# define W 119
# define A 97
# define S 115
# define D 100

# define E 101

# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364

# define SPACE 32

# define ESCAPE 65307
# define MINUS 45
# define PLUS 61

# define SHIFT 65505

# define PI 3.14159265359

# define ERR_MSG "[" RED500 "ERROR" RESET "]  ➞ "
# define DBG_MSG "[" BLUE500 "DEBUG" RESET "]  ➞ "

# define ERR_MINILIBX ERR_MSG "Something wrong hapenned with MiniLibX...\n"
# define ERR_MALLOC ERR_MSG "Malloc failed\n"
# define ERR_WEIRD_MAP ERR_MSG "Badly formatted map...\n"
# define ERR_UNKN_CHAR ERR_MSG "Unknown character '%c' in the map.\n"
# define DBG_MALLOC DBG_MSG "Malloc failed\n"
# define ERR_NO_FTYPE ERR_MSG "The file must be a %s file.\n"
# define ERR_NO_LINE ERR_MSG "Can't get content from map\n"
# define ERR_NO_ARG ERR_MSG "Wrong usage : %s <map>.\n"
# define ERR_EXIST ERR_MSG "This value is being define twice!\n"
# define ERR_FILE_DOESNT_EXIST ERR_MSG "File %s doesn't exist.\n"
# define ERR_COLOR_FORMAT ERR_MSG "A color is wrongly formatted.\n"
# define ERR_MAP_BORDER ERR_MSG "The map is not closed.\n"
# define ERR_NO_PLAYER ERR_MSG "There is no player on the map.\n"
# define ERR_TOO_PLAYER ERR_MSG "There is too much player on the map (%i)\n"
# define ERR_TEXTURE_ID ERR_MSG "Texture ID:%i %s not found.\n"
# define ERR_TEXTURE ERR_MSG "Texture %s not found.\n"

#endif