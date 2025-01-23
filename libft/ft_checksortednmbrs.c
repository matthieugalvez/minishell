/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checksortednmbrs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:58:32 by mgalvez           #+#    #+#             */
/*   Updated: 2024/12/11 11:59:22 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_checksortednmbrs(int *tab, int depht)
{
	int	i;
	int	j;

	i = 0;
	while (i < depht)
	{
		j = i + 1;
		while (j < depht)
		{
			if (tab[i] > tab[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
