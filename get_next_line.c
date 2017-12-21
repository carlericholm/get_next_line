/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cholm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 18:17:18 by cholm             #+#    #+#             */
/*   Updated: 2017/12/21 15:45:05 by cholm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include <stdio.h>


char	*ft_getstr(const int fd, char *str, char *buf)
{
	char *tmp;
	int ret;

	ret = 0;
	tmp = ft_strnew(1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0 && (str = ft_strchr(buf, '\n')) == NULL)
	{
		buf[ret] = '\0';
		tmp = ft_strjoin(tmp, buf);
	}
	buf[ret] = '\0';
	printf("STR ->>>%s\n", str);

	return (ft_strjoin(tmp , ft_strsub(buf, 0, (str - buf))));
}


int		get_next_line(const int fd, char **line)
{
	static char buf[BUFF_SIZE + 1];
	static char *str;
	int i;

	i = 0;
	printf("***************************************\n");
	printf("entre gnl ->>> %s\n", buf);
	if (buf[0])
	{
		while (buf[i] != '\n' && buf[i] != '\0')
		{
			if (buf[i] == '\0')
			{
				i = 0;
				break;
			}
			i++;
		}
	}
	printf("strsub = %s\n",ft_strsub(buf, i + 1, BUFF_SIZE));
	*line  = ft_strjoin(ft_strsub(buf, i + 1, BUFF_SIZE) ,ft_getstr(fd, str, buf));
	printf("getstr = %s\n",ft_getstr(fd, str, buf));
	printf("--> str = %s<-- ,--> buf = %s <--\n", str , buf);

	return (0);
}


int main(int ac, char **av)
{
	int     fd;
	int     ret;
	char    *line;

	line = NULL;
	fd = open(av[ac - 1], O_RDONLY);
	get_next_line(fd, &line);
	printf("ligne de sorti 1 = %s<--\n",line);
	get_next_line(fd, &line);
	printf("ligne de sorti 2 = %s<--\n",line);
	return (0);
}
