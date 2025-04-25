/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:16:43 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/25 19:55:42 by theaux           ###   ########.fr       */
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
	shade_factor = 1.0 - fmin(0.7, hit.dist / 14.0);
	shade_factor = fmax(0.2, shade_factor);
	direction_shade = 1.0;
	if (hit.facing == 'N' || hit.facing == 'S')
		direction_shade = 0.1;
	else if (hit.facing == 'E' || hit.facing == 'W')
		direction_shade = 10.0;
	shade_factor *= direction_shade;
	rgb.r = ((color >> 16) & 0xFF) * shade_factor;
	rgb.g = ((color >> 8) & 0xFF) * shade_factor;
	rgb.b = (color & 0xFF) * shade_factor;
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

// unsigned int	get_pixel_from_tex(int x, int y, t_texture_struct tex,
// 		t_hit hit)
// {
// 	(void)hit;
// 	unsigned int *img;

// 	if(x >= tex.width || y >= tex.height || x < 0 || y < 0)
// 		return (0x000000);

// 	img = (unsigned int *)tex.data;
// 	return (img[y * tex.width + x]);
// }

void	put_pixel(t_vec2 pos, int color, t_cub3d *cub3d)
{
	unsigned int	*img;

	if (pos.x >= WIDTH || pos.y >= HEIGHT || pos.x < 0 || pos.y < 0)
		return ;
	img = (unsigned int *)cub3d->data;
	img[pos.y * WIDTH + pos.x] = color;
}

// void	draw_square(t_vec2 coords, int size, int color, t_cub3d *cub3d)
// {
// 	t_vec2	pos;

// 	pos = (t_vec2){0, 0};
// 	while (pos.y < size)
// 	{
// 		pos.x = 0;
// 		while (pos.x < size)
// 		{
// 			put_pixel(coords.x + pos.y, coords.y + pos.x, color, cub3d);
// 			pos.x++;
// 		}
// 		pos.y++;
// 	}
// }

// void	draw_map(t_cub3d *cub3d)
// {
// 	t_vec2	drawcoords;
// 	t_vec2	poscoords;

// 	drawcoords = (t_vec2){.x = 0, .y = 0};
// 	poscoords = (t_vec2){.x = 0, .y = 0};
// 	poscoords.x = (int)cub3d->player.pos.x * MINIMAP_SCALE + 30;
// 	poscoords.y = (int)cub3d->player.pos.y * MINIMAP_SCALE + 30;
// 	while (cub3d->map.map[drawcoords.y])
// 	{
// 		drawcoords.x = 0;
// 		while (cub3d->map.map[drawcoords.x][drawcoords.y])
// 		{
// 			if (cub3d->map.map[drawcoords.x][drawcoords.y] == '1')
// 				draw_square(drawcoords, MINIMAP_SCALE, 0x000000, cub3d);
// 			drawcoords.x += MINIMAP_SCALE;
// 		}
// 		drawcoords.y += MINIMAP_SCALE;
// 	}
// 	draw_square(poscoords, MINIMAP_SCALE, 0xFFFF00, cub3d);
// }
