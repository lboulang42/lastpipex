/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:03:21 by lboulang          #+#    #+#             */
/*   Updated: 2023/06/23 09:58:25 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*MANDATORY*/
// Votre programme sera exécuté comme suit :
// 	./pipex file1 cmd1 cmd2 file2
// • file1 et file2 sont des noms de fichier.
// • cmd1 et cmd2 sont des commandes shell avec leurs paramètres.
// Votre programme doit se comporter exactement comme la commande shell suivante :
// 	< file1 cmd1 | cmd2 > file2

/*EXEMPLES*/
// ./pipex infile "ls -l" "wc -l" outfile
// Devrait être identique à < infile ls -l | wc -l > outfile
// ./pipex infile "grep a1" "wc -w" outfile
// Devrait être identique à < infile grep a1 | wc -w > outfile

/*
Notes : 
Moins de 5 args : Print "Pipex error, must be executed as ./pipex file1 cmd1 cm2 file2"
tous les errors messages commencent par "pipex : "
file existe pas : "name: no such file or directory\n"
command existe pas : "cmdname: command not found\n"

Must be tested : 
Less 5 args
5 invalid args
Infile error
First command error -> resulat de la 2e command lancée sur vide dans outfile
First command with invalid flags
Last command with invalid flags
Last command error -> outfile créé et vide
outfile already exist `touch outfile && < Makefile cat | wc -l >` (fonctionnement habituel)
*/
int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac < 5)
		return (ft_printf("Pipex syntax error\n"));
		// return (ft_printf("syntax error near unexpected token: %s", av[ac -1]));
	pipex.env_path = ft_get_env_path(env);
	ft_exec(&pipex, ac, av, env);
	ft_free_tab((void **)pipex.env_path);
}
