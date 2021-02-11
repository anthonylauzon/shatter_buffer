#include "shtr_buf.h"

struct shtr_node *shtr_write(void *buf,
                             uint64_t buf_len,
                             unsigned short int *obfs_seedp) {
    struct shtr_node *cur_node = (struct shtr_node *)
                                 malloc(sizeof(struct shtr_node));

    struct shtr_node *head_node = cur_node;
    struct shtr_node *prev_node;

    uint64_t buf_len_left = buf_len;

    void *buf_ptr = buf;

    while (1) {
        uint64_t slice_len = max((uint64_t) (drand48() * buf_len_left), 1);
        void *slice_buf = malloc(slice_len * sizeof(char));

        memcpy(slice_buf, buf_ptr, slice_len);

        cur_node->buf = slice_buf;
        cur_node->buf_len = slice_len;
        buf_ptr = buf_ptr + slice_len;

        if (buf_len_left < buf_len) {
            prev_node->next = cur_node;
        }

        buf_len_left = buf_len_left - slice_len;

        if (buf_len_left == 0) {
            break;
        }

        prev_node = cur_node;
        cur_node = (struct shtr_node *) malloc(sizeof(struct shtr_node));
        cur_node->next = NULL;
    }

    uint64_t head_obfs = (uint64_t) nrand48(obfs_seedp);

    cur_node = head_node;
    while (cur_node != NULL) {
        struct shtr_node *next_node = cur_node->next;
        shtr_obfs(cur_node->next, obfs_seedp);
        cur_node = next_node;
    }

    return head_node +  head_obfs;
}

unsigned char *shtr_read(struct shtr_node *head_node,
                         unsigned short int *obfs_seedp) {
    head_node = shtr_deobfs(head_node, obfs_seedp);

    uint64_t buf_len = head_node->buf_len;
    uint64_t buf_i = 0;

    unsigned char *buf = (unsigned char *) malloc(buf_len *
                                                  sizeof(unsigned char));

    struct shtr_node *cur_node = head_node;

    while (1) {
        for (int j = 0; j < cur_node->buf_len; j++) {
            buf[buf_i + j] = cur_node->buf[j];
        }
        buf_i = buf_i + cur_node->buf_len;

        shtr_deobfs(cur_node->next, obfs_seedp);

        cur_node = cur_node->next;

        if (cur_node == NULL) {
            break;
        }

        buf_len = buf_len + cur_node->buf_len;

        buf = (unsigned char *) realloc(buf, buf_len * sizeof(unsigned char));
    }

    return buf;
}

struct shtr_node *shtr_obfs(struct shtr_node *node,
                            unsigned short int *obfs_seedp) {
    return node + nrand48(obfs_seedp);
}

struct shtr_node *shtr_deobfs(struct shtr_node *node,
                              unsigned short int *obfs_seedp) {
    return node - nrand48(obfs_seedp);
}