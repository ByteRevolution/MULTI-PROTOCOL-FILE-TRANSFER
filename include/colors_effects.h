#ifndef COLORS_H
#define COLORS_H
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

#define BOLD      "\x1b[1m"
#define UNDERLINE "\x1b[4m"
#define RESET     "\x1b[0m"

#define PRINT_BOLD(msg)      printf(BOLD "%s" RESET, msg)
#define PRINT_UNDERLINE(msg) printf(UNDERLINE "%s" RESET, msg)
#endif 
