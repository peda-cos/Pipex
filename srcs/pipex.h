/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 07:28:54 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/26 00:34:57 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

char	**ft_split(const char *s, char c);
void	ft_free_split(char **split);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);

char	*resolve_command_path(char **envp, char *command,
			char *original_command);

void	close_fds(int fd_in1, int fd_in2, int fd_out1, int fd_out2);
void	execute_command(char *command, int fd_in, int fd_out, char **envp);
pid_t	create_pipe(int fd_in, int fd_out, char **args, char **envp);

int		main(int argc, char **argv, char **envp);

#endif
