#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
  block_t *block;
  void *mem;
  
  /* Get current program break */
  mem = sbrk(0);
  
  /* Request additional memory */
  if (sbrk(size + BLOCK_SIZE) == (void *)-1) {
    return NULL;
  }
  
  /* Initialize the new block at the old program break */
  block = (block_t *)mem;
  block->size = size;
  block->free = 0;
  block->next = NULL;
  block->prev = last;
  
  /* Link with the previous block if it exists */
  if (last) {
    last->next = block;
  }

  return block;
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

  /* In C90, malloc(0) is implementation-defined - can return NULL or valid ptr */
  /* We'll allow zero-sized allocations to work normally */

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

  if (ptr) {
    memset(ptr, 0, num * size);
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
    
    /* Try to merge with previous block if it's free */
    if (block->prev && block->prev->free) {
      block = merge_blocks(block->prev);
    }

    /* Try to merge with next block if it exists */
    if (block->next) {
      block = merge_blocks(block);
    } else {
      /* Last block in the list, consider returning memory to the system */
      if (block->prev) {
        /* There are previous blocks, just unlink this one */
        block->prev->next = NULL;
      } else {
        /* This is the only block, remove it from the list */
        head = NULL;
      }
      
      /* Return memory to the system by moving the program break */
      /* Use the correct address - the beginning of this block */
      brk((void*)block);
    }
  }
}
