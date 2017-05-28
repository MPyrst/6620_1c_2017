//
// Created by federicofarina on 5/28/17.
//

#ifndef DEFINES_H
#define DEFINES_H

/*
 * dr: total reads on data cache
 * dw: total writes on data cache
 * d1mr: total reads miss rate on data cache
 * d1mw: total writes miss rate on data cache
 */
struct parser_output {
    long dr;
    long dw;
    long d1mr;
    long d1mw;
};

#endif //DEFINES_H
