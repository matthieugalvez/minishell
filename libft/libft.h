/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:06:28 by mgalvez           #+#    #+#             */
/*   Updated: 2025/09/10 13:33:18 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif

typedef struct s_list {
	void			*content;
	struct s_list	*next;
}	t_list;

double	ft_atof(char *num1, char *num2);
int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_checkrepeatingnbrs(int *tab, int depht);
int		ft_checksortednmbrs(int *tab, int depht);
void	ft_cut_tabline(char **tab, int i);
void	ft_freetab(char **tab);
void	ft_freentab(char **tab, size_t size);
int		ft_getbiggest(int *tab, int len);
int		ft_getmult(int nb);
char	*ft_getnextline(int fd);
int		ft_getsmallest(int *tab, int len);
int		*ft_indextab(int *tab, int depht);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isint(char *str);
int		ft_isoperator(char c);
int		ft_isspace(int c);
int		ft_isspacestr(char *str);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	ft_lstadd_back(t_list **lst, t_list *elem);
void	ft_lstadd_front(t_list **lst, t_list *elem);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
char	*ft_makerngname(int len);
int		ft_makernguint(int mod);
int		ft_max(int n1, int n2);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
int		ft_min(int n1, int n2);
int		ft_nbrlen(int nb);
int		ft_printf(const char *format, ...);
int		ft_printf_fd(int fd, const char *format, ...);
void	ft_pull(int *tab, int len);
void	ft_push(int *tab, int len);
int		ft_putaddress(void *address);
int		ft_putchar(char c, int fd);
int		ft_putendl(char *s, int fd);
int		ft_putnbr(int n, char *base, int fd);
int		ft_putlng(unsigned long nbr, char *base, int fd);
int		ft_putstr(char *s, int fd);
void	ft_print_str_tab(char **tab, int fd);
int		ft_putstr_errnull(char *s, int fd);
int		ft_putunsint(unsigned int nbr, char *base);
char	**ft_split(char const *s, char c);
char	**ft_split_free(char *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free(char *s1, char *s2, int to_free);
size_t	ft_strlcat(char *dst, const char *src, size_t siz);
size_t	ft_strlcpy(char *dst, const char *src, size_t siz);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strrncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strtrim_free(char *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_swap(int *n1, int *n2);
int		ft_tabcpy(char **dest, char **src);
int		ft_tablen(char **tab);
int		ft_tolower(int c);
int		ft_toupper(int c);

#endif
