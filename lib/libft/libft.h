/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:33:22 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/22 11:28:28 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include <stdbool.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strlen(const char *s);
int		ft_atoi(const char *str);
long	ft_atol(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_ltoa(long n);
char	**ft_split(char const *s, char c);
int		ft_wordcount(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void	*));

//printf
int		ft_printf(const char *format, ...);
int		ft_loop_format(const char *format, int chars, va_list args);
int		ft_flaghandling(char c, va_list args);
int		ft_hex(unsigned long number, char c);
int		ft_counthex(unsigned long c);
char	*ft_litoa(long n);
int		ft_putchar_fd_l(char c, int fd);
int		ft_putstr_fd_l(char *s, int fd, char c);

//getnextline
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

//getnextline
char	*get_next_line(int fd);
void	*freeme(char **tofree);
int		ft_posinset(char const c, char const *ptr);
void	*hack_and_stack(char *line, char **cur_line, char **str_ret, int *pos);
void	*read_and_join(char *line, char **cur_line, const int fd, int *ret);
char	*ft_strjoin_ns(char *s1, char *s2);

//own functions from push_swap
int		ft_strisdigit(char *str);
char	*ft_strstr(const char *haystack, const char *needle);
void	ft_strreplace(char *str, char *tofind, char *replace);

//own functions from pipex
char	*ft_first_word(const char *str, char c, int rev);

//own functions from minishell
# ifndef READ
#  define READ 0
# endif
# ifndef WRITE
#  define WRITE 1
# endif
# ifndef FD_UNUSED
#  define FD_UNUSED INT32_MIN
# endif

int		ft_arraycount(char **array);
char	*ft_last_word(const char *str, char c, int rev);
int		ft_strcmp(char *s1, char *s2);
char	*multijoin(bool tofr, int n, ...);
char	*ft_multijoin_array(char **array);
void	ft_free_multiple(int n, ...);
void	*ft_free_array(void **array);
void	ft_close_and_neg(int *fd);
void	ft_close_pipe_fds(int pipe[2]);
#endif
