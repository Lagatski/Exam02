#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

int get_next_line(char **line, int fd)
{
	int rd = 0;
	int i = 0;
	char ch;
	char *buffer = malloc(100000);
	
	*line = buffer;
	while ((rd = read(fd, &ch, 1)) > 0 && ch != '\n')
		buffer[i++] = ch;
	buffer[i] = '\0';
	return (rd);
}
