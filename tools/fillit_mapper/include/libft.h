/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 18:16:07 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/08 14:43:02 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_dl_list
{
	void				*content;
	size_t				content_size;
	struct s_dl_list	*prev;
	struct s_dl_list	*next;
}				t_dl_list;

typedef struct	s_queue
{
	void			*content;
	size_t			content_size;
	struct s_queue	*prev;
	struct s_queue	*next;
}				t_queue;

typedef struct	s_stack
{
	void			*content;
	size_t			content_size;
	struct s_stack	*prev;
}				t_stack;

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, void const *src, size_t n);
void			*ft_memccpy(void *dest, void const *src, int c, size_t n);
void			*ft_memmove(void *dest, void const *src, size_t n);
void			*ft_memchr(void const *s, int c, size_t n);
int				ft_memcmp(void const *s1, void const *s2, size_t n);
size_t			ft_strlen(char const *s);
char			*ft_strdup(char const *s);
char			*ft_strcpy(char *dest, char const *src);
char			*ft_strncpy(char *dest, char const *src, size_t n);
char			*ft_strcat(char *dest, char const *src);
char			*ft_strncat(char *dest, char const *src, size_t n);
size_t			ft_strlcat(char *dest, char const *src, size_t n);
char			*ft_strchr(char const *s, int c);
char			*ft_strrchr(char const *s, int c);
char			*ft_strstr(char const *haystack, char const *needle);
char			*ft_strnstr(char const *s1, char const *s2, size_t n);
int				ft_strcmp(char const *s1, char const *s2);
int				ft_strncmp(char const *s1, char const *s2, size_t n);
int				ft_atoi(char const *nptr);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void(*f)(char *));
void			ft_striteri(char *s, void(*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char(*f)(char));
char			*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
# ifdef LIBFT_EXTRA

int				ft_pow(int b, int e);
int				ft_isspace(int c);
int				ft_isupper(int c);
int				ft_islower(int c);
int				ft_lstsize(t_list *lst);
t_dl_list		*ft_dl_lstnew(void const *content, size_t content_size);
void			ft_dl_lstclear(t_dl_list **alst);
t_dl_list		*ft_dl_lstfront(t_dl_list *lst);
t_dl_list		*ft_dl_lstback(t_dl_list *lst);
void			ft_dl_lstpushfront(t_dl_list **alst, t_dl_list *new);
void			ft_dl_lstpushback(t_dl_list *lst, t_dl_list *new);
void			ft_dl_lstpopfront(t_dl_list **alst);
void			ft_dl_lstpopback(t_dl_list **alst);
void			ft_dl_lstiter(t_dl_list *lst, void (*f)(t_dl_list *elem));
t_dl_list		*ft_dl_lstmap(t_dl_list *lst, t_dl_list *(*f)(t_dl_list *elem));
int				ft_dl_lstsize(t_dl_list *lst);
t_queue			*ft_queuenew(void const *content, size_t content_size);
t_queue			*ft_queuefront(t_queue *queue);
t_queue			*ft_queueback(t_queue *queue);
void			ft_queuepush(t_queue *queue, t_queue *new);
void			ft_queuepop(t_queue **aqueue);
int				ft_queuesize(t_queue *queue);
t_stack			*ft_stacknew(void const *content, size_t content_size);
void			ft_stackpush(t_stack **astack, t_stack *new);
void			ft_stackpop(t_stack **astack);
int				ft_stacksize(t_stack *stack);
# endif
#endif
