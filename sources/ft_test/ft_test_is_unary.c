/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_is_unary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:30:29 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/23 10:09:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_21sh.h"

static int	is_not(char **arg)
{
	return (ft_strequ(arg[1], "!"));
}

// True if the length of string is zero.
static int ft_test_z(char **arg)
{
	int		not;

	not = is_not(arg);
	if (not && ft_strlen(arg[3]) == 0)
		return (1);
	else if (ft_strlen(arg[2]) == 0)
		return (0);
	return (1);
}

//	True if file exists and is executable.  True indicates only
//	that the execute flag is on.  If file is a directory, true
//	indicates that file can be searched.
static int ft_test_x(char **arg)
{
	int		not;

	not = is_not(arg);
	if (not && access(arg[3], X_OK) == 0)
		return (1);
	else if (access(arg[2], X_OK) == 0)
		return (0);
	return (1);
}

//	True if file exists and is writable.  True indicates only
//	that the write flag is on.  The file is not writable on a
//	read-only file system even if this test indicates true.
static int ft_test_w(char **arg)
{
	int		not;

	not = is_not(arg);
	if (not && access(arg[3], W_OK) == 0)
		return (1);
	else if (access(arg[2], W_OK) == 0)
		return (0);
	return (1);
}

//	True if file exists and its set user ID flag is set.
static int ft_test_u(char **arg) //need more work
{
	int		not;

	not = is_not(arg);
	if (not && access(arg[3], U_OK) == 0)
		return (1);
	else if (access(arg[2], U_OK) == 0)
		return (0);
	return (1);
}

// True if file exists and has a size greater than zero.
static int ft_test_s(char **arg)  //need more work
{
	int		not;

	not = is_not(arg);
	if (not && access(arg[3], S_OK) == 0)
		return (1);
	else if (access(arg[2], S_OK) == 0)
		return (0);
	return (1);
}

// True if file exists and is a socket.
static int ft_test_capital_s(char **arg) //need more work
{
	int		not;

	not = is_not(arg);
	if (not && access(arg[3], S_OK) == 0)
		return (1);
	else if (access(arg[2], S_OK) == 0)
		return (0);
	return (1);
}

/*
	These are mandatory:
	-c, -d, -e, -f, -g, -L, -p, -r, -S, -s, -u, -w, -x, -z, !
*/
int is_unary(char *str)
{
	return (ft_strequ(str, "-c") || ft_strequ(str, "-d")
			|| ft_strequ(str, "-e") || ft_strequ(str, "-f")
			|| ft_strequ(str, "-g") || ft_strequ(str, "-L")
			|| ft_strequ(str, "-p") || ft_strequ(str, "-r")
			|| ft_strequ(str, "-S") || ft_strequ(str, "-s")
			|| ft_strequ(str, "-u") || ft_strequ(str, "-w")
			|| ft_strequ(str, "-x") || ft_strequ(str, "-z")
			|| ft_strequ(str, "!"));
}
