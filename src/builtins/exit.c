/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:32:00 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/02 15:54:23 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Passe tous les espaces blancs et le signe, puis vérifie s'il y a
// autre chose que des chiffres.
static void	only_numeric_or_not(char *cmd_arg, bool *atoi_error)
{
	int	i;

	i = 0;
	if (cmd_arg[i] == '-' || cmd_arg[i] == '+')
		i++;
	while (cmd_arg[i])
	{
		if (!is_white_space(cmd_arg[i]))
			if (cmd_arg[i] < '0' || '9' < cmd_arg[i])
				*atoi_error = true;
		i++;
	}
}

static void	exit_numeric_arg(t_global *global, char **cmd_arg_array)
{
	global->exit_value = 2;
	if (!pipe_inside_token_list(global))
		ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd_arg_array[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit_function(global, false);
}

// Atoi crée pour exit : il permet de convertir le nombre donné en un nombre
// compris entre 0 et 255, car toutes les commandes Linux retournent une
// valeur comprise entre cette plage. (error_value % 256 (+256 si négatif))
static int	atoi_exit(char *cmd_arg, bool *atoi_error)
{
	long long	result;
	int			sign;
	int			i;
	int			j;

	i = 0;
	j = 0;
	result = 0;
	sign = 1;
	while (is_white_space(cmd_arg[i]))
		i++;
	if (cmd_arg[i] == '-' || cmd_arg[i] == '+')
		if (cmd_arg[i++] == '-')
			sign *= -1;
	while (cmd_arg[i] >= '0' && cmd_arg[i] <= '9' && ++j)
		result = (result * 10) + (cmd_arg[i++] - '0');
	while (cmd_arg[i++])
		j++;
	if ((j > 19 && sign == 1) || (j > 20 && sign == -1))
		*atoi_error = true;
	result = (result * sign) % 256;
	if (result < 0)
		result += 256;
	return ((int)result);
}

// Fonction de sortie.
void	exit_function(t_global *global, bool write_exit)
{
	if (write_exit == true)
		ft_printf("exit\n");
	free_all(global);
}

// Provoque l'arrêt du minishell avec un code de retour ($?) égal à n.
// Si n n'est pas précisé, le code de retour fourni est celui
// de la dernière commande exécutée.
void	ft_exit(t_global *global, char **cmd_arg_array)
{
	int		arg_nbr;
	bool	atoi_error;

	arg_nbr = 0;
	atoi_error = false;
	while (cmd_arg_array[arg_nbr])
		arg_nbr++;
	if (arg_nbr == 1)
	{
		if (pipe_inside_token_list(global))
			exit_function(global, false);
	}
	else if (arg_nbr >= 3)
	{
		global->exit_value = 1;
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2));
	}
	else if (arg_nbr == 2)
	{
		only_numeric_or_not(cmd_arg_array[1], &atoi_error);
		global->exit_value = atoi_exit(cmd_arg_array[1], &atoi_error);
		if (atoi_error == true)
			exit_numeric_arg(global, cmd_arg_array);
	}
	exit_function(global, true);
}
