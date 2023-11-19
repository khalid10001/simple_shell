#include "shell.h"

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

int is_delim(char c, char *delim)
{
	for (; *delim;)
		if (*delim++ == c)
			return (1);
	return (0);
}


int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int _atoi(char *s)
{
	int x, sign = 1, flag = 0, op;
	unsigned int res = 0;

	for (x = 0; s[x] != '\0' && flag != 2; x++)
	{
	if (s[x] == '-')
		sign *= -1;

	if (s[x] >= '0' && s[x] <= '9')
	{
		flag = 1;
		res *= 10;
		res += (s[x] - '0');
	}
	else if (flag == 1)
		flag = 2;
	}

	if (sign == -1)
		op = -res;
	else
		op = res;

	return (op);
}
