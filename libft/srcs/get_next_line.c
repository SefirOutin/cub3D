/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:46:39 by bmoudach          #+#    #+#             */
/*   Updated: 2024/02/22 20:09:26 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	ft_trim(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	str[i] = '\0';
}

static void	ft_mouv(char *buf, int byte)
{
	int	i;
	int	j;

	if (!ft_strchr(buf, '\n'))
		return ;
	i = ft_strchr(buf, '\n') - buf + 1;
	j = 0;
	while (buf[i] && (byte || ft_strchr(buf, '\n')))
		buf[j++] = buf[i++];
	buf[j] = '\0';
}

char	*get_next_line(int fd, int *err)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			byte;

	byte = 1;
	if (fd < 0 || read(fd, buf, 0))
		return (NULL);
	line = (char *)ft_strjoin_gnl(NULL, buf);
	if (!line)
		return (*err = 1, NULL);
	while (!ft_strchr(line, '\n'))
	{
		byte = read(fd, buf, BUFFER_SIZE);
		buf[byte] = '\0';
		if (byte == 0)
			break ;
		if (byte < 0)
			return (*err = 1, free(line), NULL);
		line = (char *)ft_strjoin_gnl(line, buf);
		if (!line)
			return (*err = 1, NULL);
	}
	if (!line[0])
		return (free(line), NULL);
	return (ft_trim(line), ft_mouv(buf, byte), line);
}

/*int	main(void)
|{
  char	*str;
  int		fd;

  fd = open("texte", O_RDONLY);
  while (str = get_next_line(fd))
  {
  write(1, str, strlen(str));
  free(str);
  }
  close(fd);
  }*/
