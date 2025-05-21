/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_putstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:00:25 by tcali             #+#    #+#             */
/*   Updated: 2025/05/21 16:57:12 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "../includes/ft_printf.h"
#include "../includes/libft.h"

void	str_check_prefix(t_printf *list)
{
	if (ft_present("cs", list->format.specifier)
		|| list->format.prefix_checked)
		return ;
	if (list->format.is_negative)
		list->dest = ft_strjoin(list->dest, str_putformat(list, '-'));
	else if (list->format.hash)
	{
		if (list->format.uppercase)
		{
			list->dest = ft_strjoin(list->dest, str_putformat(list, '0'));
			list->dest = ft_strjoin(list->dest, str_putformat(list, 'X'));
		}
		else if (list->format.lowercase)
		{
			list->dest = ft_strjoin(list->dest, str_putformat(list, '0'));
			list->dest = ft_strjoin(list->dest, str_putformat(list, 'x'));
		}
	}
	else if (list->format.space && !list->format.is_negative)
		list->dest = ft_strjoin(list->dest, str_putformat(list, ' '));
	else if (list->format.plus && !list->format.is_negative)
		list->dest = ft_strjoin(list->dest, str_putformat(list, '+'));
	list->format.prefix_checked = 1;
}

static void	str_handle_precision_str(t_printf *list, char *str)
{
	int	i;

	i = 0;
	if (list->format.precision == 0)
	{
		list->dest = ft_strjoin(list->dest, str_putchar('\0'));
		return ;
	}
	else
	{
		while (i < list->format.precision)
		{
			list->dest = ft_strjoin(list->dest, str_putformat(list, str[i]));
			i++;
		}
	}
}

void	str_putstr(t_printf *list, char *str)
{
	int	precision;

	precision = list->format.precision;
	if (!str)
		return ;
	str_check_prefix(list);
	if (list->format.specifier == 's'
		&& precision >= 0 && precision < ft_strlen_int(str))
	{
		str_handle_precision_str(list, str);
	}
	else
		list->dest = ft_strjoin_free(list->dest, str);
}
