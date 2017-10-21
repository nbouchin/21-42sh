/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:38:59 by zadrien           #+#    #+#             */
/*   Updated: 2017/06/04 15:07:14 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

char	*ft_strdup(const char *src)
{
	char	*dest;

	if (!src)
		return (NULL);
	dest = (char*)(malloc(sizeof(char) * (ft_strlen(src) + 1)));
	if (dest)
	{
		ft_strcpy(dest, src);
		return (dest);
	}
	return (NULL);
}
