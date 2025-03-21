/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 21:53:49 by tbabou            #+#    #+#             */
/*   Updated: 2025/03/21 18:10:22 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parse_textures(t_cub3d *cub3d, t_texture_struct *texture, int pos);

bool	init_textures(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub3d->map.texture[i].path)
		{
			if (parse_textures(cub3d, &cub3d->map.texture[i], i))
				return (true);
		}
		else
		{
			ft_dprintf(2, ERR_TEXTURE, "NULL");
			return (true);
		}
		i++;
	}
	return (false);
}

bool	parse_textures(t_cub3d *cub3d, t_texture_struct *texture, int pos)
{
	ft_printf("attempt to loading texture %i\n", pos);
	ft_printf("path : %s\n", texture[pos].path);
	texture[pos].img = mlx_xpm_file_to_image(cub3d->mlx, texture[pos].path,
			&texture[pos].width, &texture[pos].height);
	if (!texture[pos].img)
	{
		ft_dprintf(2, ERR_TEXTURE, texture[pos].path);
		return (true);
	}
	texture[pos].data = mlx_get_data_addr(texture[pos].img, &texture[pos].bpp,
			&texture[pos].size_line, &texture[pos].endian);
	if (!texture[pos].data)
	{
		ft_dprintf(2, ERR_TEXTURE, texture[pos].path);
		return (true);
	}
	ft_printf("Texture %i loaded successfully!\n", pos);
	return (false);
}
