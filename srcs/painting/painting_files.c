/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:47:58 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/03/13 20:44:48 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

/*
	Conver file to mlx image.

	May return NULL
*/
t_image	*paint_get_image(t_painting *painting, char *file_name)
{
	t_image	*image;

	if (!painting || !file_name)
		return (NULL);
	image = (t_image *)malloc(sizeof(t_image));
	if (!image)
		return (NULL);
	image->drawable.img = mlx_xpm_file_to_image(painting->mlx, file_name,
			&image->w, &image->h);
	if (!image->drawable.img)
	{
		free(image);
		return (NULL);
	}
	image->drawable.img_addr = mlx_get_data_addr(image->drawable.img,
			&image->drawable.bits_per_pixel,
			&image->drawable.size_line, &image->drawable.endian);
	return (image);
}
