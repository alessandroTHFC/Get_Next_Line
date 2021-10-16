/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-n <llopes-n@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:06:23 by llopes-n          #+#    #+#             */
/*   Updated: 2021/10/11 18:22:57 by llopes-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*read_acheck_bk(int fd, char *buffer, char *backup)
{
	int		read_line;
	char	*char_temp;

	read_line = 1;
	while (read_line != 0)
	{
		read_line = read(fd, buffer, BUFFER_SIZE);//two things: read_line = nb bytes read&buff gets whats read;
		if (read_line == -1)
			return (NULL);
		else if (read_line == 0)
			break ;
		buffer[read_line] = '\0';
		if (!backup)
			backup = ft_strdup("");//if no previous read or no nl in previous read, backup is empty;
						

		char_temp = backup;//backup which should be the reminder of previous read stored in char temp;
		backup = ft_strjoin(char_temp, buffer);//backups new value is the join old contents with new read;
		free(char_temp);
		char_temp = NULL;


		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (backup);
}

static char	*extract_format(char *line)
{
	size_t	count_nl;
	char	*backup;
	
	count_nl = 0;
	while (line[count_nl] != '\n' && line[count_nl] != '\0')
		count_nl++;//counts up to where it finds the newline
	if (line[count_nl] == '\0' || line[1] == '\0')
		return (NULL);
	printf("\n>>LINE Xtrc b: %s<<\n", line);
	backup = ft_substr(line, count_nl + 1, ft_strlen(line) - count_nl); //taking whats after the newline and saving
										//it in backup!
	if (*backup == '\0')
	{
		free(backup);
		backup = NULL;
	}
	line[count_nl + 1] = '\0';//line has contents after newline nulled
	printf("\n>>LINE Af TERMINATR: %s<<\n", line);
	return (backup);//this value will be the what gets cut off after newline is found;
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*backup;

	printf("\n>>BACKUP AT BEGINING: %s<<\n", backup);
	if (fd < 0 || BUFFER_SIZE <= 0)//usual error checking blah blah
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));//malloc to create buffer to store whats read plus
									//room for null terminator;
	if (!buffer)
		return (NULL);
	line = read_acheck_bk(fd, buffer, backup);//call function that reads and stores new value in line&& if has read
							//on a previous function call will append new read onto contents
							//of old read stored in backup <- returns this value so line =
							// the contents of new read onto new read;
	printf("\n>>LINE GETS VAL: %s<<\n", line);
	free(buffer);//no need for buffer anymore because its contents are now stored onto the end of backup;
	buffer = NULL;
	if (!line)
		return (line);
	backup = extract_format(line);//this function updates backup to the contents after newline and formats line to
					//stop after the newline has been found;
	//after previous statement backup equals the remainder and line is the string rd up to and inc newline;
	printf("\n>>F VAL OF LINE: %s----OF BACK: %s <<\n", line, backup);
	return (line);
}
