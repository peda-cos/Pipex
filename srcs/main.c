/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 07:28:31 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/24 15:03:55 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	file_in;
	int	file_out;

	if (argc != 5)
	{
		write(2, "Usage: pipex <FILE_IN> <CMD1> <CMD2> <FILE_OUT>\n", 48);
		exit(EXIT_FAILURE);
	}
	file_in = open(argv[1], O_RDONLY);
	if (file_in == -1)
	{
		perror("Error ");
		exit(EXIT_FAILURE);
	}
	file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_out == -1)
	{
		perror("Error ");
		close(file_in);
		exit(EXIT_FAILURE);
	}
	create_pipe(file_in, file_out, argv, envp);
	close(file_in);
	close(file_out);
	return (0);
}
