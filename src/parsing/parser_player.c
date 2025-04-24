/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:04:55 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/24 19:56:50 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (true);
	return (false);
}

static void	set_player_dir(t_player *player, char c)
{
	if (c == 'N')
		player->angle = 3 * PI / 2;
	else if (c == 'E')
		player->angle = 0;
	else if (c == 'S')
		player->angle = PI / 2;
	else if (c == 'W')
		player->angle = PI;
}

static void	set_player_pos(t_player *player, int x, int y)
{
	player->pos = (t_dvec2){(float)x + 0.5f, (float)y + 0.5f};
	player->spawn_pos = (t_vec2){x, y};
}

bool	init_player(char **map, t_player *player)
{
	t_vec2	player_pos;

	player_pos = (t_vec2){0, 0};
	empty_player(player);
	while (map[player_pos.y])
	{
		while (map[player_pos.y][player_pos.x])
		{
			if (is_valid_player(map[player_pos.y][player_pos.x]))
			{
				set_player_dir(player, map[player_pos.y][player_pos.x]);
				set_player_pos(player, player_pos.x, player_pos.y);
				return (false);
			}
			player_pos.x++;
		}
		player_pos.y++;
		player_pos.x = 0;
	}
	return (ft_dprintf(2, ERR_NO_PLAYER), true);
}
