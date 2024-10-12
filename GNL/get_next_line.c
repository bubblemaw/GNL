/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:42:53 by maw               #+#    #+#             */
/*   Updated: 2024/10/12 19:54:31 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*feedline(char *s)
{
	size_t	i;
	char	*feed;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0' && s[i] != '\n')
	{
		i++;
	}
	feed = ft_substr(s, 0, i + 1);
	if (!feed)
		return (NULL);
	return (feed);
}

static	char	*reading(int fd, char *get, char *reste, char *buffer)
{
	int	readcount;

	readcount = 1;
	while (readcount > 0)
	{
		readcount = read(fd, buffer, BUFFER_SIZE);
		if (readcount == -1)
			return (NULL);
		buffer[readcount] = '\0';
		if (get == NULL)
		{
			get = ft_strdup(buffer);
			if (get == NULL)
			{
				free(get);
				return (NULL);
			}
			if (ft_strchr(get, '\n') != NULL)
				return (get);
		}
		else
		{
			reste = ft_strjoin(get, buffer);
			free(get);
			get = reste;
			if (!get)
				return (NULL);
			if (ft_strchr(get, '\n') != NULL)
				return (get);
		}
	}
	return (get);
}

static	char	*setupget(char *get, char *reste)
{
	reste = NULL;
	if (ft_strchr(get, '\n') != NULL)
	{
		reste = ft_strdup(ft_strchr(get, '\n') + 1);
		if (!reste)
		{
			free(reste);
			return (NULL);
		}
		free(get);
		get = reste;
		if (get == NULL)
			return (NULL);
	}
	else
	{
		free(get);
		get = NULL;
	}
	return (get);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*get;
	char		*line;
	char		*reste;

	line = NULL;
	reste = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(get);
		get = NULL;
		return (NULL);
	}
	get = reading(fd, get, reste, buffer);
	if (!get)
		return (NULL);
	if (get)
	{
		line = feedline(get);
		get = setupget(get, reste);
		if (!line || line[0] == '\0')
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}

// int main(void)
// {
// 	int fd;
// 	char *line;

// 	fd = open("test.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 		{
// 			break ;
// 		}
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }

// // // objectif creer un buffer que je vais print
// puis ensuite freee ainsi de suite jusqua la fin
// de la laligne en gros

// Il faut que je soit capable de mofdifier la taiile
// de mon buffer en fonction de la tailler du buffersize donneer