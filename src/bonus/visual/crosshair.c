/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:25:01 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/25 19:57:50 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_crosshair_color(t_hit hit)
{
	if (hit.type == 'D')
		return (get_trgb(0, 0, 255, 0));
	if (hit.type == 'd')
		return (get_trgb(0, 255, 0, 0));
	return (get_trgb(0, 255, 255, 255));
}

void	draw_crosshair(t_cub3d *cub3d, t_ray *ray)
{
	t_vec2	coords;
	int		diff;
	int		color;

	coords = (t_vec2){WIDTH / 2, HEIGHT / 2};
	diff = CROSSHAIR_SIZE;
	color = get_crosshair_color(ray->hit);
	while (diff-- > 3)
	{
		put_pixel((t_vec2){coords.x + diff, coords.y}, color, cub3d);
		put_pixel((t_vec2){coords.x, coords.y - diff}, color, cub3d);
	}
	while (diff++ < CROSSHAIR_SIZE - 1)
	{
		put_pixel((t_vec2){coords.x + diff, coords.y}, color, cub3d);
		put_pixel((t_vec2){coords.x, coords.y + diff}, color, cub3d);
	}
}
