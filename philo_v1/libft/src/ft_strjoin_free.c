/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:44:08 by tcali             #+#    #+#             */
/*   Updated: 2025/05/21 16:03:52 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:49:59 by tcali             #+#    #+#             */
/*   Updated: 2025/03/25 23:39:07 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		s1_len;
	int		s2_len;
	char	*joined;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined = malloc (sizeof(char) * (s1_len + s2_len + 1));
	if (!joined)
		return (NULL);
	while (i < s1_len)
	{
		joined[i] = s1[i];
		i++;
	}
	while (i - s1_len < s2_len)
	{
		joined[i] = s2[i - s1_len];
		i++;
	}
	joined[i] = '\0';
	free (s1);
	return (joined);
}
