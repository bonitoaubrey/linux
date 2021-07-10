#include "get_next_line.h"

char	*ft_add_line(char *buff, char **line)
{
	char	*temp;

	temp = ft_strchr(buff, '\n');
	if (temp)
	{
		*temp++ = '\0';
		*line = ft_strjoin(*line, buff);
		*line = ft_strjoin(*line, "\n");
		ft_strcpy(buff, temp);
	}
	else
		*line = ft_strjoin(*line, buff);
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*temp;
	char		*line;
	static char	buff[SIZE + 1];
	static int	end = 1;

	if (read(fd, buff, 0) == -1 || SIZE == 0 || end == -1)
		return (NULL);
	line = ft_strdup("");
	if (NULL == line)
		return (NULL);
	temp = ft_add_line(buff, &line);
	while (end > 0 && !temp)
	{
		end = read(fd, buff, SIZE);
		if (end == -1)
		{
			free(line);
			return (NULL);
		}
		buff[end] = '\0';
		temp = ft_add_line(buff, &line);
	}
	if (end == 0 && !temp)
		end = -1;
	return (line);
}
