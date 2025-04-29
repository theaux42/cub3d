/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:16:43 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/29 18:40:25 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_pixel_from_tex(t_vec2 pos, t_texture_struct tex, t_hit hit)
{
	unsigned int	*img;
	unsigned int	color;
	double			shade_factor;
	t_rgb			rgb;
	double			direction_shade;

	if (pos.x >= tex.width || pos.y >= tex.height || pos.x < 0 || pos.y < 0)
		return (0x000000);
	img = (unsigned int *)tex.data;
	color = img[pos.y * tex.width + pos.x];
	shade_factor = 1.0 - fmin(0.7, hit.dist / 15.0);
	shade_factor = fmax(0.2, shade_factor);
	direction_shade = 1.0;
	if (hit.facing == NORTH || hit.facing == SOUTH)
		direction_shade = 0.9;
	else if (hit.facing == EAST || hit.facing == WEST)
		direction_shade = 0.8;
	shade_factor *= direction_shade;
	rgb.r = ((color >> 16) & 0xFF) * shade_factor;
	rgb.g = ((color >> 8) & 0xFF) * shade_factor;
	rgb.b = (color & 0xFF) * shade_factor;
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

void	draw_square(t_cub3d *cub3d, t_vec2 pos, int size, int color)
{
	t_vec2			cursor;
	unsigned int	*img;
	unsigned int	*row;

	if (pos.x >= WIDTH || pos.y >= HEIGHT || pos.x < 0 || pos.y < 0)
		return ;
	cursor = (t_vec2){0, 0};
	img = (unsigned int *)cub3d->data;
	while (cursor.y < size)
	{
		row = img + ((pos.y + cursor.y) * WIDTH + pos.x);
		cursor.x = 0;
		while (cursor.x < size)
		{
			row[cursor.x] = (unsigned int)color;
			cursor.x++;
		}
		cursor.y++;
	}
}

void	put_pixel(t_vec2 pos, int color, t_cub3d *cub3d)
{
	unsigned int	*img;

	if (pos.x >= WIDTH || pos.y >= HEIGHT || pos.x < 0 || pos.y < 0)
		return ;
	img = (unsigned int *)cub3d->data;
	img[pos.y * WIDTH + pos.x] = color;
}
