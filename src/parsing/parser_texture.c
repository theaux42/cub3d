/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 21:53:49 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/25 15:28:01 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	parse_textures_xpm(t_cub3d *cub3d, t_texture_struct *texture);

bool	init_textures(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (cub3d->map.texture[i].path)
		{
			if (parse_textures_xpm(cub3d, &cub3d->map.texture[i]))
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

bool	is_file_exist(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (true);
	close(fd);
	return (false);
}

static bool	parse_textures_xpm(t_cub3d *cub3d, t_texture_struct *texture)
{
	texture->width = 0;
	texture->height = 0;
	if (is_file_exist(texture->path))
		return (ft_printf(ERR_FILE_DOESNT_EXIST, texture->path), true);
	if (ft_strncmp(texture->path + ft_strlen(texture->path) - 4, ".xpm", 4))
		return (ft_printf(ERR_NO_FTYPE, ".xpm"), true);
	texture->img = mlx_xpm_file_to_image(cub3d->mlx, texture->path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		ft_dprintf(2, ERR_TEXTURE, texture->path);
		return (true);
	}
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
	if (!texture->data)
	{
		ft_dprintf(2, ERR_TEXTURE, texture->path);
		return (true);
	}
	return (false);
}
