/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:31:11 by tcali             #+#    #+#             */
/*   Updated: 2025/05/21 16:52:06 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/ft_printf.h"

static int	ft_init_printf(t_printf *list, const char *format, int fd, int str)
{
	list->nb_chars = 0;
	list->str = format;
	list->fd = fd;
	if (str == 1)
	{
		list->dest = malloc(sizeof(char) * 1);
		if (!list->dest)
			return (0);
		list->dest[0] = '\0';
	}
	return (1);
}

int	ft_printf(const char *format, ...)
{
	t_printf	list;

	va_start(list.ap, format);
	if (!ft_init_printf(&list, format, 1, 0))
		return (-1);
	while (*list.str)
	{
		if (*list.str == '%' && list.str[1])
		{
			++list.str;
			if (ft_parse_format(&list) <= 0)
				return (0);
			ft_render_format(&list);
		}
		else
		{
			ft_putformat(&list, *list.str);
		}
		++list.str;
	}
	va_end(list.ap);
	return (list.nb_chars);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	t_printf	list;

	va_start(list.ap, format);
	if (!ft_init_printf(&list, format, fd, 0))
		return (-1);
	while (*list.str)
	{
		if (*list.str == '%' && list.str[1])
		{
			++list.str;
			if (ft_parse_format(&list) <= 0)
				return (0);
			ft_render_format(&list);
		}
		else
		{
			ft_putformat(&list, *list.str);
		}
		++list.str;
	}
	va_end(list.ap);
	return (list.nb_chars);
}

void	update_list_dest(t_printf *list, char c)
{
	char	*tmp;

	tmp = str_putformat(list, c);
	if (!tmp)
	{
		free(list->dest);
		return ;
	}
	list->dest = ft_strjoin_free(list->dest, tmp);
	free(tmp);
}

int	ft_sprintf(char **str, const char *format, ...)
{
	t_printf	list;

	va_start(list.ap, format);
	if (!ft_init_printf(&list, format, 1, 1))
		return (-1);
	while (*list.str)
	{
		if (*list.str == '%' && list.str[1])
		{
			++list.str;
			if (ft_parse_format(&list) <= 0)
				return (free(list.dest), 0);
			str_render_format(&list);
		}
		else
		{
			update_list_dest(&list, *list.str);
		}
		++list.str;
	}
	*str = ft_strdup(list.dest);
	if (list.dest)
		free(list.dest);
	va_end(list.ap);
	return (list.nb_chars);
}
