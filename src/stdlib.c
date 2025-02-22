#include <stdlib.h>
#include <string.h>

#define MAX_ATEXIT 32

static void (*atexit_funcs[MAX_ATEXIT])(void);
static int atexit_count;

void __exit(int status);

void exit(int status) {
  int i = 0;
  
  for (i = atexit_count - 1; i >= 0; i--) {
    atexit_funcs[i]();
  }
  __exit(status);
}

int atexit(void (*func)(void)) {
  if (atexit_count < MAX_ATEXIT) {
    atexit_funcs[atexit_count++] = func;
    return 0;
  }
  return 1;
}

/* Implementation for `malloc` and co. lovingly (?) taken from https://github.com/RAGUL1902/Dynamic-Memory-Allocation-in-C */

typedef struct block {
  size_t size;
  int free;
  struct block *next;
  struct block *prev;
  char data[1];
} block_t;

#define BLOCK_SIZE (sizeof(block_t) - 1)

block_t *head = NULL;
int __brk(void *addr);
void *__sbrk(int increment);

static block_t *find_block(block_t **last, size_t size) {
  block_t *b = head;
  while (b && !(b->free && b->size >= size)) {
    *last = b;
    b = b->next;
  }
  return b;
}

static void split_block(block_t *block, size_t size) {
  block_t *new = (block_t *)(block->data + size);
  new->size = block->size - size - BLOCK_SIZE;
  new->free = 1;
  new->next = block->next;
  new->prev = block;

  block->size = size;
  block->next = new;
  if (new->next) {
    new->next->prev = new;
  }
}

static block_t *merge_blocks(block_t *block) {
  if (block->next && block->next->free) {
    block->size += BLOCK_SIZE + block->next->size;
    block->next = block->next->next;
  }
  if (block->next) {
    block->next->prev = block;
  }
  return block;
}

static block_t *extend_heap(block_t *last, size_t size) {
  block_t *old, *new;
  old = __sbrk(0);
  new = __sbrk(size + BLOCK_SIZE);
  if (new == (void *)-1) {
    return NULL;
  }
  old->size = size;
  old->free = 0;
  old->next = NULL;
  old->prev = last;
  if (last) {
    last->next = old;
  }

  return old;
}

static int is_addr_valid(void *ptr) {
  block_t *b = head;
  while (b) {
    if (b->data == ptr) {
      return 1;
    }
    b = b->next;
  }
  return 0;
}

static block_t *get_block_addr(void *ptr) {
  return (block_t *)((char *)ptr - BLOCK_SIZE);
}

void *malloc(size_t size) {
  block_t *block, *last;

  if (size <= 0) {
    return NULL;
  }

  if (head) {
    last = head;
    block = find_block(&last, size);
    if (block) {
      if (block->size - size > BLOCK_SIZE) {
        split_block(block, size);
      }
      block->free = 0;
    } else {
      block = extend_heap(last, size);
      if (!block) {
        return NULL;
      }
    }
  } else {
    block = extend_heap(NULL, size);
    if (!block) {
      return NULL;
    }
    head = block;
  }

  return block->data;
}

void *calloc(size_t num, size_t size) {
  void *ptr = malloc(num * size);
  size_t i;

  if (ptr) {
    for (i = 0; i < num * size; i++) {
      ((char *)ptr)[i] = 0;
    }
  }

  return ptr;
}

void *realloc(void *ptr, size_t size) {
  block_t *old_block, *new_block;
  void *new_ptr;

  if (!ptr) {
    return malloc(size);
  }

  if (is_addr_valid(ptr)) {
    old_block = get_block_addr(ptr);

    if (old_block->size >= size) {
      if (old_block->size - size > BLOCK_SIZE) {
        split_block(old_block, size);
      }
    } else {
      if (old_block->next && old_block->next->free && (old_block->size + old_block->next->size + BLOCK_SIZE) >= size) {
        merge_blocks(old_block);
        if (old_block->size - size > BLOCK_SIZE) {
          split_block(old_block, size);
        }
      } else {
        new_ptr = malloc(size);

        if (!new_ptr) {
          return NULL;
        }

        memcpy(new_ptr, ptr, old_block->size);
        free(ptr);
        return new_ptr;
      }
    }

    return ptr;
  }

  return NULL;
}

void free(void *ptr) {
  if (is_addr_valid(ptr)) {
    block_t *block = get_block_addr(ptr);
    block->free = 1;
    
    if (block->prev && block->prev->free) {
      block = merge_blocks(block->prev);
    }

    if (block->next) {
      block = merge_blocks(block);
    } else {
      if (block->prev) {
        block->prev->next = NULL;
      } else {
        head = NULL;
      }
      __brk(block);
    }
  }
}
