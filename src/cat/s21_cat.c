#include "s21_cat.h"

int main(int argc, char *argv[]) {
  struct flags_cat flag;
  init_flag(&flag);
  if (argc > 1) {
    if (!flags(argc, argv, &flag)) {
      if (flag.fl_t == 1 || flag.fl_e == 1) flag.fl_v = 1;
      if (flag.fl_b == 1) flag.fl_n = 0;
      last_linking(argc, argv, &flag);
    }
  } else {
    printf("no arg");
  }
  return 1;
}

void init_flag(struct flags_cat *flag) {
  flag->fl_b = 0;
  flag->fl_e = 0;
  flag->fl_n = 0;
  flag->fl_s = 0;
  flag->fl_t = 0;
  flag->fl_E = 0;
  flag->fl_T = 0;
  flag->fl_v = 0;
}

void flag_v(int *ch) {
  if ((*ch >= 0 && *ch <= 31 && *ch != 9 && *ch != 10)) {
    *ch += 64;
    printf("^");
  } else if (*ch == 127) {
    *ch -= 64;
    printf("^");
  }
}

void last_linking(int argc, char *argv[], struct flags_cat *flag) {
  int symbol;
  char up = '\n';
  unsigned int empty_str = 0;
  FILE *mp;
  for (int a = 1; a < argc; a++) {
    if (argv[a][0] != '-') {
      mp = fopen(argv[a], "r");
      // int i = 1;
      if (mp == NULL) {
        fprintf(stderr, "s21_cat: %s: No such file or directory\n", argv[a]);
      } else {
        int i = 1;
        while ((symbol = fgetc(mp)) != EOF) {
          if ((flag->fl_s == 1 && symbol == '\n') &&
              (up == '\n' || up == '\0')) {
            empty_str++;
            if (empty_str > 1) continue;
          } else {
            empty_str = 0;
          }
          if ((flag->fl_b == 1 && symbol != '\n' && up == '\n') ||
              (flag->fl_n == 1 && up == '\n' && flag->fl_b != 1)) {
            printf("%6d\t", i++);
          }
          if (flag->fl_e == 1 && symbol == '\n') {
            putchar('$');
          }
          if (flag->fl_t == 1 && symbol == '\t') {
            putchar('^');
            symbol = 'I';
          }
          if (flag->fl_E == 1 && symbol == '\n') {
            putchar('$');
          }
          if (flag->fl_t == 1 && symbol == '\t') {
            putchar('^');
            symbol = 'I';
          }
          if (flag->fl_v == 1 && symbol != '\n') {
            flag_v(&symbol);
          }
          up = symbol;
          putchar(symbol);
        }
        fclose(mp);
      }
    }
  }
}

int flags(int argc, char *argv[], struct flags_cat *flag) {
  int error = 0;
  for (int i = 1; i < argc; i++) {
    int j = 1;
    if (argv[i][0] == '-' && argv[i][1] != '-') {
      while (argv[i][j] != '\0') {
        // printf("%c", argv[i][j + 1]);
        switch (argv[i][j]) {
          case 'b':
            flag->fl_b = 1;
            break;
          case 'e':
            flag->fl_e = 1;
            break;
          case 'n':
            flag->fl_n = 1;
            break;
          case 's':
            flag->fl_s = 1;
            break;
          case 't':
            flag->fl_t = 1;
            break;
          case 'T':
            flag->fl_t = 1;
            break;
          case 'E':
            flag->fl_e = 1;
            break;
          case 'v':
            flag->fl_v = 1;
            break;
          default:
            fprintf(stderr,
                    "cat: illegal option -- |%c|\n"
                    "usage: cat [-benstuv] [file ...]\n",
                    argv[i][j]);
            error = 1;
            break;
        }
        j++;
      }
    } else if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] != '-') {
      if (strcmp(argv[i], "--number-nonblank") == 0)
        flag->fl_b = 1;
      else if (strcmp(argv[i], "--number") == 0)
        flag->fl_n = 1;
      else if (strcmp(argv[i], "--squeeze-blank") == 0)
        flag->fl_s = 1;
    } else if (argv[j][0] == '-' && argv[j][1] == '-' && argv[j][2] == '-') {
      fprintf(stderr,
              "cat: illegal option -- -\nusage: cat [-benstuv] [file ...]\n");
      error = 1;
    }
  }
  return error;
}
