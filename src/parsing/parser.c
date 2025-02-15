/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 23:04:14 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/07 23:04:14 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void print_settings(t_cub3d *cub3d)
{
    ft_printf("Texture : \n");
    for (int i = 0; i < 4; i++)
        ft_printf("    Texture path %i : %s", i, cub3d->map.textures[i]);
    ft_printf("Color : \n");
    ft_printf("    Floor Color: %X \n",cub3d->map.colors[FLOOR]);
    ft_printf("    Ceiling Color: %X \n",cub3d->map.colors[CEILING]);
}

bool    init_parsing(t_cub3d *cub3d)
{
    if (parse_settings(cub3d))
        return (true);
    print_settings(cub3d);
    if (parse_map(cub3d))
        return (true);
    if (init_player(cub3d))
        return (true);
    return (false);
}