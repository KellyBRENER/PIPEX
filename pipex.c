int main(int argc, char **argv, char **env)
{
	if (argc != 5)
	{
		write(1, "incorrect argument count", 24);
		return 1;
	}
	if (pipex(argv, env) == -1)
		return 1;
	return (0);
}
