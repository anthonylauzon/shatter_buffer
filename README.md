# shatter_buffer

shatter_buffer is a stochastic obfuscator for buffers. it works by breaking
an input buffer up into slices of random length, randomly allocating the slices
into a linked list structure, and finally obfuscating the linked list's next
pointers according to some secure known seed.

## usage

```
// shatter a buffer and return the head node's obfuscated location in memory
set_obfs_seedp(obfs_seedp);
struct shtr_node *head_obfs = shtr_write(in_buf, in_buf_len, obfs_seedp);

// recover the original buffer
set_obfs_seedp(obfs_seedp);
unsigned char *out_buf = shtr_read(head_obfs, obfs_seedp);
```