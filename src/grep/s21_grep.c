#include "s21_grep.h"

int main(int argc, char *argv[]) {
  int res;
  char pattern[99999];
  flg_t flg = {};
  // memset(&flg, 0, sizeof(flg));  // инициализирование флагов
  res = parser(argc, argv, &flg, pattern);  // парсинг всех флагов
  if (argc >= 3 &&
      res != 1) {  // проверка на корректность количества переменных в грепе
    grepping(argc, argv, &flg, pattern);  // начало обработки
  }
  return res;
}

int parser(int argc, char **argv, flg_t *flg, char *pattern) {
  int c = 0, res = 0;
  while ((c = getopt(argc, argv, "e:ivclnhsof:")) != -1) {
    switch (c) {
      case 'e': {
        flg->e = 1;
        sprintf(pattern, "%s", optarg);
        break;
      }
      case 'i': {
        flg->i = 1;
        break;
      }
      case 'v': {
        flg->v = 1;
        break;
      }
      case 'c': {
        flg->c = 1;
        break;
      }
      case 'l': {
        flg->l = 1;
        break;
      }
      case 'n': {
        flg->n = 1;
        break;
      }
      case 'h': {
        flg->h = 1;
        break;
      }
      case 's': {
        flg->s = 1;
        break;
      }
      case 'o': {
        flg->o = 1;
        break;
      }
      case 'f': {
        flg->f = 1;
        sprintf(pattern, "%s", optarg);
        break;
      }
      default: {
        res = 1;
        if (!flg->s) printf("./21_grep: invalid option -- %c\n", c);
        break;
      }
    }
  }
  return res;
}

void grepping(int argc, char **argv, flg_t *flg, char *pattern) {
  char patternL[99999] = {0};
  int file_count = 0;
  int cols = 0;

  if (!flg->f && !flg->e) {
    sprintf(patternL, "%s", argv[optind++]);
  } else if (flg->f) {
    cols = s_p(patternL, pattern);
  } else if (!flg->f && flg->e) {
    sprintf(patternL, "%s", pattern);
  }

  if (cols != -1) {
    if (argc - optind > 1) file_count = 1;  // если файлов больше, чем 1
    for (int i = optind; i < argc; ++i) {  // обработка каждого файла
      preparing_file(flg, argv[i], file_count, patternL);
    }
  }
}

void preparing_file(flg_t *flg, char *file, int file_count, char *pattern) {
  int cflags = (flg->i) ? REG_ICASE | REG_EXTENDED : REG_EXTENDED;
  regex_t reg;
  FILE *fp = fopen(file, "r");

  if (fp != NULL) {
    regcomp(&reg, pattern, cflags);
    output(flg, fp, reg, file, file_count);
    regfree(&reg);
    fclose(fp);
  } else if (!flg->s) {
    printf("./s21_grep: %s: No such file or directory\n", file);
  }
}

void output(flg_t *flg, FILE *fp, regex_t reg, char *file, int file_count) {
  char text[99999] = {0};
  regmatch_t pmatch[1];
  int line_matchs = 0, nline = 1;
  int status;

  while (fgets(text, 99999 - 1, fp) != NULL) {
    status = regexec(&reg, text, 1, pmatch, 0);
    int match = 0;

    if (file_count && status == 0 && !flg->l && !flg->c &&
        !flg->h) {          // если файлов больше чем 1
      printf("%s:", file);  // выводим название кажого файла
    }

    if ((status == 0 && !flg->v) || (status == REG_NOMATCH && flg->v))
      match = 1;

    if (match && !flg->l && !flg->c && flg->n) printf("%d:", nline);
    if (match && !flg->l && !flg->c && !flg->o) {
      printf("%s", text);
      if (strrchr(text, '\n') == NULL) printf("\n");
    }

    if (match && flg->o) {
      for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
        printf("%c", text[i]);
      }
      printf("\n");
    }

    nline++;
    line_matchs += match;
  }

  if (flg->l && line_matchs > 0 && !flg->h) printf("%s\n", file);
  if (flg->c && !flg->l && file_count) {
    printf("%s:", file);
    printf("%d\n", line_matchs);
  } else if (flg->c && !flg->l) {
    printf("%d\n", line_matchs);
  }
}

int s_p(char *pattern, char *temp) {
  FILE *fp = fopen(temp, "r");
  int err;
  if (fp != NULL) {
    err = 0;
    int c, i = 0;
    while ((c = fgetc(fp)) != EOF) {
      if (c == '\n' || c == 13)
        pattern[i++] = '|';  // 13 - символ возврата картеки
      if (c != '\n' && c != 13) pattern[i++] = c;
    }
    if (pattern[i--] == '|') pattern[i--] = '\0';
    fclose(fp);
  } else {
    err = -1;
  }
  return err;
}
