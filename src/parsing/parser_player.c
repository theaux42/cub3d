/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:04:55 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/15 19:13:31 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// typedef struct  s_player
// {
//     double      x;
//     double      y;
//     double      dir;
//     double      fov;
// }               t_player;

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
            if (map[i][j] == 'N')
            {
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
