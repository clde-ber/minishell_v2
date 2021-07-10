void	prep_fds(t_mp *mp, t_fd *f, int *test)
{
	ft_putstr_fd("ok", 2);
	if (mp->count == 0)
	{
		close(test[0]);
		dup2(test[1], 1);
	}
	else if (mp->count == count_pipes(f->res) + 1)
		dup2(test[(mp->count -1) * 2], 0);
	else
	{
		dup2(test[(mp->count - 1) * 2], 0);
		dup2(test[((mp->count - 1) * 2) + 3], 1);
		close(test[((mp->count - 1) * 2) + 1]);
		close(test[((mp->count - 1) * 2) + 2]);
	}
}

void	parent_process_mult(t_mp *mp, int count, t_fd *f, int *test)
{
	if (mp->count == 0)
		close(mp->fd[1]);
	else if (mp->count == count_pipes(f->res) + 1)
		close(test[(mp->count -1) * 2]);
	else
	{
		close(test[(mp->count - 1) * 2]);
		close(test[((mp->count - 1) * 2) + 3]);
	}
	// mp->fdd = mp->fd[0];
	mp->count++;
	if (mp->count == count)
	{
		while (wait(NULL) >= 0)
			;
	}
}

int	handle_multipipes(t_fd *f, t_list *var_env, t_command *cmd, char **env)
{
	t_mp	mp[1];
	int *test;

	init_mp(mp, 0, f);
	pipe(mp->fd);
	int i = 0;
	test = malloc(sizeof(int) * (count_pipes(f->res) * 2));
	while (i < count_pipes(f->res))
	{
		pipe(test + (i * 2));
		i++;
	}
	mp->fdd = mp->fd[0];
	while (mp->count <= count_pipes(f->res) + 1)
	{
		mp->pid = fork();
		if (mp->pid == -1)
			return (0);
		else if (mp->pid == 0)
		{
			prep_fds(mp, f, test);
			go_instruction(end_redir(middle_pipe(f->res, mp->count), f),
				var_env, cmd, env);
			exit(mp->status);
		}
		else
		{
			if (WIFSIGNALED(mp->status) && g_sig.boolean != -1)
				g_sig.boolean++;
			waitpid(mp->pid, &mp->status, 1);
			parent_process_mult(mp, count_pipes(f->res) + 1, f, test);
		}
	}
	return (0);
}