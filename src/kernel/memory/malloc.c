//
// Created by onureozcan on 01.06.2019.
//

/**
 * This file implements k_malloc, k_free and k_realloc defined in memory_manager.h
 * */
#include <memory/memory_manager.h>
#include <common.h>
#include <string/k_string.h>
#include <display/console.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "K_MALLOC"
#define SIZE_OF_K_MALLOC_NODE sizeof(struct k_malloc_node)

struct k_malloc_node {
    int is_free;  // TODO: why wasting this many bytes?
    size_t size;
    struct k_malloc_node *next;
};

static struct k_malloc_node *head = (void *) kernel_heap_area;

static struct k_malloc_node *get_k_malloc_node_from_ptr(void *ptr) {
    return ((struct k_malloc_node *) ((void *) ptr - SIZE_OF_K_MALLOC_NODE));
}

void memory_manager_malloc_init() {
    head->is_free = TRUE;
    head->next = NULL;
    head->size = KERNEL_HEAP_SIZE_BYTES - SIZE_OF_K_MALLOC_NODE;
}

/**
 * splits a given block
 * @param big_block
 * @param size
 */
static void k_malloc_split(struct k_malloc_node *big_block, size_t size) {

    struct k_malloc_node *new_block = ((void *) big_block + size + SIZE_OF_K_MALLOC_NODE);
    new_block->size = (big_block->size - size - SIZE_OF_K_MALLOC_NODE);
    new_block->is_free = TRUE;
    new_block->next = big_block->next;
    big_block->size = size;
    big_block->is_free = FALSE;
    big_block->next = new_block;
    console_log(LOG_TAG, "split block %p. new block: %p, size: %d\n", big_block, new_block, new_block->size);

}

static void k_malloc_merge_2_blocks(struct k_malloc_node *current, struct k_malloc_node *next) {
    console_log(LOG_TAG,"merging blocks %p and %d\n", current, next);
    current->next = next->next;
    current->size += next->size + SIZE_OF_K_MALLOC_NODE;
}

static void k_malloc_merge() {
    struct k_malloc_node *current = head;
    while (current != NULL) {
        if (current->is_free) {
            struct k_malloc_node *next = current->next;
            if (next && next->is_free) {
                k_malloc_merge_2_blocks(current, next);
            }
        }
        current = current->next;
    }
}

void *k_malloc(size_t size) {
    console_log(LOG_TAG, "malloc %d bytes\n", size);
    size = ALIGN_4(size);
    struct k_malloc_node *current = head;
    while (current != NULL) {
        console_log(LOG_TAG, "current:%p is_free:%d, size:%d\n", current, current->is_free, current->size);
        if (current->is_free && current->size + SIZE_OF_K_MALLOC_NODE >= size) {
            if (current->size + SIZE_OF_K_MALLOC_NODE != size) {
                k_malloc_split(current, size);
            }
            current->is_free = FALSE;
            return (void *) current + SIZE_OF_K_MALLOC_NODE;
        }
        current = current->next;
    }
    console_log(LOG_TAG, "unable to deliver %d bytes requested\n", size);
    panic("kernel runs out of memory!");
    return NULL;
}

void *k_realloc(void *ptr, size_t size) {
    if (ptr == NULL) {
        return k_malloc(size);
    } else {
        size_t old_size = get_k_malloc_node_from_ptr(ptr)->size;
        void *new_ptr = k_malloc(size);
        memcpy(new_ptr, ptr, old_size);
        return new_ptr;
    }
    return NULL;
}

void k_free(void *ptr) {
    struct k_malloc_node *node = get_k_malloc_node_from_ptr(ptr);
    node->is_free = TRUE;
    k_malloc_merge();
}

