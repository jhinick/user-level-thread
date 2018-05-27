//
// Created by koc on 5/23/18.
//

#include <stdlib.h>
#include "tool.h"
#include "coroutine.h"

thread_list *create_thread_list() {
    thread_list *list = malloc(sizeof(thread_list));
    thread_node *empty_node = malloc(sizeof(thread_node));
    empty_node->next = NULL;
    list->head = empty_node;
    list->tail = empty_node;
    list->length = 0;
    return list;
}

int append_thread(thread_list *list, thread_node *node) {
    list->tail->next = node;
    list->tail = node;
    list->length++;
    return list->length;
}

int delete_thread_by_tid(thread_list *list, int tid) {
    thread_node *last = list->head;
    thread_node *cn = list->head->next;
    while (cn) {
        if (cn->context.tid == tid) {
            if (cn == list->tail) {
                list->tail = list->head;
            }
            last->next = cn->next;
            return 0;
        }
    }
    return -1;
}

thread_node *pop_thread(thread_list *list, int pos) {
    if (pos < 0) {
        return pop_thread(list, list->length + pos);
    } else if (pos >= list->length) {
        return NULL;
    } else {
        thread_node *current_node = list->head->next;
        thread_node *last = list->head;
        for (int i = 0; i < pos; i++) {
            last = current_node;
            current_node = current_node->next;
        }
        last->next = current_node->next;
        list->length--;
        if (current_node == list->tail) {
            list->tail = last;
        }
        current_node->next = NULL;
        return current_node;
    }
}

thread_node *find_thread(thread_list*list,int tid) {
    thread_node *cn = list->head->next;
    while (cn) {
        if (cn->context.tid == tid) {
            return cn;
        }
        cn = cn->next;
    }
    return NULL;
}