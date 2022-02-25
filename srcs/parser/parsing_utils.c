#include "../../include/arg_parser.h"

int	error_texture_message(void)
{
	printf("Error: invalid texture arguments \n");
	return (1);
}

int	error_ud_message(void)
{
	printf("Error: invalid floor/ceiling arguments\n");
	return (1);
}


/*
	Free freed and input sms about
	invalide argums if sms_fl == 'y'
*/
void	*free_return(size_t *freed, char sms_fl)
{
	if (sms_fl && sms_fl == 'y')
		error_ud_message();
	free(freed);
	return (NULL);
}

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
