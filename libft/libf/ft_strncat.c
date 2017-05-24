/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:00:56 by khabbar           #+#    #+#             */
/*   Updated: 2017/02/20 14:11:00 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*str;

	str = s1;
	while (*s1)
		s1++;
	while (n > 0 && *s2)
	{
		*s1++ = *s2++;
		n--;
	}
	*s1 = '\0';
	return (str);
}
