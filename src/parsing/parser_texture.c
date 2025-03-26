/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 21:53:49 by tbabou            #+#    #+#             */
/*   Updated: 2025/03/25 17:28:06 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	parse_textures_xpm(t_cub3d *cub3d, t_texture_struct *texture, int pos);

bool	init_textures(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub3d->map.texture[i].path)
		{
			if (parse_textures_xpm(cub3d, &cub3d->map.texture[i], i))
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
	{
		ft_dprintf(2, ERR_TEXTURE, path);
		return (true);
	}
	close(fd);
	return (false);
}

static bool parse_textures_xpm(t_cub3d *cub3d, t_texture_struct *texture, int pos)
{
	ft_printf("Parsing texture %i\n", texture->path);
	texture->width = 0;
	texture->height = 0;
    if (is_file_exist(texture->path))
        return (ft_printf("The file doesn't exist\n"), true);
    else
        ft_printf("The file exists\n");
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
    ft_printf("Texture %i loaded successfully!\n", pos);
    return (false);
}
