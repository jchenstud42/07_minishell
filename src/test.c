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

// Utilise dup2 pour dupliquer le fd de la sortie standard,
// et pouvoir utiliser printf dans notre fichier_fd directement
void	dup2_example(void)
{
	int	fichier_fd;

	fichier_fd = open("text1.txt", O_WRONLY);
	dup2(fichier_fd, STDOUT_FILENO);
	printf("Mwehehehehehehe\n");
	close(fichier_fd);
}

// Utilise execve pour remplacer le processus par la commande "ls -l"
// On peut utiliser differentes combinaisons de commandes
void	execve_example(void)
{
	const char	*path = "/usr/bin/ls";
	char		*envp[] = {NULL};
	char		*av[] = {"/usr/bin/ls", "-l", NULL};

	execve(path, av, envp);
}

// // On peut aussi utiliser execve directement dans le main
// int	main(int ac, char **av, char **envp)
// {
// 	char	*file_path;

// 	(void)ac;
// 	file_path = "/usr/bin/echo";
// 	execve(file_path, av, envp);
// }

// Lorsque fork() est appele, il renvoie une valeur differente :
// Parent : pid contient le PID de l'enfant
// Enfant : pid sera 0
void	fork_example(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
		printf("Je suis le child %d\n", getpid());
	else
		printf("Je suis le parent %d et j'ai cree l'enfant %d\n", getpid(),
			pid);
}

void	pipe_example(void)
{
	int		pipefd[2];
	pid_t	pid;
	char	buffer[100];
	char	*message;

	message = "Bonjour mon enfant.";
	pipe(pipefd);
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		close(pipefd[1]);
		read(pipefd[0], buffer, sizeof(buffer));
		printf("Aujourd'hui, parent m'a dit : %s\n", buffer);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		write(pipefd[1], message, strlen(message) + 1);
		close(pipefd[1]);
	}
}

// Utilise access() pour vérifier si le fichier text1.txt existe
// Si c’est le cas, supprime le fichier.
void	unlink_example(void)
{
	if (access("text1.txt", F_OK) == 0)
		unlink("text1.txt");
}

void	wait_example(void)
{
	int	status;
	int	n;

	n = 0;
	// waiting for one child
	wait(&status);
	// waiting for multiple children
	while (n > 0)
	{
		wait(&status);
		n--;
	}
}

// Attend que le processus child change de status
void	waitpid_example(void)
{
	int	status;
	int	pid;

	pid = fork();
	waitpid(pid, &status, 0);
}

// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)**av;
// readline_example();
// getcwd_example();
// chdir_example();
// opendir_example();
// getenv_example();
// more_elaborate_readline_example(env);
// dup2_example();
// execve_example();
// fork_example();
// unlink_example();
// wait_example();
// pipe_example();
// }
