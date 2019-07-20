/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:44:53 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/07/20 14:53:25 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_ASSERT_H
# define DEBUG_ASSERT_H

# include <stdio.h>
# include <assert.h>

#define log_error(M, ...) fprintf(stderr, "Assert failed at %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define assertf(A, M, ...) if(!(A)) { log_error(M, ##__VA_ARGS__); assert(A); }

#endif
