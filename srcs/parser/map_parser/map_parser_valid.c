#include "../../../include/map_parser.h"

static int	error_map_message(void)
{
	printf("Error: invalid map \n");
	return (-1);
}

static int	map_check_valid_spaces(char **arr, size_t i_arr,
						size_t i_str, t_param_len *lens)
{
	// printf ("i_arr:%zu   i_str:%zu   l_up:%zu  l_down:%zu\n", i_arr, i_str, lens->up, lens->down);
	if (lens->up && i_str <= (lens->up - 1)   										// check for up elem
		&& (arr[i_arr - 1][i_str] != ' ' && arr[i_arr - 1][i_str] != '1'))
		return (error_map_message());
	if (lens->down && i_str <= (lens->down - 1) 										// check for down elem
		&& (arr[i_arr + 1][i_str] != ' ' && arr[i_arr + 1][i_str] != '1'))
		return (error_map_message());

	// check right side
	if (arr[i_arr][i_str + 1]      											// check for right elem
		&& (arr[i_arr][i_str + 1] != ' ' && arr[i_arr][i_str + 1] != '1'))
		return (error_map_message());
	if (lens->up && i_str < (lens->up - 1)    										// check for right_up elem
		&& (arr[i_arr - 1][i_str + 1] != ' ' && arr[i_arr - 1][i_str + 1] != '1'))
		return (error_map_message());
	if (lens->down && i_str < (lens->down - 1)  										// check for right_down elem
		&& (arr[i_arr + 1][i_str + 1] != ' ' && arr[i_arr + 1][i_str + 1] != '1'))
		return (error_map_message());

	// checks left side
	if (i_str != 0 && (arr[i_arr][i_str - 1] != ' ' && arr[i_arr][i_str - 1] != '1')) 	// check for left elem
		return (error_map_message());
	if (i_str != 0 && lens->up && i_str <= (lens->up - 1)
			&& (arr[i_arr - 1][i_str - 1] != ' ' && arr[i_arr - 1][i_str - 1] != '1'))// check for left_up elem
		return (error_map_message());
	if (i_str != 0 && lens->down && i_str <= (lens->down - 1)
			&& (arr[i_arr + 1][i_str - 1] != ' ' && arr[i_arr + 1][i_str - 1] != '1'))// check for left_down elem
		return (error_map_message());
	return (0);
}

static int	map_check_valid_doors(char **arr, size_t i_arr,
						size_t i_str, t_param_len *lens)
{
	if (i_str > (lens->up - 1) || i_str >(lens->down - 1)
			|| !arr[i_arr][i_str + 1])
		return (error_map_message());
	if (arr[i_arr - 1][i_str] == '1')
	{
		if (arr[i_arr + 1][i_str] == '1' && arr[i_arr][i_str - 1] != '1'
			&& arr[i_arr][i_str + 1] != '1')
			return (0);
	}
	else if (arr[i_arr][i_str - 1] == '1')
	{
		if (arr[i_arr][i_str + 1] == '1' && arr[i_arr - 1][i_str] != '1'
			&& arr[i_arr + 1][i_str] != '1')
			return (0);
	}
	return (error_map_message());
}

static int	map_check_valid_str(char **arr, size_t i_arr, t_param_len *lens)
{
	size_t	i;

	if ((arr[i_arr][0] != '1' && arr[i_arr][0] != ' ')
			|| (arr[i_arr][lens->str - 1] != '1'
				&& arr[i_arr][lens->str - 1] != ' '))
		return (error_map_message());
	i = 1;
	while (arr[i_arr][i])
	{
		if (arr[i_arr][i] == ' ')
		{
			if (map_check_valid_spaces(arr, i_arr, i, lens) < 0)
				return (-1);
		}
		else if (arr[i_arr][i] == 'd' || arr[i_arr][i] == 'D')
		{
			if (map_check_valid_doors(arr, i_arr, i, lens) < 0)
				return (-1);
		}
		i++;
	}
	return (0);
}

static int	map_check_str_end(char **arr, size_t i_arr, t_param_len *lens)
{
	size_t	i;

	i = lens->str - 1;
	if (lens->up && lens->up < lens->str)
	{
		while (i >= (lens->up - 1))
		{
			if (arr[i_arr][i] != '1' && arr[i_arr][i] != ' ')
				return (error_map_message());
			i--;
		}
		i = lens->str - 1;
	}
	if (lens->down && lens->down < lens->str)
	{
		while (i >= (lens->down - 1))
		{
			if (arr[i_arr][i] != '1' && arr[i_arr][i] != ' ')
				return (error_map_message());
			i--;
		}
	}
	return (0);
}

int	map_pars_valid(char **arr)
{
	size_t		i_arr;
	size_t		i_str;
	t_param_len	lens;

	if (!arr)
		return (2);
	i_arr = 0;
	i_str = 0;
	lens.arr = arr_size_before_empty_str(arr);
	lens.up = 0;
	lens.down = 0;
	while (i_arr < lens.arr)
	{
		lens.str = ft_strlen(arr[i_arr]);
		if (i_arr != 0)
			lens.up = ft_strlen(arr[i_arr - 1]);
		if (i_arr != (lens.arr - 1))
			lens.down = ft_strlen(arr[i_arr + 1]);
		else
			lens.down = 0;
		if (map_check_str_end(arr, i_arr, &lens) < 0)
		{
			return (-1);
		}
		if (i_arr == 0 || i_arr == (lens.arr - 1)) // first or last str
		{
			while (arr[i_arr][i_str])
			{
				if (arr[i_arr][i_str] != '1' && arr[i_arr][i_str] != ' ')
					return (error_map_message()); //check argums to anvalid spaces
				if (arr[i_arr][i_str] == ' ')
				{
					if (map_check_valid_spaces(arr, i_arr, i_str, &lens) < 0)
						return (-1);
				}
				i_str++;
			}
			i_str = 0;
		}
		else
		{
			if (map_check_valid_str(arr, i_arr, &lens) < 0)
				return (-1);
		}
		i_arr++;
	}
	return (lens.arr);
}
