/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:50:45 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/21 16:50:15 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	int	i;
	int	words;

	i = 1;
	words = 0;
	if (!str[0])
		return (words);
	while (str[i])
	{
		if ((str[i] == c || str[i] == '\0') && str[i - 1] != c)
			words++;
		i++;
	}
	if ((str[i] == '\0') && str[i - 1] != c)
		words++;
	return (words);
}

static int	word_len(const char *str, int index, char set)
{
	int	i;
	int	j;

	i = index;
	j = 0;
	while (str[i] == set && str[i])
		i++;
	while ((str[i] != set && str[i] != '\0'))
	{
		j++;
		i++;
	}
	return (j);
}

static char	*ft_strdup_n(const char *src, int n, int index)
{
	char	*dup;
	int		i;
	int		j;

	i = index;
	j = 0;
	dup = malloc((n + 1) * sizeof(char));
	if (!dup)
		return (0);
	while (src[i] && j < n)
	{
		dup[j] = src[i];
		i++;
		j++;
	}
	dup[j] = 0;
	return (dup);
}

static int	skip_c(const char *s, char c, int i)
{
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		i_tab;
	int		nb_words;
	char	**tab;

	if (!s)
		return (0);
	i = 0;
	i_tab = 0;
	nb_words = count_words(s, c);
	tab = malloc((nb_words + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (nb_words-- > 0)
	{
		i = skip_c(s, c, i);
		tab[i_tab] = ft_strdup_n(s, word_len(s, i, c), i);
		if (tab[i_tab] == NULL)
			free_tab(tab);
		i_tab++;
		while (s[i] && (s[i] != c))
			i++;
	}
	tab[i_tab] = NULL;
	return (tab);
}

// int	main(void)
// {
// 	// int	i = 0;
// 	char **tab = ft_split("  un    deux    trois         ", ' ');

// 	// while (i < 2)
// 	// {
// 	printf("%s\n", tab[0]);
// 	printf("%s\n", tab[1]);
// 	printf("%s\n", tab[2]);
// 	// printf("%s\n", tab[3]);
// 	// 	i++;
// 	// }
// }
