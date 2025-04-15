/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_floodfill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:57:38 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/12 18:03:10 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	skip_whitespace(char *str, int *pos)
{
	char	current;

	current = '\0';
	while (ft_isspace(str[*pos]))
	{
		current = str[*pos];
		(*pos)++;
		ft_printf(" ");
		if (current == '0' && ft_isspace(str[*pos]))
			return (true);
	}
	return (false);
}

static bool	is_valid_access(t_map map, t_vec2 pos)
{
	if (pos.y < 0 || pos.y >= map.height)
		return (false);
	if (pos.x < 0 || pos.x >= (int)ft_strlen(map.map[pos.y]))
		return (false);
	if (map.map[pos.y][pos.x] == '\0')
		return (false);
	return (true);
}

static bool	perform_flood_fill(t_map map, bool **checked, t_vec2 pos)
{
	if (!is_valid_access(map, pos))
		return (false);
	if (map.map[pos.y][pos.x] == ' ')
		return (false);
	if (map.map[pos.y][pos.x] == '1' || checked[pos.y][pos.x])
		return (true);
	checked[pos.y][pos.x] = true;
	return (perform_flood_fill(map, checked, (t_vec2){pos.x + 1, pos.y})
		&& perform_flood_fill(map, checked, (t_vec2){pos.x - 1, pos.y})
		&& perform_flood_fill(map, checked, (t_vec2){pos.x, pos.y + 1})
		&& perform_flood_fill(map, checked, (t_vec2){pos.x, pos.y - 1}));
}

static bool	init_checked(bool ***checked, t_map map)
{
	int	i;

	i = 0;
	*checked = ft_calloc(map.height, sizeof(bool *));
	if (!*checked)
		return (true);
	while (i < map.height)
	{
		(*checked)[i] = ft_calloc(ft_strlen(map.map[i]), sizeof(bool));
		if (!(*checked)[i])
		{
			while (i <= 0)
				free((*checked)[i--]);
			return (free(*checked), true);
		}
		i++;
	}
	return (false);
}

static void	free_checked(bool **checked, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(checked[i]);
		i++;
	}
	free(checked);
	ft_printf("\n-------------\n");
}

bool	is_map_closed(t_cub3d *cub3d)
{
	bool	**checked;
	t_vec2	pos;

	pos = (t_vec2){0, 0};
	if (init_checked(&checked, cub3d->map))
		return (ft_printf(ERR_MALLOC), true);
	while (cub3d->map.map[pos.y] && pos.y < cub3d->map.height)
	{
		pos.x = 0;
		skip_whitespace(cub3d->map.map[pos.y], &pos.x);
		while (cub3d->map.map[pos.y][pos.x])
		{
			ft_printf("%c",cub3d->map.map[pos.y][pos.x]);
			if (ft_strchr(VALID_CHARS, cub3d->map.map[pos.y][pos.x])
				&& !checked[pos.y][pos.x])
				if (!perform_flood_fill(cub3d->map, checked, pos))
					return ((free_checked(checked, cub3d->map.height),
							ft_printf(DBG_MAP_BORDER, pos.x, pos.y)), true);
			pos.x++;
		}
		pos.y++;
	}
	return (free_checked(checked, cub3d->map.height), false);
}
