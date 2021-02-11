#ifndef __SHTR_H
#define __SHTR_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a,b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
       _a > _b ? _a : _b; })

struct shtr_node {
    char *buf;
    uint64_t buf_len;
    struct shtr_node *next;
};

struct shtr_node *shtr_obfs(struct shtr_node *node,
                            unsigned short int *obfs_seedp);

struct shtr_node *shtr_deobfs(struct shtr_node *node,
                              unsigned short int *obfs_seedp);

extern struct shtr_node *shtr_write(void *buf,
                                    uint64_t buf_len,
                                    unsigned short int *obfs_seedp);

extern unsigned char *shtr_read(struct shtr_node *head_node,
                                unsigned short int *obfs_seedp);

#endif