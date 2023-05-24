#include "shell.h"

/**
 * _myhistory - displays the history list
 * one command by line
 * with line numbers starting at zero (0)
 * @info: structure containing potential arguments
 * used to maintain constant function prototype
 * Return: Always returns 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: always 0 on success 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *pi, c;
	int ret;

	pi = _strchr(str, '=');
	if (!pi)
		return (1);
	c = *pi;
	*pi = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*pi = c;
	return (ret);

}

/**
 * set_alias - sets alias to a string
 * @info: parameter structure
 * @str: the string alias
 * Return: always 0 on success and 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *pi;

	pi = _strchr(str, '=');
	if (!pi)
		return (1);
	if (!*++pi)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 * Return: 0 on success and 1 on error
 */
int print_alias(list_t *node)
{
	char *pi = NULL, *a = NULL;

	if (node)
	{
		pi = _strchr(node->str, '=');
		for (a = node->str; a <= pi; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(pi + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments
 * Used to maintain constant function prototype
 *  Return: always 0
 */
int _myalias(info_t *info)
{
	int j = 0;
	char *pi = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		pi = _strchr(info->argv[j], '=');
		if (pi)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}
