/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:47:12 by jchen             #+#    #+#             */
/*   Updated: 2024/11/20 11:57:50 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/****************************/
/*          LIB  C          */
/****************************/

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlen(const char *s);
void				*ft_memset(void *dest, int val, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t siz);
size_t				ft_strlcat(char *dst, const char *src, size_t siz);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_atoi(const char *nptr);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *s);

/****************************/
/*            ADD           */
/****************************/

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/****************************/
/*          STRUCT          */
/****************************/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/****************************/
/*          PRINTF          */
/****************************/

int					ft_printchar(char c);
int					ft_printf(const char *str, ...);
int					ft_printstr(char *str);
int					ft_printnbr(int n);
int					ft_printunsigned(unsigned int n);
int					ft_printhex(unsigned int n, char c);
int					ft_printptr(void *adr_ptr);

/****************************/
/*       GET_NEXT_LINE      */
/****************************/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FDMAX
#  define FDMAX 1024
# endif

char				*get_next_line(int fd);
size_t				gnl_strlen(const char *s);
int					gnl_strchr_i(const char *s, int c);
size_t				gnl_strlcpy(char *dst, const char *src, size_t size);
char				*gnl_substr(char const *s, unsigned int start, size_t len);
size_t				gnl_strlcat(char *dst, const char *src, size_t size);
char				*gnl_shrink_buffer(char *buf, char *line);
char				*gnl_expand_buffer(char *buf, int fd);
char				*gnl_newread(int fd);

/****************************/
/*           AUTRE          */
/****************************/

char				*ft_strchr(const char *s, int c);
char				*ft_strstr(char *str, char *to_find);
char				*ft_chardup(char c);

#endif
