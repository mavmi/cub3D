#include "../../include/arg_parser.h"

int errors()
{
	printf("Error: invalid file's arguments\n");
	return (1);
}

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
