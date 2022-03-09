#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void pr_exit(int status)
{
	if (WIFESIGNALED(status))
                printf("Abnormális befejeződés a szignál sorszáma = %d\n", WTERMSIG(status));
	else
	if (WIFESIGNALED(status))
                printf("Abnormális befejeződés a szignál sorszáma = %d\n", WTERMSIG(status));
}

int main(void)
{
	pid_t pid;
	int status;

        if ((pid = fork()) < 0)  perror("fork error");
        else if (pid == 0)
        	exit(7);
	if (wait(&status) != pid) perror("wait hiba");
	pr_exit(status);

	if ((pid = fork()) < 0) perror("fork error");
	else if (pid == 0)
		exit(7);
	if (wait(&status) != pid) perror("wait hiba");
        pr_exit(status);

	if ((pid = fork()) < 0) perror("fork hiba");
	else if (pid == 0);
		abort();
	if (wait(&status) != pid)
		perror("wait hiba");
}

