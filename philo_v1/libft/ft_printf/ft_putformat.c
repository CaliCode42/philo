/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putformat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:39:56 by tcali             #+#    #+#             */
/*   Updated: 2025/05/21 15:24:48 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <unistd.h> 

void	ft_putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
}

void	ft_putformat(t_printf *list, char c)
{
	ft_putchar_fd(list->fd, c);
	list->nb_chars++;
}

char	*str_putchar(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*str_putformat(t_printf *list, char c)
{
	char	*str;

	str = str_putchar(c);
	list->nb_chars++;
	return (str);
}
