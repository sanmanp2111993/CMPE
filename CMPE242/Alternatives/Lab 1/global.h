#include <stdio.h>
#include <stdlib.h>

int lsm303_open(char *dev_fqn, int addr, struct lsm303* e);
int accread();
int magread();
void open_buzzer(void);
void set_buzzer_freq(int freq);
