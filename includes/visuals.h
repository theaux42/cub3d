/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:18:55 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/25 15:07:58 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

#ifndef VISUALS_H
# define VISUALS_H

int     get_trgb(int t, int r, int g, int b);

void    free_map_struct(t_map_line *map);
void    free_cub3d(t_cub3d *cub3d);

void	draw_square(t_vec2 coords, int size, int color, t_cub3d *cub3d);
void    put_pixel(int x, int y, int color, t_cub3d *cub3d);
void    draw_map(t_cub3d *cub3d);

void	perform_calculation(t_cub3d *cub3d, t_ray *ray, int x);
void	perform_dda(t_cub3d *cub3d, t_ray *ray, bool is_crosshair);

void	draw_crosshair(t_cub3d *cub3d, t_ray *ray);

unsigned int get_pixel_from_tex(int x, int y, t_texture_struct tex, t_hit hit);

char get_wall_orientation(t_cub3d *cub3d, float hitX, float hitY, float ray_angle);

#endif