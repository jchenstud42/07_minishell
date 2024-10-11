#include "../inc/minishell.h"

// ???? Je vois pas trop d'utilite, ca n'ajoute rien a readline()
int	rl_on_new_line_example(void)
{
	char	*input;

	input = readline("Prompt > ");
	if (input)
	{
		if (input == NULL || ft_strcmp(input, "exit") == 0)
		{
			ft_printf("exit");
			free(input);
			return (0);
		}
		ft_printf("%s\n", input);
		rl_on_new_line();
		free(input);
	}
	return (0);
}

// Affiche le prompt, puis print le texte insere dans le terminal
int	readline_example(void)
{
	char	*input;

	input = readline("Prompt > ");
	printf("%s\n", input);
	free(input);
	return (0);
}

// Replique la commande pwd
int	getcwd_example(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
		ft_printf("%s\n", pwd);
	else
	{
		ft_printf("error\n");
		free(pwd);
		return (1);
	}
	free(pwd);
	return (0);
}

// Replique la commande cd
int	chdir_example(void)
{
	if (chdir("../") != 0)
		ft_printf("Ca ne marche qu'avec <cd ..> pour le moment..!\n");
	return (0);
}

// affiche le terminal tout en printant le texte
// insere dans le terminal, jusqu'a ce qu'on quitte
// en inserant exit ou Ctrl + D
int	more_elaborate_readline_example(void)
{
	char	*input;

	while (1)
	{
		input = readline("Minishell > ");
		if (input == NULL || ft_strcmp(input, "exit") == 0)
		{
			ft_printf("exit");
			free(input);
			break ;
		}
		else if (ft_strcmp(input, "pwd") == 0)
			getcwd_example();
		else if (ft_strcmp(input, "cd ..") == 0)
			chdir_example();
		else
			ft_printf("%s\n", input);
		add_history(input);
		free(input);
	}
	rl_clear_history();
	return (0);
}

int	main(void)
{
	// rl_on_new_line_example();
	// readline_example();
	// getcwd_example();
	// chdir_example();
	more_elaborate_readline_example();
}
