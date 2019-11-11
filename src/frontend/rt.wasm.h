/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.wasm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 09:21:28 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/11/14 09:29:00 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_WASM_H
# define RT_WASM_H

# include <stdint.h>
# include <stdbool.h>
# include <stddef.h>

bool		rt_render_update(uint32_t *pixels, size_t progress);

#endif
