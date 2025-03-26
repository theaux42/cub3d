/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:18:55 by tbabou            #+#    #+#             */
/*   Updated: 2025/03/25 20:55:50 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

#ifndef VISUALS_H
# define VISUALS_H

int     get_trgb(int t, int r, int g, int b);

void    free_map_struct(t_map_line *map);
void    free_cub3d(t_cub3d *cub3d);

void    ft_mlx_clear_image(t_cub3d *cub3d);
void    draw_square(int x, int y, int size, int color, t_cub3d *cub3d);
void    put_pixel(int x, int y, int color, t_cub3d *cub3d);
void    draw_map(t_cub3d *cub3d);

char get_wall_orientation(t_cub3d *cub3d, float hitX, float hitY, float ray_angle);

#endif