#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

int get_next_line(char **line)
{
	int rd = 0;
	int i = 0;
	char ch;
	char *buffer = malloc(100000);
	
	*line = buffer;
	while ((rd = read(0, &ch, 1)) > 0 && ch != '\n')
		buffer[i++] = ch;
	buffer[i] = '\0';
	return (rd);
}

int	main()
{
	char **line;
	int i = 1;

	*line = malloc(1);
	while (i != 0)
	{
		i = get_next_line(line);
		printf ("%s\n", *line);
		printf("%d\n", i);
	}
	return(0);
}
