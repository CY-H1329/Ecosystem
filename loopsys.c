#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

int main(){
  for(int i = 0; i < 500000; i++){
    getpid();
  }
  return 0;
}
