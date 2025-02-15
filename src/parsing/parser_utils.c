/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:34:24 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/14 17:36:27 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool is_finished(t_cub3d *cub3d)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (cub3d->map.textures[i] == NULL)
            return (false);
        i++;
    }
    if (cub3d->map.colors[FLOOR] == -1)
        return (false);
    if ( cub3d->map.colors[CEILING] == -1)
        return (false);
    return (true);
}
