/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:18:55 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/27 03:46:07 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

#ifndef VISUALS_H
# define VISUALS_H

int     get_trgb(int t, int r, int g, int b);

void    free_map_struct(t_map_line *map);
void    free_cub3d(t_cub3d *cub3d);

void	draw_square(t_vec2 coords, int size, int color, t_cub3d *cub3d);
void    put_pixel(t_vec2 pos, int color, t_cub3d *cub3d);
void    draw_map(t_cub3d *cub3d);

void	draw_floor(t_cub3d *cub3d);

void	perform_dda(t_cub3d *cub3d, t_ray *ray,  int x, bool is_crosshair);

void	draw_crosshair(t_cub3d *cub3d, t_ray *ray);

unsigned int get_pixel_from_tex(t_vec2 pos, t_texture_struct tex, t_hit hit);

#endif