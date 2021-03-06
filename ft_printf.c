#include <stdarg.h>
#include <stdlib.h>
#include "printf.h"

int		init(t_printf *list)
{
	if (ft_strcmp(list->f_copy, "%") == 0)
		return (0);
	while (list->f_copy[list->i] != '\0')
	{
		if (list->f_copy[list->i] == '%')
		{
			list->i++;
			flag(list);
			display(list);
		}
		else
		{
			write(1, &list->f_copy[list->i], 1);
			list->cow++;
		}
		list->i++;
	}
	return (list->cow);
}

t_printf	*newlist_with_printf(t_printf *list)
{
	list->flag = 'Q';
	list->width = 0;
	list->precision = 0;
	list->length[0] = 'Q';
	list->type = 'Q';
	list->widthofline = 0;
	list->widthofcontent = 0;
	list->base = 10;
	list->cow = 0;
	list->np = 'n';
	list->i = 0;
	list->types = "aAcCeEgGsSnpdDifFuUoxX%";
	list->cons = "-+ 0#";
	list->args = "lhjz";
	return (list);
}

void	display(t_printf *list)
{
	if (list->type == 'd' || list->type == 'i' || list->type == 'D')
		d_and_i(list);
	else if (list->type == 'c' || list->type == 'C')
		type_c(list);
	else if (list->type == 'f' || list->type == 'F')
		type_f_and_F(list);
	else if (list->type == 's' || list->type == 'S')
		type_s(list);
	else if (list->type == 'u' || list->type == 'U')
		type_u(list);
	else if (list->type == 'x' || list->type == 'X' || list->type == 'o')
		type_x_and_X(list);
	else if (list->type == 'p')
		type_p(list);
	else
		ft_putstr_cow(list->f_copy, list);
		//ft_putchar_cow(list->f_copy[i], list);
}

int		ft_printf(const char *format, ...)
{
	t_printf *list;

	if (!(list = (t_printf*)malloc(sizeof(t_printf))))
		return(-1);
	list->format = format;
	list = newlist_with_printf(list);
	if (format)
	{
		va_start(list->ap, format);
		list->f_copy = (char *)list->format;
		list->cow = init(list);
		va_end(list->ap);
	}
	free(list);
	return (list->cow);
}
