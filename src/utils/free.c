/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 00:30:54 by tbabou            #+#    #+#             */
/*   Updated: 2025/03/21 17:55:28 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_map_struct(t_map_line *map)
{
    t_map_line *current = map;
    t_map_line *next;

    while (current != NULL)
    {
        next = current->next;
        free(current->line);
        free(current);
        current = next;
    }
}


void free_cub3d(t_cub3d *cub3d)
{
    int i;

    i = 0;
    if (!cub3d)
        return;
    while (i < 4)
    {
        if (cub3d->map.texture[i].path)
            free(cub3d->map.texture[i].path);
        i++;
    }
    ft_freesplit(cub3d->map.map);
    if (cub3d->win)
    {
        mlx_destroy_window(cub3d->mlx, cub3d->win);
        cub3d->win = NULL;
    }
    if (cub3d->mlx)
    {
        mlx_destroy_display(cub3d->mlx);
        free(cub3d->mlx);
        cub3d->mlx = NULL;
    }
    free(cub3d);
}

