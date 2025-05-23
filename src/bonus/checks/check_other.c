/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 05:18:25 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/30 10:32:33 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_playerchr(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	check_map_chars(t_map map)
{
	t_vec2	pos;
	bool	end_of_map;

	end_of_map = false;
	pos = (t_vec2){0, 0};
	while (pos.y < map.height - 1)
	{
		pos.x = 0;
		if (map.map[pos.y][pos.x] == '\0' && !end_of_map)
			end_of_map = true;
		if (map.map[pos.y][pos.x] != '\0' && end_of_map)
			return (ft_printf(ERR_WEIRD_MAP), true);
		pos.y++;
	}
	return (false);
}

bool	check_map_unkn_char(t_map map)
{
	t_vec2	pos;

	pos = (t_vec2){0, 0};
	while (pos.y < map.height - 1)
	{
		while ((map.map[pos.y][pos.x]) && ft_isspace(map.map[pos.y][pos.x]))
			pos.x++;
		while (map.map[pos.y][pos.x])
		{
			if (!ft_strchr(VALID_CHARS, map.map[pos.y][pos.x]))
				return (ft_printf(ERR_UNKN_CHAR, map.map[pos.y][pos.x]), true);
			pos.x++;
		}
		pos.x = 0;
		pos.y++;
	}
	return (false);
}

bool	check_player_amount(t_map map)
{
	t_vec2	pos;
	int		player_count;

	player_count = 0;
	pos = (t_vec2){0, 0};
	while (pos.y < map.height)
	{
		while (pos.x < (int)ft_strlen(map.map[pos.y]))
		{
			if (is_playerchr(map.map[pos.y][pos.x]))
				player_count++;
			pos.x++;
		}
		pos.x = 0;
		pos.y++;
	}
	if (player_count <= 0)
		return (ft_printf(ERR_NO_PLAYER), true);
	if (player_count > 1)
		return (ft_printf(ERR_TOO_PLAYER, player_count), true);
	return (false);
}
