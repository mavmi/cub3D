#include "../../include/arg_parser.h"

/*
	Checks the floor and ceiling digit colors
	aren't bigger then three ints (hundredth place)
*/
int	check_other_three_elems(char *str)
{
	size_t	i_str;
	size_t	i_int;

	if (!str)
		return (2);
	i_str = 0;
	i_int = 0;
	while (str[i_str])
	{
		while (str[i_str] >= '0' && str[i_str++] <= '9')
			i_int++;
		if (i_int > 3)
			return (error_ud_message());
		i_int = 0;
		i_str++;
	}
	return (0);
}


size_t	arr_size_before_empty_str(char **arr)
{
	size_t	len;

	len = 0;
	if (!arr)
		return (len);
	while (arr[len][0])// if we take empty str
	{
		len++;
	}
	return (len);
}

int	error_destroy(char error_message)
{
	pars_destroy_up_down(ud_arr);
	pars_destroy_textures(txtr_arr);
	if (error_message == 'y')
		return (errors());
	else
		return (1);
}
