/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:04:55 by tbabou            #+#    #+#             */
/*   Updated: 2025/03/21 17:39:14 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	set_player_dir(char c)
{
	if (c == 'N')
		return (3 * PI / 2);
	else if (c == 'E')
		return (0);
	else if (c == 'S')
		return (PI / 2);
	else if (c == 'W')
		return (PI);
	return (0);
}

bool    init_player(char **map, t_player *player)
{
    int i;
    int j;

    i = 0;
    j = 0;
    empty_player(player);
    while (map[i])
    {
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'S')
            {
				player->dir = set_player_dir(map[i][j]);
                player->x = (((float)j + 1) * (BLOCK) + (BLOCK / 2));
                player->y = (((float)i + 1) * (BLOCK) + (BLOCK / 2));
                return (false);
            }
            j++;
        }
        i++;
        j = 0;
    }
    return (ft_dprintf(2, ERR_NO_PLAYER), true);
}
