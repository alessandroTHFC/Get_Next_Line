#include "get_next_line.h"

static char	*read_n_append(int fd, char *buffer, char *leftovers);
static char	*update_n_format(char *line);

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*leftovers;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	line = read_n_append(fd, buffer, leftovers);
	free(buffer);
	buffer = NULL;
	if (line == NULL)
		return (NULL);
	leftovers = update_n_format(line);
	return (line);
}

static char	*read_n_append(int fd, char *buffer, char *leftovers)
{
	int	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!leftovers)
			leftovers = ft_strdup("");
		temp = leftovers;
		leftovers = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break;
	}
	return (leftovers);
}

static char *update_n_format(char *line)
{
	size_t	nl_indx;
	char	*leftovers;

	nl_indx = 0;
	while (line[nl_indx] != '\n' && line[nl_indx] != '\0')
		nl_indx++;
	if (line[nl_indx] == '\0' || line[1] == '\0')
		return(NULL);
	leftovers = ft_substr(line, nl_indx + 1, ft_strlen(line) - nl_indx);
	if (*leftovers == '\0')
	{
		free(leftovers);
		leftovers = NULL;
	}
	line[nl_indx + 1] = '\0';
	return (leftovers);
}
