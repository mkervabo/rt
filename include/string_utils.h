/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:28:51 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/10 18:29:21 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_UTILS_H
# define STRING_UTILS_H

# include <stddef.h>
# include <stdbool.h>

bool		ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *str);
void		*ft_memset(void *s, int c, size_t n);

#endif
