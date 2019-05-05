void emptycall()
{
	printf("Signal SIGTTOU catched\n");
}

void CurrentProcToBackground(char *workingPath)
{
	pid_t pid;
  
	if( (pid = fork()))
		exit(0);
	else if( pid < 0 )
	{
    		printf("Fork Error: %s\n", strerror(errno) );
		exit(1);
	}

	setsid();
	if( (pid = fork()) )
		exit(0);
	else if( pid < 0 )
	{
    		printf("Fork Error: %s\n", strerror(errno) );
		exit(2);
	}

	chdir(workingPath);
	umask(0);

	signal(SIGTTOU, emptycall);
	signal(SIGCHLD, SIG_IGN);	
}
