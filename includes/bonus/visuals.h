/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:18:55 by tbabou            #+#    #+#             */
/*   Updated: 2025/05/01 18:22:39 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALS_H
# define VISUALS_H

# include "cub3d.h"

int				get_trgb(int t, int r, int g, int b);

void			free_map_struct(t_map_line *map);
void			free_cub3d(t_cub3d *cub3d);
void			put_pixel(t_vec2 pos, int color, t_cub3d *cub3d);
void			draw_floor_line2(t_floor_data *f, t_cub3d *cub3d);
void			init_floor(t_cub3d *cub3d, t_floor_data *f);

void			vert_sky_cal(t_sky_data *sky_data, int x);
void			horiz_sky_cal(t_cub3d *cub3d, t_sky_data *sky_data, int x,
					int y);
void			init_sky(t_cub3d *cub3d, t_sky_data *sky_data);

void			draw_minimap(t_cub3d *cub3d);

void			draw_square(t_cub3d *cub3d, t_vec2 pos, int size, int color);

void			perform_dda(t_cub3d *cub3d, t_ray *ray, int x,
					bool is_crosshair);

void			draw_crosshair(t_cub3d *cub3d, t_ray *ray);

unsigned int	get_pixel_from_tex(t_vec2 pos, t_texture_struct tex, t_hit hit);

#endif