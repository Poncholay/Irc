/*
** store_nbr.c for store_nbr in /Users/noboud_n/Documents/Share/PSU_2015_myirc/serv/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sat May 21 23:51:13 2016 Nyrandone Noboud-Inpeng
** Last update Sun May 22 00:48:54 2016 Nyrandone Noboud-Inpeng
*/

int	inf(char **str, int *x, int nb)
{
  if (nb < 0)
    {
      nb = nb * (-1);
      (*str)[(*x)++] = '-';
      return (nb);
    }
  return (nb);
}

void	store_nbr(char **str, int *x, int nb)
{
  int	i;

  nb = inf(str, x, nb);
  i = 1;
  while ((nb / i) > 9)
    i = i * 10;
  while (i > 0)
    {
      (*str)[(*x)++] = ('0' + ((nb / i) % 10));
      i = i / 10;
    }
}
