#include <stdio.h>

int main(void) {
  int num;
  char buf[256];
  while (!feof(stdin)) {
    num = fread(&buf,1,256,stdin);
    printf("%d\n",num);
  }
  
  return(0);
}
