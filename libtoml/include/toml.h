/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toml.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:02:26 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/28 11:14:00 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOML_H
# define TOML_H

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>

typedef struct	s_reader
{
	int		fd;
	char	*buffer;
	size_t	buffer_size;
	size_t	len;
	size_t	i;
	size_t	column;
	size_t	line;
}				t_reader;

typedef enum	e_toml_type
{
	TOML_Integer,
	TOML_Float,
	TOML_String,
	TOML_Boolean,
	TOML_Array,
	TOML_Table
}				t_toml_type;

typedef enum	e_toml_error
{
	No_Error,
	Error_Malloc,
	Invalid_Array,
	Invalid_Bool,
	Invalid_Key,
	Invalid_String,
	Invalid_Table_Header,
	Invalid_Table,
	Invalid_Inline_Table,
	Invalid_Toml_Value,
	Invalid_Format_Key_Value,
}				t_toml_error;

typedef union	u_toml_value
{
	int64_t				integer_v;
	double				float_v;
	char				*string_v;
	bool				boolean_v;
	struct s_toml_array	*array_v;
	struct s_toml_table	*table_v;
}				t_toml_value;

typedef struct	s_toml
{
	t_toml_type		type;
	t_toml_value	value;
}				t_toml;

typedef struct	s_str
{
	size_t	len;
	size_t	capacity;
	char	*inner;
}				t_str;

typedef struct	s_toml_array
{
	size_t		len;
	size_t		capacity;
	t_toml_type	type;
	t_toml		*inner;
}				t_toml_array;

typedef struct	s_toml_entry
{
	char	*key;
	t_toml	value;
}				t_toml_entry;

typedef struct	s_toml_table
{
	size_t			len;
	size_t			capacity;
	t_toml_type		type;
	t_toml_entry	*inner;
}				t_toml_table;

t_reader		create_reader(int fd, char *buffer, size_t buffer_size);
int16_t			reader_peek(t_reader *self);
void			reader_next(t_reader *self);

void			skip_ws(t_reader *r, bool newline);
char			read_escape(t_reader *r);

t_str			create_str(size_t capacity);
bool			append_char(t_str *str, char c);
t_toml_array	*create_array(size_t capacity);
bool			append_array(t_toml_array *array, t_toml tom);
t_toml_table	*create_table(size_t capacity);
bool			append_table(t_toml_table *table, char *key, t_toml tom);

t_toml_error	read_toml(t_reader *r, t_toml_table **gros_poisson,
					bool read_tables);
t_toml_error	read_table(t_reader *r, t_toml_table *gros_poisson);
t_toml_error	read_inline_table(t_reader *r, t_toml *tom);

t_toml_error	read_key(t_reader *r, char **str);
t_toml_error	read_key_val(t_reader *r, t_toml_table *gros_poisson);
t_toml_error	read_quoted_key(t_reader *r, bool b, char **str);
t_toml_error	read_dotted_key(t_reader *r, t_toml_table **petit_poisson,
					char **key);

t_toml_error	read_toml_value(t_reader *r, t_toml *tom);
t_toml			read_toml_digit(t_reader *r);
t_toml_error	read_string(t_reader *r, t_toml *tom);
t_toml_error	read_multi_string(t_reader *r, bool quote, char **s);
t_toml_error	read_array(t_reader *r, t_toml *tom);
t_toml_error	read_boolean(t_reader *r, t_toml *tom);

t_toml			*table_get(t_toml_table *table, const char *key);
t_toml			create_toml_table(t_toml_table *value);
char			*toml_error_msg(t_toml_error err);

int				free_toml_array(t_toml_array *array);
int				free_toml_table(t_toml_table *table);
int				free_toml_string(char *str);
void			free_toml(t_toml *tom);

#endif
