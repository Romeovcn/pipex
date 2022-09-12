/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:50:34 by rvincent          #+#    #+#             */
/*   Updated: 2022/09/11 15:18:22 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_array_size(char const *str, char charset)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && *str == charset)
			str++;
		if (*str != charset && *str)
			count++;
		while (*str != charset && *str)
			str++;
	}
	return (count);
}

static char	*get_next_word(char const *str, char charset)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && str[i] != charset)
		i++;
	word = malloc((i + 1) * sizeof(char));
	if (word == NULL)
		return (0);
	i = 0;
	while (str[i] && str[i] != charset)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		count;
	char	**result;

	i = 0;
	count = get_array_size(s, c);
	result = malloc((count + 1) * sizeof(char *));
	if (result == NULL)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s != c && *s)
			result[i++] = get_next_word(s, c);
		while (*s != c && *s)
			s++;
	}
	result[i] = 0;
	return (result);
}

// int	main(void)
// {
// 	char **result = ft_split("lorem ipsum dolor sit", ' ');
// 	printf("%s\n", result[0]);
//  	printf("%s\n", result[1]);
//  	printf("%s\n", result[2]);
// 	free(result);
//}
