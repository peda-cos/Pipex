/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 07:28:31 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/25 22:12:37 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_input_error(const char *out_file)
{
	int	file_out;

	perror("Error: cannot read input file");
	file_out = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_out == -1)
	{
		perror("Error: cannot open/create output file");
		exit(EXIT_FAILURE);
	}
	close(file_out);
	exit(EXIT_FAILURE);
}

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
		handle_input_error(argv[4]);
	file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_out == -1)
	{
		perror("Error: cannot open/create output file");
		close(file_in);
		exit(EXIT_FAILURE);
	}
	create_pipe(file_in, file_out, argv, envp);
	close(file_in);
	close(file_out);
	return (0);
}
