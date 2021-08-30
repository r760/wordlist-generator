#include <stdio.h>

void man() {
  printf("Use: ./wordlistGenerator -o OUT -min MIN -max MAX [at least one of: "
         "-d -l "
         "-L -s -a] \n\n");

  printf("A simple wordlist generator written in C.\n\n");

  printf("required arguments:\n\n");
  printf("\t-o OUT \n\t\t write generated wordlist to a file named OUT\n");
  printf("\t-min MIN \n\t\t set minimum word length to MIN (MIN must be "
         "greater or equal 1)\n");
  printf("\t-max MAX \n\t\t set maximum word length to MAX (MAX must be "
         "greater or equal 1)\n\n");
  printf("\tNote: \n\t\t to set the word length to exactly n");
  printf(", use: ./wordlistGenerator -o OUT -min n -max n\n");
  printf("\t\t to set the word length from n to m (m must be greater or equal "
         "n),\n");
  printf("\t\t use: ./wordlistGenerator -o OUT -min n -max m\n\n");

  printf("semi-required argument(s) (choose at least one):\n\n");
  printf("\t-d \n\t\t append [0-9] to the alphabet\n");
  printf("\t\t Use: ./wordlistGenerator -o OUT -min MIN -max MAX -d\n");

  printf("\t-l \n\t\t append [a-z] to the alphabet\n");
  printf("\t\t Use: ./wordlistGenerator -o OUT -min MIN -max MAX -l\n");

  printf("\t-L \n\t\t append [A-Z] to the alphabet\n");
  printf("\t\t Use: ./wordlistGenerator -o OUT -min MIN -max MAX -L\n");

  printf("\t-s \n\t\t append [space] to the alphabet\n");
  printf("\t\t Use: ./wordlistGenerator -o OUT -min MIN -max MAX -s\n\n");

  printf("\t-a APPEND \n\t\t append APPEND to the alphabet");
  printf(", note you need to escape special characters\n");
  printf(
      "\t\t Use: ./wordlistGenerator -o OUT -min MIN -max MAX -a APPEND\n\n");
}