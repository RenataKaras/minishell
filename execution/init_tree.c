/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_tree.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/20 17:14:01 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/09/24 16:15:40 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Pipes (|) are processed left-to-right (send output from left to right).
//Heredoc (<<) typically applies to the right-hand command,
//cmd1 | cmd2 << heredoc, here, cmd1 writes its output to cmd2 by the pipe.
//and The heredoc provides data to cmd2
//In (AST), cmd1 is on the left side of the tree (because it's executed first)
//and cmd2 is on the right (because it receives data from cmd1)
//When there's heredoc, it affects the right side (i.e., cmd2).
//So the tree processes the right-hand side when the heredoc isn't initialized
//to ensure that cmd2 properly receives input from the heredoc 
//INSTEAD OF from cmd1's pipe.
//while it’s not mandatory to place the command affected by heredoc on the right
//the design conventionally puts it there for consistency with other operators.
//so if heredoc_siginit is not initialized, we do it

// static void	init_leaf(t_data *data)
// {
	
// }
void	init_tree(t_node *node, t_data *data)
{
	if (!node)
		return ;
	if (data->ast->type == N_PIPE)
	{
		init_tree(data ->ast -> left);
		if (!data->heredoc_siginit)
			init_tree(data-> ast -> right);
	}
	else
		init_leaf(data);
}
