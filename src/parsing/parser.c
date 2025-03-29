/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:02:50 by tbabou            #+#    #+#             */
/*   Updated: 2025/03/29 15:02:50 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_settings(t_cub3d *cub3d)
{
	ft_printf("Texture : \n");
	ft_printf("Color : \n");
	ft_printf("    Floor Color: %X \n", cub3d->map.colors[FLOOR]);
	ft_printf("    Ceiling Color: %X \n", cub3d->map.colors[CEILING]);
}

bool	init_parsing(t_cub3d *cub3d)
{
	if (parse_settings(cub3d))
		return (true);
    if (!is_finished(cub3d))
    {
        return (ft_dprintf(2, "Error happened\n"), true);
    }
	print_settings(cub3d);
	if (parse_map(cub3d))
		return (true);
	if (init_player(cub3d->map.map, &cub3d->player))
		return (true);
	if (init_textures(cub3d))
		return (true);
	return (false);
}
