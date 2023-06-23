/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:03:21 by lboulang          #+#    #+#             */
/*   Updated: 2023/06/23 09:10:35 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*BONUS*/
// 1) Gérez plusieurs pipes.
// 		./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
// 		Devrait être identique à :
// 		< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
// 2) Gérez « et » quand le premier paramètre est "here_doc"
//  	./pipex here_doc LIMITER cmd cmd1 file
//  	Devrait être identique à :
//  	cmd << LIMITER | cmd1 >> file

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac < 5)
		return (ft_printf("syntax error near unexpected token: %s", av[ac -1]));
	pipex.env_path = ft_get_env_path(env);
	ft_exec(&pipex, ac, av, env);
	ft_free_tab((void **)pipex.env_path);
}
