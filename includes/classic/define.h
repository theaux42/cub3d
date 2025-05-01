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

#ifndef DEFINE_H
# define DEFINE_H

typedef enum e_texture
{
	NO_TEXTURE = 0,
	SO_TEXTURE = 1,
	WE_TEXTURE = 2,
	EA_TEXTURE = 3,
}	t_texture;

typedef enum e_facing
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_facing;

typedef enum e_colors
{
	FLOOR = 0,
	CEILING = 1
}	t_colors;

# define WIDTH 1280
# define HEIGHT 720

# define BLOCK 128

# define MINIMAP_PLAYER_SIZE 4

# define TEXTURE_AMOUNT 4

# define PLAYER_SPEED 0.1f
# define CAMERA_SPEED 0.05f

# define VALID_CHARS " 10NSWEDds"

# define W 119
# define A 97
# define S 115
# define D 100

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

# define ERR_MSG "[ERROR]   ➞ "

# define ERR_MINILIBX "[ERROR]  ➞ Something wrong hapenned with MiniLibX...\n"
# define ERR_MALLOC "[ERROR]  ➞ Malloc failed\n"
# define ERR_WEIRD_MAP "[ERROR]  ➞ Badly formatted map...\n"
# define ERR_UNKN_CHAR "[ERROR]  ➞ Unknown character '%c' in the map.\n"
# define DBG_MALLOC "[DEBUG]  ➞ Malloc failed\n"
# define ERR_NO_FTYPE "[ERROR]  ➞ The file must be a %s file.\n"
# define ERR_NO_LINE "[ERROR]  ➞ Can't get content from map\n"
# define ERR_NO_ARG "[ERROR]  ➞ Wrong usage : %s <map>.\n"
# define ERR_EXIST "[ERROR]  ➞ This value is being defined twice!\n"
# define ERR_FILE_DOESNT_EXIST "[ERROR]  ➞ File %s doesn't exist.\n"
# define ERR_COLOR_FORMAT "[ERROR]  ➞ A color is wrongly formatted.\n"
# define ERR_MAP_BORDER "[ERROR]  ➞ The map is not closed.\n"
# define ERR_NO_PLAYER "[ERROR]  ➞ There is no player on the map.\n"
# define ERR_TOO_PLAYER "[ERROR]  ➞ There is too much player on the map (%i)\n"
# define ERR_TEXTURE_ID "[ERROR]  ➞ Texture ID:%i %s not found.\n"
# define ERR_TEXTURE "[ERROR]  ➞ Texture %s not found.\n"

#endif