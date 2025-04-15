/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:16:43 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/11 20:41:54 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_pixel_from_tex(int x, int y, t_texture_struct tex,
		t_hit hit)
{
	unsigned int	*img;
	unsigned int	color;
	double			shade_factor;
	t_rgb			rgb;

	if (x >= tex.width || y >= tex.height || x < 0 || y < 0)
		return (0x000000);
	img = (unsigned int *)tex.data;
	color = img[y * tex.width + x];
	shade_factor = 1.0 - fmin(0.7, hit.dist / 14.0);
	shade_factor = fmax(0.2, shade_factor);
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

void	put_pixel(int x, int y, int color, t_cub3d *cub3d)
{
	unsigned int	*img;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	img = (unsigned int *)cub3d->data;
	img[y * WIDTH + x] = color;
}

void	draw_square(int x, int y, int size, int color, t_cub3d *cub3d)
{
	t_vec2	pos;

	pos = (t_vec2){0, 0};
	while (pos.y < size)
	{
		pos.x = 0;
		while (pos.x < size)
		{
			put_pixel(x + pos.y, y + pos.x, color, cub3d);
			pos.x++;
		}
		pos.y++;
	}
}

void	draw_map(t_cub3d *cub3d)
{
	t_vec2	drawcoord;
	t_vec2	playercoord;

	drawcoord = (t_vec2){.x = 0, .y = 0};
	playercoord = (t_vec2){.x = 0, .y = 0};
	playercoord.x = (int)cub3d->player.pos.x * MINIMAP_SCALE + 30;
	playercoord.y = (int)cub3d->player.pos.y * MINIMAP_SCALE + 30;
	while (cub3d->map.map[drawcoord.y])
	{
		drawcoord.x = 0;
		while (cub3d->map.map[drawcoord.x][drawcoord.y])
		{
			if (cub3d->map.map[drawcoord.x][drawcoord.y] == '1')
				draw_square(drawcoord.x, drawcoord.y, MINIMAP_SCALE, 0x000000,
					cub3d);
			drawcoord.x += MINIMAP_SCALE;
		}
		drawcoord.y += MINIMAP_SCALE;
	}
	draw_square(playercoord.x, playercoord.y, MINIMAP_SCALE, 0xFFFF00, cub3d);
}
