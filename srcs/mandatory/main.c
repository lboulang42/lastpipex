/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:03:21 by lboulang          #+#    #+#             */
/*   Updated: 2023/06/26 18:40:35 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
			MANDATORY
Votre programme sera exécuté comme suit :
	./pipex file1 cmd1 cmd2 file2
• file1 et file2 sont des noms de fichier.
• cmd1 et cmd2 sont des commandes shell avec leurs paramètres.
Votre programme doit se comporter exactement comme la commande shell suivante :
	< file1 cmd1 | cmd2 > file2
*/
/*
			EXEMPLES
'./pipex infile "ls -l" "wc -l" outfile'
Devrait être identique à < infile ls -l | wc -l > outfile

'./pipex infile "grep a1" "wc -w" outfile'
Devrait être identique à < infile grep a1 | wc -w > outfile
*/
int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac < 5)
		return (ft_printf("%s %s\n", ERR_SYNTX, av[ac - 1]), 1);
	if (ac > 5)
		return (ft_printf("Pipex : Mandatory only support 2 commands\n"), 1);
	pipex.env_path = ft_get_env_path(env);
	ft_exec(&pipex, ac, av, env);
	ft_free_tab((void **)pipex.env_path);
	return (pipex.exit_code);
}
