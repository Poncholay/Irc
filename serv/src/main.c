/*
** main.c for main in /Users/noboud_n/Documents/Share/PSU_2015_myirc/server/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon May 16 11:35:58 2016 Nyrandone Noboud-Inpeng
** Last update Sat May 21 02:19:39 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include "circular_buffer.h"
#include "errors.h"
#include "serv.h"

int			main(int argc, char **argv)
{
  t_socket		*socket;
  int			port;

  if (argc != 2 || (port = atoi(argv[1])) < 0)
    {
      fprintf(stderr, "Usage: ./server port\n");
      return (-1);
    }
  signal(SIGINT, clean_socket);
  if ((socket = init_server_socket(port)) == NULL)
    return (-1);
  core(socket, NULL, NULL);
  return (0);
}
