#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include<time.h>
#include<stdlib.h>

int megoldo(double a, double b, double c,
                double *x, double *y)
{
  double d;
  int valos;

  valos = 1;
  if (a == 0.0) {
      if (b == 0.0) {
          valos = 0;
      } else {
          *x = -(c / b);
          *y = *x;
      }
  } else {
      d = b * b - 4.0 * a * c;
      if (d < 0.0) {
          valos = 0;
      } else {
          *x = (-b + sqrt(d)) / (2.0 * a);
          *y = (-b - sqrt(d)) / (2.0 * a);
      }
  }
  return valos;
}

int main() {

    int pipefd[2];
    int pipefdmasik[2];
    pid_t cpid;
    int buf;
    int masikbuf;
    int ret;

    if(pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(-1);
    }
    if(pipe(pipefdmasik) == -1)
    {
        perror("pipe");
        exit(-1);
    }

    cpid = fork();
    if(cpid == -1)
    {
        perror("fork");
        exit(-1);
    }



    if(cpid == 0)
    {
        printf("%d: gyerek vagyok\n",getpid());
        double a, b, c;
        printf("Adja meg az egyutthatokat!\n:",getpid());
        scanf("%lf", &a); scanf("%lf", &b); scanf("%lf", &c);

        close(pipefd[0]);

        while (read(pipefd[0], &buf, 1) > 0)
        {
            printf("%d", buf);
        }

        close(pipefd[0]);
        int pid = getpid();
        write(pipefdmasik[1], pid, sizeof(int));

        exit(0);
    }
    else
    {
        close(pipefd[0]);

        int pid=getpid();
        write(pipefd[1], pid, sizeof(int));


        while (read(pipefdmasik[0], &masikbuf, 1) > 0)
        {
		 printf("%d",masikbuf);
        }

        close(pipefd[1]);

        wait(NULL);

        double a, b, c, x, y;
        if(megoldo(a, b, c, &x, &y))
        {
            printf("Az egyenlet megoldasai: %lf, %lf\n", x, y);
        }
        else
        {
            printf("Az egyenletnek nincs valos megoldasa.\n");
        }
        exit(0);
    }
}
