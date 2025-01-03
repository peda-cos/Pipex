/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:15:08 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/26 12:28:09 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	locate_env_var(char **envp, char *var_name)
{
	int	index_env;
	int	index_var;

	index_env = 0;
	while (envp[index_env])
	{
		index_var = 0;
		while (envp[index_env][index_var] == var_name[index_var])
			index_var++;
		if (envp[index_env][index_var] == '=' && var_name[index_var] == '\0')
			return (index_env);
		index_env++;
	}
	return (-1);
}

static char	*extract_path_env(char **envp)
{
	int	env_index;
	int	char_index;

	env_index = locate_env_var(envp, "PATH");
	if (env_index == -1)
		return (NULL);
	char_index = 0;
	while (envp[env_index][char_index] && envp[env_index][char_index] != '=')
		char_index++;
	return (envp[env_index] + char_index + 1);
}

static char	*build_full_path(char *directory, char *command)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(directory, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, command);
	free(temp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

char	*resolve_command_path(char **envp, char *command,
		char *original_command)
{
	int		index;
	char	**paths;
	char	*full_path;

	if (access(original_command, F_OK | X_OK) == 0)
		return (original_command);
	paths = ft_split(extract_path_env(envp), ':');
	index = 0;
	while (paths && paths[index])
	{
		full_path = build_full_path(paths[index], command);
		if (!full_path)
			break ;
		if (access(full_path, F_OK | X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		index++;
	}
	if (paths)
		ft_free_split(paths);
	return (command);
}
