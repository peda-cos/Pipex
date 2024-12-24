/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:14:53 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/24 16:14:55 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(int fd_in1, int fd_in2, int fd_out1, int fd_out2)
{
	close(fd_in1);
	close(fd_in2);
	close(fd_out1);
	close(fd_out2);
}

void	execute_command(char *command, int fd_in, int fd_out, char **envp)
{
	char	**cmd_parts;
	char	*command_path;

	if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(fd_out, STDOUT_FILENO) == -1)
		perror("Error ");
	close(fd_in);
	close(fd_out);
	cmd_parts = ft_split(command, ' ');
	if (!cmd_parts)
	{
		perror("Error ");
		exit(EXIT_FAILURE);
	}
	command_path = resolve_command_path(envp, cmd_parts[0], command);
	execve(command_path, cmd_parts, envp);
	perror("Error ");
	free(command_path);
	ft_free_split(cmd_parts);
	exit(EXIT_FAILURE);
}

pid_t	create_pipe(int fd_in, int fd_out, char **args, char **envp)
{
	int		pipe_ends[2];
	pid_t	child_pid[2];

	if (pipe(pipe_ends) == -1)
		return (-1);
	child_pid[0] = fork();
	if (child_pid[0] == -1)
		return (-1);
	if (child_pid[0] == 0)
	{
		close(pipe_ends[0]);
		execute_command(args[2], fd_in, pipe_ends[1], envp);
	}
	child_pid[1] = fork();
	if (child_pid[1] == -1)
		return (-1);
	if (child_pid[1] == 0)
	{
		close(pipe_ends[1]);
		execute_command(args[3], pipe_ends[0], fd_out, envp);
	}
	close_fds(fd_in, fd_out, pipe_ends[0], pipe_ends[1]);
	waitpid(child_pid[0], NULL, 0);
	waitpid(child_pid[1], NULL, 0);
	return (0);
}
