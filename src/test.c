#include "../inc/minishell.h"

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

// Replique vite fait la commande ls
int	opendir_example(void)
{
	DIR				*dir;
	struct dirent	*entry;
	const char		*actual_directory = ".";

	dir = opendir(actual_directory);
	if (dir == NULL)
	{
		perror("opendir");
		return (1);
	}
	// struct dirent *entry :
	// Struct qui stocke le numero d'inode (ID unique pour chaque fichier)
	// et le nom du fichier/sous-repertoire
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
			ft_printf("%s ", entry->d_name);
	}
	closedir(dir);
	ft_printf("\n");
	return (0);
}

// Replique la commande env (vite fait)
int	getenv_example(void)
{
	const char	*home;

	home = getenv("HOME");
	if (!home)
		return (1);
	printf("HOME=%s\n", home);
	return (0);
}

// Replique MIEUX la commande env, en prenant en parametre env
int	getenv_false_example(char **env)
{
	char	**print_env;

	print_env = env;
	while (*print_env)
	{
		ft_printf("%s\n", *print_env);
		print_env++;
	}
	return (0);
}

// affiche le terminal tout en printant le texte
// insere dans le terminal, jusqu'a ce qu'on quitte
// en inserant "exit" ou "Ctrl + D"
int	more_elaborate_readline_example(char **env)
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
		else if (ft_strcmp(input, "ls") == 0)
			opendir_example();
		else if (ft_strcmp(input, "env") == 0)
			// getenv_example();
			getenv_false_example(env);
		else
			ft_printf("%s\n", input);
		add_history(input);
		free(input);
	}
	rl_clear_history();
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)**av;
	// readline_example();
	// getcwd_example();
	// chdir_example();
	// opendir_example();
	// getenv_example();
	more_elaborate_readline_example(env);
}
