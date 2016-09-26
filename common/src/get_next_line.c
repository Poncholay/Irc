/*
** get_next_line.c for  in /home/wilmot_g/Documents/rendu/BocalEmblem
**
** Made by Guillaume WILMOT
** Login   <wilmot_g@epitech.net>
**
** Started on  Fri May 15 21:17:35 2015 guillaume wilmot
** Last update Tue May 17 11:26:15 2016 Nyrandone Noboud-Inpeng
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char		*my_new_line(char *line, char buff[BUFSIZ + 1],
			     int *st, int end)
{
  int		i;
  int		j;

  j = 0;
  i = line ? strlen(line) : 0;
  if ((line = realloc(line, (i + end + 1) * sizeof(char))) == NULL)
    {
      fprintf(stderr, "Error: realloc failed.\n");
      return (NULL);
    }
  while (j < end)
    {
      line[i + j] = buff[*st + j];
      j++;
    }
  line[i + j] = 0;
  *st = *st + end + 1;
  return (line);
}

char		*get_next_line(const int fd)
{
  char		*actual_line;
  static char	buff[BUFSIZ + 1];
  static int	start = 0;
  static int	size_buff = 0;
  int		end;

  actual_line = NULL;
  end = 0;
  while (42)
    {
      if (start >= size_buff)
	{
	  end = 0;
	  start = 0;
	  if ((size_buff = read(fd, buff, BUFSIZ)) <= 0)
	    return (actual_line);
	}
      if (buff[start + end] == '\n')
	return (my_new_line(actual_line, buff, &start, end));
      if (start + end == size_buff - 1)
	actual_line = my_new_line(actual_line, buff, &start, end + 1);
      end++;
    }
}
