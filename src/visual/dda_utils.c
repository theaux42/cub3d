/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 03:38:47 by theaux            #+#    #+#             */
/*   Updated: 2025/04/27 03:39:02 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_touching_wall(float origin_x, float origin_y, char **map,
		bool is_crosshair)
{
	int	x;
	int	y;

	x = (int)origin_x;
	y = (int)origin_y;
	if (x < 0 || y < 0)
		return (true);
	if (is_crosshair && map[y][x] == 'd')
		return (true);
	if (map[y][x] == '1' || map[y][x] == 'D')
		return (true);
	return (false);
}
