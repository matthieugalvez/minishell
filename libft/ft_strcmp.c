/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:53:02 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/10 15:31:12 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*cp1;
	unsigned char	*cp2;

	if (!s1 && !s2)
		return (-1);
	if (!s1 && s2)
		return (*s2);
	if (s1 && !s2)
		return (*s1);
	cp1 = (unsigned char *) s1;
	cp2 = (unsigned char *) s2;
	while (*cp1 && *cp2)
	{
		if (*cp1 != *cp2)
			return (*cp1 - *cp2);
		cp1++;
		cp2++;
	}
	return (*cp1 - *cp2);
}
