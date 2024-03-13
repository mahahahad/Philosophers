/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:28:56 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/13 11:35:23 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	i = 0;
	if (!s)
		return (NULL);
	if ((size_t) start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (i != len)
		substr[i++] = s[start++];
	substr[len] = '\0';
	return (substr);
}

static int	count_words(const char *s, const char c)
{
	int	words;
	int	word_found;
	int	i;

	words = 0;
	word_found = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] != c && !word_found)
		{
			word_found = 1;
			words++;
		}
		if (s[i] == c)
			word_found = 0;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	int			word_start_index;
	size_t		i;
	int			j;
	char		**strings;

	if (!s)
		return (NULL);
	strings = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!strings)
		return (NULL);
	word_start_index = -1;
	i = -1;
	j = 0;
	while (++i != ft_strlen(s) + 1)
	{
		if ((s[i] == c || i == ft_strlen(s)) && word_start_index >= 0)
		{
			strings[j++] = ft_substr(s, word_start_index, i - word_start_index);
			word_start_index = -1;
		}
		if (s[i] != c && word_start_index < 0)
			word_start_index = i;
	}
	strings[j] = NULL;
	return (strings);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*final_str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	final_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!final_str)
		return (NULL);
	while (s1[++i])
		final_str[i] = s1[i];
	while (s2[j])
		final_str[i++] = s2[j++];
	final_str[i] = '\0';
	return (final_str);
}
