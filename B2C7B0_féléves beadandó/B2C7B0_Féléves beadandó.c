#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

int megoldo(double a, double b, double c,                       /* egy�tthat�k */
                double *x, double *y)                         /* gy�k�k */
{
  double d;                                                     /* a diszkrimin�ns */
  int valos;                                                    /* van-e megold�s */

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

    printf("Megnyit�s...\n");
    printf("Megnyitva\n");

	double a, b, c, x, y;
	printf("Adja meg az egyutthatokat!\n:");
	scanf("%lf", &a); scanf("%lf", &b); scanf("%lf", &c);
	if(megoldo(a, b, c, &x, &y))
		printf("Az egyenlet megoldasai: %lf, %lf\n", x, y);
	else
		printf("Az egyenletnek nincs valos megoldasa.\n");


    printf("Meg�rva\n");
	printf("Bez�rva\n");
	return 0;
}

