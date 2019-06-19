/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:09:45 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/22 16:14:05 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toml.h"

char	*toml_error_msg(t_toml_error err)
{
	const char	*messages[] = {
		[Error_Malloc] = "Error Maloc",
		[Invalid_Array] = "Invalid Array",
		[Invalid_Bool] = "Invalid Boolean",
		[Invalid_Key] = "Invalid Key",
		[Invalid_String] = "Invalid String",
		[Invalid_Table_Header] = "Invalid Table Header",
		[Invalid_Table] = "Invalid Table",
		[Invalid_Inline_Table] = "Invalid Inline Table",
		[Invalid_Toml_Value] = "Invalid Toml Value",
		[Invalid_Format_Key_Value] = "Invalid Format Key Value (missing '=' ?)",
	};

	if (err > 0 && err <= sizeof(messages) / sizeof(*messages))
		return ((char *)messages[err]);
	else
		return (NULL);
}
