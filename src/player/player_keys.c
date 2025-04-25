/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:44:44 by theaux            #+#    #+#             */
/*   Updated: 2025/04/25 19:29:31 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	manage_movement_key(int key, t_player *player, bool status)
{
	if (key == A)
		player->left = status;
	else if (key == D)
		player->right = status;
	else if (key == W)
		player->up = status;
	else if (key == S)
		player->down = status;
	else if (key == SHIFT)
		player->sprint = status;
}

void	manage_camera_key(int key, t_player *player, bool status)
{
	if (key == UP)
		player->look_up = status;
	else if (key == DOWN)
		player->look_down = status;
	else if (key == LEFT)
		player->rotate_left = status;
	else if (key == RIGHT)
		player->rotate_right = status;
}

int	on_key_press(int key, t_cub3d *cub3d)
{
	manage_movement_key(key, &cub3d->player, true);
	manage_camera_key(key, &cub3d->player, true);
	if (key == ESCAPE)
		(free_cub3d(cub3d), exit(0));
	else if (key == E)
		cub3d->player.interact = true;
	return (0);
}

int	on_key_release(int key, t_player *player)
{
	manage_movement_key(key, player, false);
	manage_camera_key(key, player, false);
	return (0);
}