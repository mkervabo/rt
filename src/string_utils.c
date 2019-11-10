#include <stddef.h>
#include <stdbool.h>

bool 		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (s1[i] == s2[i])
		return (false);
	return (true);
}

size_t		ft_strlen(const char *str)
{
	size_t	size;

	size = 0;
	while (str[size])
		size++;
	return (size);
}

void		*ft_memset(void *s, int c, size_t n)
{
	while (n--)
		((unsigned char *)s)[n] = c;
	return (s);
}