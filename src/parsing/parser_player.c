/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:04:55 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/15 15:32:19 by tbabou           ###   ########.fr       */
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

bool    init_player(t_cub3d *cub3d)
{
    int i;
    int j;

    i = 0;
    j = 0;
    empty_player(&cub3d->player);
    while (cub3d->map.map[i])
    {
        while (cub3d->map.map[i][j])
        {
            if (cub3d->map.map[i][j] == 'N')
            {
                cub3d->player.x = (double)j;
                cub3d->player.y = (double)i;
                ft_printf("X = %i, Y = %i", i, j);
                printf("Player has been found at : x=%f -y= %f", cub3d->player.x, cub3d->player.y);
                return (false);
            }
            j++;
        }
        i++;
        j = 0;
    }
    return (ft_dprintf(2, ERR_NO_PLAYER), true);
}
