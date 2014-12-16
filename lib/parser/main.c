#include <stdio.h>
#include <stdlib.h>
#include "fx_parse.h"


int main(int argc, char *argv[]) {
  printf("\nFauxy -> Go!\n\n");

  int status = 0;
  while(status == 0) {
    status = parse_stdin();
    printf("\n\n");
  }

  return status;
}
