#include "minishell.h"

int chrtabtab(char **res, char *str)
{
	int i;

	i = 0;
	while (res[i])
	{
		if (ft_strcmp(res[i], str) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char **divide_pipe(char **res, t_fd *f)
{
	int m;
	int i;
	char **tabl;

	i = 0;
	m = count_tabs(res) - chrtabtab(res, "|");
	if (!(f->save_pipe = malloc(sizeof(char *) * (m + 2))))
		return NULL;
	if (!(tabl = malloc(sizeof(char *) * (chrtabtab(res, "|") + 2))))
		return (NULL);
	while (i < chrtabtab(res, "|"))
	{
		tabl[i] = ft_strdup(res[i]);
		i++;
	}
	tabl[i] = NULL;
	i = 0;
	while (res[chrtabtab(res, "|") + i + 1])
	{
		f->save_pipe[i] = ft_strdup(res[chrtabtab(res, "|") + i + 1]);
		i++;
	}
	f->save_pipe[i] = NULL;
	return (tabl);
}

int go_e(char **tabl, t_list *var_env, t_command *cmd)
{
	if (ft_strcmp(tabl[0], "echo") == 0)
		ft_echo(tabl, var_env);
	else if (ft_strcmp(tabl[0], "export") == 0 && tabl[1])
	{
		check_doublons_cl(tabl);
		set_env(tabl, var_env, cmd);
	}
	else if (ft_strcmp(tabl[0], "export") == 0 && tabl[1])
		errors(cmd);
	else if (ft_strcmp(tabl[0], "export") == 0 && (!(tabl[1])))
		print_sorted_env(var_env);
	else if (ft_strcmp(tabl[0], "env") == 0)
		print_env(var_env);
}

int go_instruction(char **tabl, t_list *var_env, t_command *cmd, char **env)
{
	int sig;

	sig = 0;
	if (tabl[0][0] == 'e')
		go_e(tabl, var_env, cmd);
	else if (ft_strcmp(tabl[0], "pwd") == 0)
		ft_pwd(tabl);
	else if (ft_strcmp(tabl[0], "cd") == 0)
		ft_cd(tabl);
	else if (tabl[0][0] == '.' && tabl[0][1] == '/')
		find_exe(tabl[0], env, cmd);
	else if (ft_strcmp(tabl[0], "unset") == 0 && tabl[1])
		unset(var_env, tabl);
	else if (ft_strcmp(tabl[0], "unset") == 0)
		errors(cmd);
	else if (ft_strcmp(tabl[0], "$?") == 0)
		printf("%d : Command not found\n", cmd->cmd_rv);
	else
		set_args(tabl, cmd->path, cmd);
	if (sig == 1)
		cmd->cmd_rv = 130;
	if (sig == 2)
		cmd->cmd_rv = 131;
	if (sig == 1 || sig == 2)
		sig = 0;
	return (0);
}

//marche pas avec redirs, a traiter
//atterntion prompt affiche avec pipe

int go_pipe(char **res, t_fd *f, t_list *var_env, t_command *cmd, char **env)
{
	char	**one;
	pid_t	pid;
	int		pipe_fd[2];

	one = divide_pipe(res, f);
	pipe(pipe_fd);
	if ((pid = fork()) == -1)
		return -1;
	else if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		go_instruction(end_redir(one, f), var_env, cmd, env);
		close(pipe_fd[1]);
		return 1;
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		go_instruction(end_redir(f->save_pipe, f), var_env, cmd, env);
		close(pipe_fd[0]);
	}
}

int redir_and_send(char **res, t_fd *f, t_list *var_env, t_command *cmd, char **env)
{
	if (chrtabtab(res, "|") == -1 && chrtabtab(res, ">") == -1 && chrtabtab(res, "<") == -1 && chrtabtab(res, ">>") == -1)
		return (go_instruction(res, var_env, cmd, env));
	else if (chrtabtab(res, "|") == -1)
		return (go_instruction(end_redir(res, f), var_env, cmd, env));
	else
	{
		// if (count_pipes(res) == 1)
			return (go_pipe(res, f, var_env, cmd, env));
		// else
		//     return (multiple_pipes(res, f));
	}
}