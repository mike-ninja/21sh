/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:31:36 by jakken            #+#    #+#             */
/*   Updated: 2022/11/27 20:01:26 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	ft_memd_w(void **ap)
{
	if (!ap || !(*ap))
		return (1);
	ft_memdel(ap);
	return (1);
}

static int	ft_freeda_w(void ***a, size_t row)
{
	ft_freeda(a, row);
	return (1);
}

static int	try_cmd(char *cmd, char **environ_cp, char **temp_path)
{
	if (!access(cmd, F_OK) && !access(cmd, X_OK))
		return (1);
	// JUST TO COMPILE:
	if (environ_cp && temp_path)
		return (0);
	//REPLACE OR MERGE
	//*temp_path = search_variable(environ_cp, "PATH");
	return (0);
}

char	*search_bin(char *cmd, char **environ_cp)
{
	char	**bin_paths;
	char	*temp_path;
	char	*exepath;
	int		i;

	i = 0;
	if (try_cmd(cmd, environ_cp, &temp_path))
		return (ft_strdup(cmd));
	bin_paths = NULL;
	if (temp_path)
		bin_paths = ft_strsplit(temp_path, ':');
	while (ft_memd_w((void **)&temp_path) && bin_paths && bin_paths[i])
	{
		temp_path = ft_strjoin(bin_paths[i], "/");
		exepath = ft_strjoin(temp_path, cmd);
		if (ft_memd_w((void **)&temp_path) && !access(exepath, F_OK)
			&& !access(exepath, X_OK)
			&& ft_freeda_w((void ***)&bin_paths, calc_chptr(bin_paths)))
			return (exepath);
		else
			ft_memdel((void **)&exepath);
		++i;
	}
	ft_freeda((void ***)&bin_paths, calc_chptr(bin_paths));
	return (NULL);
}
