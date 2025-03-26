/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:22:51 by tbabou            #+#    #+#             */
/*   Updated: 2025/03/25 17:31:56 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub3d *empty_cub3d(void)
{
    t_cub3d *cub3d;

    cub3d = ft_calloc(1, sizeof(t_cub3d));
    cub3d->mlx = NULL;
    cub3d->win = NULL;
    cub3d->img = NULL;
    cub3d->fd = -1;
    cub3d->map.map = NULL;
    cub3d->map.colors[0] = -1;
    cub3d->map.colors[1] = -1;
    cub3d->map.width = 0;
    cub3d->map.height = 0;
    return (cub3d);
}

bool init_minilibx(t_cub3d *cub3d)
{
    cub3d->mlx = mlx_init();
    if (!cub3d->mlx)
        return(ft_dprintf(2, ERR_MINILIBX), true);
    cub3d->win = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, "Cub3d");
    if (!cub3d->win)
        return(ft_dprintf(2, ERR_MINILIBX), true);
        
    cub3d->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
    if (!cub3d->img)
        return(ft_dprintf(2, ERR_MINILIBX), true);
        
    cub3d->data = mlx_get_data_addr(cub3d->img, &cub3d->bpp, &cub3d->size_line, &cub3d->endian);
    if (!cub3d->data)
        return(ft_dprintf(2, ERR_MINILIBX), true);
    return (false);
}
// TODO : Property handle leaks.
bool    init_cub3d(t_cub3d *cub3d, char *map_file)
{
    cub3d->fd = open(map_file, O_RDONLY);
    if (cub3d->fd < 0)
        return (ft_dprintf(2, "%s%s\n", ERR_MSG, strerror(errno)), true);
    if (init_minilibx(cub3d))
        return (close(cub3d->fd), true);
    if (init_parsing(cub3d))
        return (close(cub3d->fd), true);
    close(cub3d->fd);
    return (false);
}
