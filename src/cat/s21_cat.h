#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <string.h>

struct flags_cat {
  int fl_b;
  int fl_e;
  int fl_n;
  int fl_s;
  int fl_t;
  int fl_E;
  int fl_T;
  int fl_v;
};

int flags(int argc, char *argv[], struct flags_cat *flag);
void init_flag(struct flags_cat *flag);
void last_linking(int argc, char *argv[], struct flags_cat *flag);

#endif  // SRC_CAT_S21_CAT_H_
