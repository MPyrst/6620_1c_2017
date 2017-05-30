#ifndef DEFINES_H
#define DEFINES_H

/*
 * dr: total reads on data cache
 * dw: total writes on data cache
 * d1mr: total reads miss rate on data cache
 * d1mw: total writes miss rate on data cache
 */
struct parser_output {
    unsigned long dr = 0;
    unsigned long dw = 0;
    unsigned long d1mr = 0;
    unsigned long d1mw = 0;
};

#endif //DEFINES_H
