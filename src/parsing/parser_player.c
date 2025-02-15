/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:04:55 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/15 18:43:33 by theaux           ###   ########.fr       */
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
                player->x = (double)j;
                player->y = (double)i;
                ft_printf("X = %i, Y = %i", i, j);
                printf("Player has been found at : x=%f -y= %f", player->x, player->y);
                return (false);
            }
            j++;
        }
        i++;
        j = 0;
    }
    return (ft_dprintf(2, ERR_NO_PLAYER), true);
}
