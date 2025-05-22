/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:17:08 by tcali             #+#    #+#             */
/*   Updated: 2025/05/21 16:57:14 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*str_put_n_char(t_printf *list, int precision, char c)
{
	char	*str;

	if (precision <= 0)
		return (NULL);
	while (precision--)
		str = str_putformat(list, c);
	return (str);
}

void	ft_str_pickstr(t_printf *list)
{
	if (list->format.specifier == 's')
		str_putstr(list, list->format.str);
	else if (ft_present("pdiuxX", list->format.specifier))
		str_putstr(list, list->format.itoa);
	return ;
}

void	ft_fetch_str(t_printf *list, char *str)
{
	if (!str)
		str = "(null)";
	if (list->format.precision >= 0 && list->format.specifier != 's')
		ft_check_precision(list, str);
	else
	{
		if (list->format.specifier == 's')
			list->format.str = str;
	}
	if (list->format.width < 1)
	{
		ft_str_pickstr(list);
		return ;
	}
	if (list->format.left_justif)
	{
		ft_str_pickstr(list);
		str_put_n_char(list, ((list->format.width) - ft_strlen_int(str)), ' ');
	}
	else
		ft_check_zeropad(list);
}

void	nb_to_str(t_printf *list, char speci)
{
	ft_convert_nb(list, speci);
	if (list->format.itoa)
	{
		ft_check_width(list);
		ft_fetch_str(list, list->format.itoa);
		free(list->format.itoa);
	}
}

void	char_to_str(t_printf *list, int c, char pad)
{
	int		width;
	char	*tmp;

	width = list->format.width;
	if (width > 1)
	{
		if (list->format.left_justif)
		{
			update_list_dest(list, c);
			tmp = str_put_n_char(list, (width - 1), pad);
			list->dest = ft_strjoin_free(list->dest, tmp);
			free(tmp);
		}
		else if (list->format.zero_pad)
		{
			pad = '0';
			tmp = str_put_n_char(list, (width - 1), pad);
			list->dest = ft_strjoin_free(list->dest, tmp);
			free(tmp);
			update_list_dest(list, c);
		}
		return ;
	}
	update_list_dest(list, c);
}
