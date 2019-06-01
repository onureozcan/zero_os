//
// Created by onureozcan on 01.06.2019.
//

#include <memory/memory_manager.h>
#include <assert.h>
#include <string.h>

void test_simple_allocation() {
    void *ptr = k_malloc(10);
    assert(ptr != NULL);
    k_free(ptr);
}

void test_realloc_from_null(){
    void *ptr = k_realloc(NULL,10);
    k_free(ptr);
}

void test_realloc(){
    char *ptr = k_realloc(NULL,6);
    memcpy(ptr,"osman",6);
    ptr = k_realloc(ptr, 11);
    memcpy(ptr+5,"osman",6);
    assert(strcmp(ptr,"osmanosman") == 0);
}

int main() {

    memory_manager_malloc_init();
    test_simple_allocation();
    test_realloc_from_null();
    test_realloc();

    return 0;
}