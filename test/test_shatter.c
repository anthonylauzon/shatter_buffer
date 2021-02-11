#include <fcntl.h>
#include <shtr_buf.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_BUF_LEN 0xDEAD

int test_simple() {
      int nest_len = 0;

      int in_buf_len = drand48() * MAX_BUF_LEN;

      unsigned char *in_buf = (unsigned char *)
                              malloc(in_buf_len * sizeof(unsigned char));

      int urand = open("/dev/urandom", O_RDONLY);
      read(urand, in_buf, in_buf_len);

      unsigned short int obfs_seedp[3] = {6, 7, 8};

      struct shtr_node *head_obfs = shtr_write(in_buf,
                                               in_buf_len,
                                               obfs_seedp);

      obfs_seedp[0] = 6;
      obfs_seedp[1] = 7;
      obfs_seedp[2] = 8;

      unsigned char *out_buf = shtr_read(head_obfs, obfs_seedp);

      printf("test_simple: ");
      if (memcmp(in_buf, out_buf, in_buf_len) == 0) {
        printf("PASSED\n");
      } else {
        printf("FAILED\n");
        return 1;
      }

      return 0;
}

int main(int argc, char **argv) {
    if (test_simple()) {
        printf("FAIL: test_simple_alloc_put\n");
        return 1;
    }

    return 0;
}


