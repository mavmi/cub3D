#include "../../../include/map_parser.h"

static int	error_map_message(void)
{
	printf("Error: invalid map \n");
	return (1);
}

static int	map_check_valid_spaces(char **arr, size_t i_arr,
						size_t i_str, size_t len_str)
{
	size_t	len_str_up;
	size_t	len_str_down;

	len_str_up = ft_strlen(arr[i_arr - 1]);
	len_str_down = ft_strlen(arr[i_arr + 1]);
	if (i_str == 0)
	{

	}
}

static int	map_check_valid_str(char **arr, size_t i_arr)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(arr[i_arr]);
	if (arr[i_arr][0] != '1' || arr[i_arr][0] != ' '
			&& (arr[i_arr][len - 1] != '1' || arr[i_arr][len - 1] != ' '))
		return (error_map_message());
	i = 1;
	while (arr[i_arr][i])
	{
		if (arr[i_arr][i] == ' ')
		{
			if //func_check_spaces
				return (1);
		}
		else if (arr[i_arr][i] == 'd' || arr[i_arr][i] == 'D')
		{
			if //func_check_doors
				return (1);
		}
		i++;
	}
	return (0);
}

int	map_pars_valid(char **arr)
{
	size_t	i_arr;
	size_t	i_str;
	size_t	arr_len;

	if (!arr)
		return (2);
	i_arr = 0;
	i_str = 0;
	arr_len = arr_size_before_empty_str(arr);
	while (i_arr < arr_len) // if we take empty str
	{
		if (i_arr == 0 || i_arr == (arr_len - 1)) // first or second str
		{
			while (arr[i_arr][i_str])
			{
				if (arr[i_arr][i_str] != '1' || arr[i_arr][i_str] != ' ')
					return (error_map_message());
				i_str++;
			}
			t_str = 0;
		}
		else
		{
			if //func_check_valid_str(arr, i_arr)
				return (1);
		}
		i_arr++;
	}
	return (0);
}
