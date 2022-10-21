#include <time.h>
#include <math.h>

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#define TICK ((double)sysconf(_SC_CLK_TCK))

void lance_commande(char * commande){
  if (system(commande) == -1) {
    printf("Erreur systeme\n");
    exit(0);
  }
  return;
}

void statistiques(char * commande){
  clock_t st_time;
  clock_t en_time;
  struct tms st_cpu;
  struct tms en_cpu;

  st_time = times(&st_cpu);
  printf("st time : %f\n", st_time);

  if (system(commande) == -1) {
    printf("Erreur systeme\n");
    exit(0);
  }

  en_time = times(&en_cpu);
  printf("en time : %f\n", en_time);

  double time_spent = (double)(en_time - st_time) / TICK;

  printf("Statistiques de : %s\n", commande);
  printf("Temps total : %f\n", time_spent);
  printf("Temps utilisateur : %f\n", (double)((en_cpu.tms_utime - st_cpu.tms_utime)/ TICK));
  printf("Temps systeme : %f\n", (double)((en_cpu.tms_stime - st_cpu.tms_stime)/ TICK));
  printf("Temps utilisateur fils : %f\n", (double)((en_cpu.tms_cutime - st_cpu.tms_cutime)/ TICK));
  printf("Temps systeme fils : %f\n", (double)((en_cpu.tms_cstime - st_cpu.tms_cstime)/ TICK));
  return;
}

clock_t start_time;

clock_t get_user_ticks()
{
    struct tms t;
    times(&t);
    return t.tms_utime;
}

void start_stopwatch()
{
    start_time = get_user_ticks();
}

void stop_stopwatch()
{
    clock_t stop_time = get_user_ticks();
    double ticks = stop_time - start_time;
    double s = ticks / sysconf(_SC_CLK_TCK);
    printf("elapsed time: %fs\n", s);
}


int main(int argc, char* argv[]){
  struct timeval start, end;
  if (argc < 2){
    printf("Erreur argument\n");
    exit(0);
  }
  /*
  for(int i=1; i<argc; i++){
    gettimeofday(&start, NULL);
    lance_commande(argv[i]);
    gettimeofday(&end, NULL);
    printf("lance_commande(%d)  time spent: %0.8f sec\n",
    argv[i], time_diff(&start, &end));
  }
  */
/*
  for(int i=1; i<argc; i++){
    start_stopwatch();
    system(argv[i]);
    stop_stopwatch();
  }
*/

  for(int i=1; i<argc; i++){

    statistiques(argv[i]);

  }


  return 0;
}

//   ./mytimes "sleep 5" "sleep 10"

//  ./mytimes "ls -l" "./loopsys"
