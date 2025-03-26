/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 23:10:25 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/07 23:10:25 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

#ifndef DEFINE_H
# define DEFINE_H

typedef enum e_texture
{
    NO_TEXTURE = 0,
    SO_TEXTURE = 1,
    WE_TEXTURE = 2,
    EA_TEXTURE = 3
} t_texture;

typedef enum e_colors
{
    FLOOR = 0,
    CEILING = 1
} t_colors;

# define WIDTH 1280
# define HEIGHT 720

# define BLOCK 128
# define MINIMAP_SCALE 10

# define PLAYER_SPEED 10
# define CAMERA_SPEED 0.02

# define W 119
# define A 97
# define S 115
# define D 100

# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364

# define MINUS 45
# define PLUS 61

# define SHIFT 65505

# define PI 3.14159265359

# define ERR_MSG "[" RED500 "ERROR" RESET "] ➞ "

# define ERR_MINILIBX ERR_MSG "Something wrong hapenned with MiniLibX...\n"
# define ERR_MALLOC ERR_MSG "Malloc failed\n"
# define ERR_NO_ARG ERR_MSG "Wrong usage : %s <map>.\n"
# define ERR_EXIST ERR_MSG "This value is being define twice!\n"
# define ERR_COLOR_FORMAT ERR_MSG "A color is wrongly formatted\n."
# define ERR_NO_PLAYER ERR_MSG "There is no player on the map.\n"
# define ERR_TEXTURE ERR_MSG "Texture %s not found.\n"

#endif