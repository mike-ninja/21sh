/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_is_unary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:30:29 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/23 12:06:24 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_21sh.h"

// Make own file
static int	is_not(char **arg)
{
	return (ft_strequ(arg[1], "!"));
}

// Make own file
static int not_return_last(int not)
{
	if (not)
    	return 0;
	return 1;
}

static char *get_file_path(char **arg, int not) // Do we need to have a check for '.' and '..'?
{
	char		filepath[PATH_MAX];

	if (not)
	{
		if (arg[3][0] != '/')
		{
			getcwd(filepath, sizeof(filepath));
			filepath = ft_strjoin(filepath, arg[3]);
		}
		else
			filepath = ft_strdup(arg[3]);
	}
	else
	{
		if (arg[2][0] != '/')
		{
			getcwd(filepath, sizeof(filepath));
			filepath = ft_strjoin(filepath, arg[2]);
		}
		else
			filepath = ft_strdup(arg[2]);
	}
	return (filepath);
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
	return (not_return_last(not));
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
	return (not_return_last(not));
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
	return (not_return_last(not));
}

//	True if file exists and its set user ID flag is set.
static int ft_test_u(char **arg)
{
    struct stat file_info;
	char		*filepath;
	int			not;

	not = is_not(arg);
	filepath = get_file_path(arg, not);
    if (stat(filepath, &file_info) != 0) {
        // in this case, the file does not exist
		ft_strdel(&filepath);
		return (not_return_last(not));
    }
	ft_strdel(&filepath);
    // check the SUID flag using the S_ISUID macro
    if (S_ISUID & file_info.st_mode)
	{
        // the SUID flag is set
        if (not)
			return (1);
		return 0; // On success
	}
	return (not_return_last(not));

}

// True if file exists and has a size greater than zero.
static int ft_test_s(char **arg)
{
    struct stat file_info;
	char		*filepath;
	int			not;

	not = is_not(arg);
	filepath = get_file_path(arg, not);
	if (stat(filepath, &file_info) != 0)
	{
		ft_strdel(&filepath);
		// in this case, the file does not exist
		return (not_return_last(not));
    }
	ft_strdel(&filepath);
    if (file_info.st_size > 0)
	{
		if (not)
			return (1);
		return (0); // On success
	}
    return (not_return_last(not));
}

// True if file exists and is a socket.
static int ft_test_capital_s(char **arg)
{
	struct stat file_info;
	char		*filepath;
	int			not;

	not = is_not(arg);
	filepath = get_file_path(arg, not);
	if (stat(filepath, &file_info) != 0)
	{
		ft_strdel(&filepath);
		// in this case, the file does not exist
		return (not_return_last(not));
    }
	ft_strdel(&filepath);
    if (S_ISSOCK(file_info.st_mode))
	{
		if (not)
			return (1);
		return (0); // On success
	}
    return (not_return_last(not));
}

//True if file exists and is readable.
static int	ft_test_r(char **arg)
{
	int		not;

	not = is_not(arg);
	if (not && access(arg[3], R_OK) == 0)
		return (1);
	else if (access(arg[2], R_OK) == 0)
		return (0);
	return (not_return_last(not));
}


//	True if file exists and is a named pipe (FIFO).
static int ft_test_p(char **arg)
{
	struct stat file_info;
	char		*filepath;
	int			not;

	not = is_not(arg);
	filepath = get_file_path(arg, not);
	if (stat(filepath, &file_info) != 0)
	{
		ft_strdel(&filepath);
		// in this case, the file does not exist
		return (not_return_last(not));
	}
	ft_strdel(&filepath);
	if (S_ISFIFO(file_info.st_mode))
	{
		if (not)
			return (1);
		return (0); // On success
	}
	return (not_return_last(not));
}

// True if file exists and is a symbolic link.
static int ft_test_capital_l(char **arg)
{
	struct stat file_info;
	char		*filepath;
	int			not;

	not = is_not(arg);
	filepath = get_file_path(arg, not);
	if (stat(filepath, &file_info) != 0)
	{
		ft_strdel(&filepath);
		// in this case, the file does not exist
		return (not_return_last(not));
	}
	ft_strdel(&filepath);
	if (S_ISLNK(file_info.st_mode))
	{
		if (not)
			return (1);
		return (0); // On success
	}
	return (not_return_last(not));
}

// True if file exists and its set group ID flag is set.
static int ft_test_g(char **arg)
{
	struct stat file_info;
	char		*filepath;
	int			not;

	not = is_not(arg);
	filepath = get_file_path(arg, not);
	if (stat(filepath, &file_info) != 0)
	{
		ft_strdel(&filepath);
		// in this case, the file does not exist
		return (not_return_last(not));
	}
	ft_strdel(&filepath);
	if (S_ISGID & file_info.st_mode)
	{
		if (not)
			return (1);
		return (0); // On success
	}
	return (not_return_last(not));
}

// True if file exists and is a regular file.
static int ft_test_f(char **arg)
{
	struct stat file_info;
	char		*filepath;
	int			not;

	not = is_not(arg);
	filepath = get_file_path(arg, not);
	if (stat(filepath, &file_info) != 0)
	{
		ft_strdel(&filepath);
		// in this case, the file does not exist
		return (not_return_last(not));
	}
	ft_strdel(&filepath);
	if (S_ISREG(file_info.st_mode))
	{
		if (not)
			return (1);
		return (0); // On success
	}
	return (not_return_last(not));
}

// True if file exists (regardless of type).
static int ft_test_e(char **arg)
{
	struct stat file_info;
	char		*filepath;
	int			not;

	not = is_not(arg);
	filepath = get_file_path(arg, not);
	if (stat(filepath, &file_info) != 0)
	{
		ft_strdel(&filepath);
		// in this case, the file does not exist
		return (not_return_last(not));
	}
	ft_strdel(&filepath);
	if (not)
		return (1);
	return (0); // On success
}

// True if file exists and is a directory.
static int ft_test_d(char **arg)
{
	struct stat file_info;
	char		*filepath;
	int			not;

	not = is_not(arg);
	filepath = get_file_path(arg, not);
	if (stat(filepath, &file_info) != 0)
	{
		ft_strdel(&filepath);
		// in this case, the file does not exist
		return (not_return_last(not));
	}
	ft_strdel(&filepath);
	if (S_ISDIR(file_info.st_mode))
	{
		if (not)
			return (1);
		return (0); // On success
	}
	return (not_return_last(not));
}

// True if file exists and is a character special file.
static int ft_test_c(char **arg)
{
	struct stat file_info;
	char		*filepath;
	int			not;

	not = is_not(arg);
	filepath = get_file_path(arg, not);
	if (stat(filepath, &file_info) != 0)
	{
		ft_strdel(&filepath);
		// in this case, the file does not exist
		return (not_return_last(not));
	}
	ft_strdel(&filepath);
	if (S_ISCHR(file_info.st_mode))
	{
		if (not)
			return (1);
		return (0); // On success
	}
	return (not_return_last(not));
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
