/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:18:55 by tbabou            #+#    #+#             */
/*   Updated: 2025/05/01 19:11:04 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALS_H
# define VISUALS_H

# include "cub3d.h"

int				get_trgb(int t, int r, int g, int b);

void			free_map_struct(t_map_line *map);
void			free_cub3d(t_cub3d *cub3d);

void			draw_square(t_vec2 coords, int size, int color, t_cub3d *cub3d);
void			put_pixel(int x, int y, int color, t_cub3d *cub3d);

void			perform_dda(t_cub3d *cub3d, t_ray *ray);

unsigned int	get_pixel_from_tex(int x, int y, t_texture_struct tex,
					t_hit hit);

#endif