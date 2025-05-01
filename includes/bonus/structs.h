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

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include "define.h"
# include "cub3d.h"

typedef struct s_rgb
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}				t_rgb;

typedef struct s_vec2
{
	int			x;
	int			y;
}				t_vec2;

typedef struct s_dvec2
{
	double			x;
	double			y;
}				t_dvec2;

typedef struct s_dvec3
{
	double			x;
	double			y;
	double			z;
}				t_dvec3;

typedef struct s_player
{
	t_dvec2			pos;
	t_vec2			spawn_pos;
	float			angle;
	float			speed;
	t_dvec2			plane;
	bool			up;
	bool			left;
	bool			right;
	bool			down;
	bool			interact;
	bool			sprint;
	bool			rotate_left;
	bool			rotate_right;
	float			pitch;
	bool			look_up;
	bool			look_down;
}				t_player;

typedef struct s_texture_struct
{
	char			*path;
	char			*data;
	void			*img;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}				t_texture_struct;

typedef struct s_sky_data
{
	double				h_fov;
	double				start_ang;
	double				ang;
	t_texture_struct	sky;
	t_vec2				tex_pos;
	int					half_h;
	int					horizon;
	int					color;
	int					x;
}				t_sky_data;

typedef struct s_map
{
	char				**map;
	t_texture_struct	texture[TEXTURE_AMOUNT + 1];
	int					colors[2];
	int					width;
	int					height;
	int					settings_end;
}				t_map;

typedef struct s_map_line
{
	char				*line;
	struct s_map_line	*next;
}				t_map_line;

typedef struct s_hit
{
	double			dist;
	double			x_wall;
	bool			is_door;
	t_facing		facing;
	t_vec2			pos;
	t_dvec2			dir;
	char			type;
}				t_hit;

typedef struct s_ray
{
	t_vec2			map_pos;
	t_vec2			step;
	t_dvec2			dir;
	t_dvec2			side_dist;
	t_dvec2			delta_dist;
	int				flag;
	bool			is_hit;
	t_hit			hit;
	double			camera_x;
	double			perpwalldist;
}				t_ray;

typedef struct s_floor_data
{
	double				p;
	double				pos_z;
	double				row_dist;
	t_dvec2				dir;
	t_dvec2				step;
	t_vec2				cell;
	t_vec2				tex_pixel;
	unsigned int		color;
	t_ray				first;
	t_ray				last;
	t_vec2				tex_pos;
}				t_floor_data;

typedef struct s_fps
{
	struct timeval	last_time;
	int				frame_count;
	double			fps;
}				t_fps;

typedef struct s_cub3d
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				fd;
	int				size_line;
	int				endian;
	t_player		player;
	t_map			map;
	t_ray			*ray;
	t_fps			fps_data;
	t_sky_data		sky_data;
	t_floor_data	floor_data;
}				t_cub3d;

#endif
