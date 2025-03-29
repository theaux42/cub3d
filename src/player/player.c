/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:05:40 by tbabou            #+#    #+#             */
/*   Updated: 2025/03/29 15:17:14 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	empty_player(t_player *player)
{
	player->pos.x = 0.0;
	player->pos.y = 0.0;
	player->angle = PI / 2;
	player->fov = 1.0;
	player->speed = PLAYER_SPEED;
	player->left = false;
	player->right = false;
	player->up = false;
	player->down = false;
	player->sprint = false;
	player->rotate_left = false;
	player->rotate_right = false;
	player->plane.x = 0.0;
	player->plane.y = 0.66;
}

int	on_key_press(int key, t_cub3d *cub3d)
{
	if (key == A)
		cub3d->player.left = true;
	else if (key == D)
		cub3d->player.right = true;
	else if (key == W)
		cub3d->player.up = true;
	else if (key == S)
		cub3d->player.down = true;
	else if (key == SHIFT)
		cub3d->player.sprint = true;
	else if (key == LEFT)
		cub3d->player.rotate_left = true;
	else if (key == RIGHT)
		cub3d->player.rotate_right = true;
	else if (key == MINUS && cub3d->player.fov > 0.5)
		cub3d->player.fov -= 0.1;
	else if (key == PLUS && cub3d->player.fov < 2.0)
		cub3d->player.fov += 0.1;
	else if (key == ESCAPE)
		(free_cub3d(cub3d), exit(0));
	return (0);
}

int	on_key_release(int key, t_player *player)
{
	if (key == A)
		player->left = false;
	else if (key == D)
		player->right = false;
	else if (key == W)
		player->up = false;
	else if (key == S)
		player->down = false;
	else if (key == SHIFT)
		player->sprint = false;
	else if (key == LEFT)
		player->rotate_left = false;
	else if (key == RIGHT)
		player->rotate_right = false;
	return (0);
}

void	update_camera_plane(t_player *player)
{
	player->plane.x = sin(player->angle) * player->fov;
	player->plane.y = -cos(player->angle) * player->fov;
}

void	player_key_handler(t_player *player, char **map)
{
	float	current_speed;

	current_speed = player->speed;
	if (player->rotate_left)
		player->angle -= CAMERA_SPEED;
	if (player->rotate_right)
		player->angle += CAMERA_SPEED;
	player->angle = fmod(player->angle, 2 * PI);
	if (player->angle < 0)
		player->angle += 2 * PI;
	if (player->sprint)
		current_speed *= 1.5;
	else
		current_speed = PLAYER_SPEED / 2;
	update_camera_plane(player);
	move_player(player->angle, current_speed, player, map);
}
