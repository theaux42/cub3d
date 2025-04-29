/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 01:50:06 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/29 17:20:36 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MOUSE_SENSITIVITY 0.003

int	on_mouse_move(int x, int y, t_cub3d *cub3d)
{
	static t_vec2	last = {-1, -1};
	t_vec2			delta;

	if (last.x == -1 && last.y == -1)
	{
		last = (t_vec2){x, y};
		return (0);
	}
	delta.x = x - last.x;
	delta.y = y - last.y;
	last = (t_vec2){x, y};
	cub3d->player.angle += delta.x * MOUSE_SENSITIVITY;
	cub3d->player.pitch -= delta.y * MOUSE_SENSITIVITY * 300;
	if (cub3d->player.angle < 0)
		cub3d->player.angle += 2 * PI;
	if (cub3d->player.angle > 2 * PI)
		cub3d->player.angle -= 2 * PI;
	if (cub3d->player.pitch < -HEIGHT / 2)
		cub3d->player.pitch = -HEIGHT / 2;
	if (cub3d->player.pitch > HEIGHT / 2)
		cub3d->player.pitch = HEIGHT / 2;
	return (0);
}

void	draw_fps_counter(t_cub3d *cub3d)
{
	static struct timeval	last_time = {0};
	static int				frame_count = 0;
	static double			fps = 0.0;
	struct timeval			current_time;
	double					elapsed;
	char					display[32];

	gettimeofday(&current_time, NULL);
	if (last_time.tv_sec == 0)
		last_time = current_time;
	elapsed = (current_time.tv_sec - last_time.tv_sec) + ((current_time.tv_usec
				- last_time.tv_usec) / 1000000.0);
	frame_count++;
	if (elapsed >= 1.0)
	{
		fps = frame_count / elapsed;
		last_time = current_time;
		frame_count = 0;
	}
	snprintf(display, sizeof(display), "FPS: %i", (int)fps);
	mlx_string_put(cub3d->mlx, cub3d->win, 10, 10, 0x00FFFFFF, display);
}

int	render(t_cub3d *cub3d)
{
	raycast(cub3d);
	player_key_handler(&cub3d->player, cub3d->map.map);
	player_crosshair(cub3d);
	draw_minimap(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img, 0, 0);
	draw_fps_counter(cub3d);
	return (0);
}

int	exit_game(t_cub3d *cub3d)
{
	free_cub3d(cub3d);
	exit(0);
}

int	main(int ac, char **av)
{
	t_cub3d	*cub3d;

	if (ac != 2)
		return (ft_dprintf(2, ERR_NO_ARG, av[0]), 1);
	cub3d = empty_cub3d();
	if (!cub3d)
		return (1);
	if (init_cub3d(cub3d, av[1]))
		return (free_cub3d(cub3d), 1);
	mlx_hook(cub3d->win, 17, 1L << 17, exit_game, cub3d);
	mlx_hook(cub3d->win, 2, 1L << 0, on_key_press, cub3d);
	mlx_hook(cub3d->win, 3, 1L << 1, on_key_release, &cub3d->player);
	mlx_hook(cub3d->win, 6, 1L << 6, on_mouse_move, cub3d);
	mlx_loop_hook(cub3d->mlx, render, cub3d);
	mlx_loop(cub3d->mlx);
	free_cub3d(cub3d);
	return (0);
}
