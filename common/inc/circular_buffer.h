/*
** circular_buffer.h for myIRC in /home/wilmot_g/Rendu/PSU_2015_myirc/common
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Thu May 19 00:42:04 2016 guillaume wilmot
** Last update Sun May 22 18:29:43 2016 guillaume wilmot
*/

#ifndef CIRCULAR_BUFFER_H_
# define CIRCULAR_BUFFER_H_

# define BUFFSIZE_IN	512
# define BUFFSIZE_OUT	16384

# include "list.h"

typedef struct		s_buff
{
  unsigned int		size;
  char			*buff;
  char			*cmd;
  unsigned int		idx;
  unsigned int		start;
  unsigned int		start_bis;
  unsigned int		end;
  unsigned int		overflow;
  unsigned char		found;
}			t_buff;

typedef struct		s_buffs
{
  t_buff		in;
  t_buff		out;
  t_list		*cmds;
}			t_buffs;

t_buffs			*create_buffer(t_buffs *);
char			*get_buff_content(t_buff *);
int			write_to_buffer(const char *, t_buff *, int);
int			get_cmd_buff(int, t_buffs *);
int			send_msg(int, char *);
void			replace_end_of_string(char *);

#endif /* !CIRCULAR_BUFFER_H_ */
