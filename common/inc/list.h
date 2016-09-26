/*
** list.h for list in /home/wilmot_g/Rendu/PSU_2015_myirc/common/inc
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon May 16 23:51:11 2016 guillaume wilmot
** Last update Sat May 21 18:11:21 2016 guillaume wilmot
*/

#ifndef LIST_H_
# define LIST_H_

typedef struct		s_list
{
  struct s_list		**last;
  struct s_list		**first;
  struct s_list		*next;
  struct s_list		*prev;
  void			*struc;
  unsigned int		*size;
  struct s_list		*(*get_nth)(struct s_list *, unsigned int);
  struct s_list		*(*delete_nth)(struct s_list *, unsigned int);
  struct s_list		*(*insert_at)(struct s_list *, unsigned int, void *);
  struct s_list		*(*push_back)(struct s_list *, void *);
  struct s_list		*(*push_front)(struct s_list *, void *);
  struct s_list		*(*pop_back)(struct s_list *);
  struct s_list		*(*pop_front)(struct s_list *);
  int			(*make_circular)(struct s_list *);
  int			(*get_size)(struct s_list *);
  void			(*destroy)(struct s_list *);
}			t_list;

t_list			*create_list(void *, t_list *);
t_list			*get_nth_list(t_list *, unsigned int);
t_list			*delete_nth_list(t_list *, unsigned int);
t_list			*insert_at_list(t_list *, unsigned int, void *);
t_list			*push_back_list(t_list *, void *);
t_list			*push_front_list(t_list *, void *);
t_list			*pop_back_list(t_list *);
t_list			*pop_front_list(t_list *);
int			make_circular_list(t_list *);
int			get_size_list(t_list *);
void			destroy_list(t_list *);
void			free_content(t_list *);

#endif /* !LIST_H_ */
