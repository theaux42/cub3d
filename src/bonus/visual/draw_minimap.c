/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:14:53 by theaux            #+#    #+#             */
/*   Updated: 2025/05/01 18:59:03 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_wall_square(t_cub3d *cub3d, t_vec2 pos, int color)
{
	draw_square(cub3d, (t_vec2){MINIMAP_OFFSET_X + pos.x * MINIMAP_SCALE,
		MINIMAP_OFFSET_Y + pos.y * MINIMAP_SCALE}, MINIMAP_SCALE, color);
}

void	draw_minimap(t_cub3d *cub3d)
{
	t_vec2	pos;
	t_map	*map;

	map = &cub3d->map;
	pos = (t_vec2){0, 0};
	while (map->map[pos.y])
	{
		while (map->map[pos.y][pos.x])
		{
			if (map->map[pos.y][pos.x] == '1')
				draw_wall_square(cub3d, pos, 0xFFFFFF);
			else if (map->map[pos.y][pos.x] == 'D')
				draw_wall_square(cub3d, pos, 0x00FF00);
			else if (map->map[pos.y][pos.x] == 'd')
				draw_wall_square(cub3d, pos, 0xFF0000);
			pos.x++;
		}
		pos.x = 0;
		pos.y++;
	}
	draw_square(cub3d, (t_vec2){MINIMAP_OFFSET_X + cub3d->player.pos.x
		* MINIMAP_SCALE, MINIMAP_OFFSET_Y + cub3d->player.pos.y
		* MINIMAP_SCALE}, MINIMAP_PLAYER_SIZE, 0x0000FF);
}
