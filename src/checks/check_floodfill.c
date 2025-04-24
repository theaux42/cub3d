/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_floodfill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:57:38 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/24 17:19:51 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	floodfill(t_cub3d *cub3d, bool **filled_map, int i, int j)
{
	bool	is_closed;

	if (i < 0 || i >= cub3d->map.height || j < 0
		|| j >= (int)ft_strlen(cub3d->map.map[i]))
		return (false);
	if (cub3d->map.map[i][j] == '1' || filled_map[i][j] == true)
		return (true);
	else
		filled_map[i][j] = true;
	is_closed = true;
	is_closed &= floodfill(cub3d, filled_map, i - 1, j);
	is_closed &= floodfill(cub3d, filled_map, i + 1, j);
	is_closed &= floodfill(cub3d, filled_map, i, j - 1);
	is_closed &= floodfill(cub3d, filled_map, i, j + 1);
	return (is_closed);
}

static void	free_ptrarr(void **ptrarr)
{
	int	i;

	i = 0;
	while (ptrarr[i])
	{
		free(ptrarr[i]);
		i++;
	}
	free(ptrarr);
}

bool	is_map_closed(t_cub3d *cub3d)
{
	int		x;
	int		y;
	int		i;
	bool	**filled_map;
	bool	is_closed;

	x = cub3d->player.spawn_pos.x;
	y = cub3d->player.spawn_pos.y;
	filled_map = ft_calloc(cub3d->map.height + 1, sizeof(bool *));
	i = 0;
	while (i < cub3d->map.height)
	{
		filled_map[i] = ft_calloc(ft_strlen(cub3d->map.map[i]), sizeof(bool));
		if (!filled_map[i])
		{
			free_ptrarr((void **)filled_map);
			return (ft_dprintf(2, ERR_MALLOC), true);
		}
		i++;
	}
	is_closed = floodfill(cub3d, filled_map, y, x);
	free_ptrarr((void **)filled_map);
	if (!is_closed)
		return (ft_dprintf(2, ERR_MAP_BORDER), true);
	return (false);
}
