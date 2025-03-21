/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 23:12:54 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/07 23:12:54 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct  s_player
{
    float      x;
    float      y;
    float      dir;
    float      fov;

    bool        up;
    bool        left;
    bool        right;
    bool        down;

    bool        sprint;

    bool        rotate_left;
    bool        rotate_right;
}               t_player;

typedef struct s_texture_struct
{
	char        *path;
	void        *img;
	char        *data;
	int         bpp;
	int         size_line;
	int         endian;
	int         width;
	int         height;
}               t_texture_struct;

typedef struct  s_map
{
    char        		**map;
	t_texture_struct   	texture[4];
    int         		colors[2];    
    int         		width;
    int         		height;
    int         		settings_end;
}               t_map;

typedef struct  s_map_line
{
    char               *line;
    struct s_map_line  *next;
}               t_map_line;

typedef struct s_cub3d
{
    void        *mlx;
    void        *win;
    void        *img;

    char        *data;
    int         bpp;
    int         size_line;
    int         endian;

    t_player    player;
    t_map       map;
    int         fd;
}               t_cub3d;

#endif