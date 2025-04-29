/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 00:30:54 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/29 11:26:30 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map_struct(t_map_line *map)
{
	t_map_line	*current;
	t_map_line	*next;

	current = map;
	while (current != NULL)
	{
		next = current->next;
		free(current->line);
		free(current);
		current = next;
	}
}

void	destroy_mlx(t_cub3d *cub3d)
{
	if (cub3d->img)
	{
		mlx_destroy_image(cub3d->mlx, cub3d->img);
		cub3d->img = NULL;
	}
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
}

void	free_cub3d(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	if (!cub3d)
		return ;
	while (i < 7)
	{
		if (cub3d->map.texture[i].img)
			mlx_destroy_image(cub3d->mlx, cub3d->map.texture[i].img);
		if (cub3d->map.texture[i].path)
			free(cub3d->map.texture[i].path);
		i++;
	}
	ft_freesplit(cub3d->map.map);
	destroy_mlx(cub3d);
	free(cub3d->ray);
	free(cub3d);
}
