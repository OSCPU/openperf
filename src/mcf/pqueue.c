// #include <stdio.h>
// #include <stdlib.h>
// #include <float.h>
#include <klib.h>
#include "pqueue.h"
#include <printf.h>

////////////////////////////////////////////////////////////////////////////////
//
// PQUEUE
//
////////////////////////////////////////////////////////////////////////////////

PQUEUE *pqinit(PQUEUE *pqueue, int n) 
{
    // initialize the queue;
    pqueue->_d = (PQDATUM *)bench_malloc(sizeof(PQDATUM) * n);
    if ( pqueue->_d == NULL) {
        my_printf("\nError: Unable to malloc <pqinit>.\n");
        assert(0);
    }
    
    pqueue->_avail = pqueue->_step = n;
    pqueue->_size = 1;
    return (pqueue); // return a pointer to itself;
}

int pqinsert(PQUEUE *pqueue, PQDATUM a_d, int *pos)
{
    // insert an item into the queue;
    // return 1 if item was inserted; 0 otherwise;
    // 向队列中插入一个项目； 如果插入了项目则返回 1； 否则为 0；

    PQDATUM *tmp;
    int i, newsize;

    if ( pqueue->_size == -1) return 0; // pqueue was not initialized first;
    
    // (1) allocate more memory if necessary;
    if ( pqueue->_size >= pqueue->_avail) {
        newsize = pqueue->_size + pqueue->_step;
        tmp = (PQDATUM *)bench_realloc( pqueue->_d, sizeof(PQDATUM) * newsize);
        if ( tmp == NULL) {
            my_printf("\nError: Unable to my_realloc <pqinsert>.\n");
            assert(0);
            //return 0;
        }
        pqueue->_d = tmp; // redundant;
        pqueue->_avail = newsize;       
    }

    // (2) insert item;
    i = pqueue->_size++;
    while ( i > 1 && get_distance( pqueue->_d[i / 2]) > get_distance( a_d)) {
        pqueue->_d[i] = pqueue->_d[i / 2];
        pos[node(&pqueue->_d[i])] = i;
        i /= 2;
    }
    pqueue->_d[i] = a_d;
    pos[node(&pqueue->_d[i])] = i;
    return 1;   
} 

PQDATUM *pqremove(PQUEUE *pqueue, PQDATUM *a_d, int *pos)
{
    // remove the highest-ranking item from the queue;
    // a_d: pointer to the PQDATUM variable that will hold the
    // datum corresponding to the queue item removed;
    // return value:
    // >= 0  an item has been removed. The variable that d points
    //       to now contains the datum associated with the item in question;
    // -1    no item could be removed. Either the queue pointer
    //       provided was NULL, or the queue was empty. The chunk
    //       of memory that d points to has not been modified.

    PQDATUM tmp;
    PQDATUM_init(&tmp);
    int i = 1, j;

    if ( pqueue->_size == -1 || pqueue->_size == 1) return NULL;

    *a_d = pqueue->_d[1];
    tmp = pqueue->_d[ --pqueue->_size];
    while (i <= pqueue->_size / 2) {
        j = 2 * i;
        if ( j < pqueue->_size && get_distance(pqueue->_d[j]) > get_distance(pqueue->_d[j + 1])) {
            j++;
        }
        if ( get_distance(pqueue->_d[j]) >= get_distance(tmp)) {
            break;
        }
        pqueue->_d[i] = pqueue->_d[j];
        pos[ node(&pqueue->_d[i])] = i;
        i = j;
    }
    pqueue->_d[i] = tmp;
    pos[ node(&pqueue->_d[i])] = i;
    return a_d; 
} 

int pqdeckey(PQUEUE *pqueue, PQDATUM a_d, int *pos)
{
    int i = 0;

    if ( pqueue->_size == -1) return 0; // pqueue was not initialized first;

    i = pos[ node(&a_d)];
    if ( node(&pqueue->_d[i]) != node(&a_d))
        my_printf("wrong\n");
    while ( i > 1 && get_distance(pqueue->_d[i / 2]) > get_distance(a_d)) {
        pqueue->_d[i] = pqueue->_d[i / 2];
        pos[ node(&pqueue->_d[i])] = i;
        i /= 2;
    }
    pqueue->_d[i] = a_d;
    pos[ node(&pqueue->_d[i])] = i;
    return 1;
}

PQDATUM *pqpeek(PQUEUE *pqueue, PQDATUM *a_d)
{
    // access highest-ranking item without removing it;
    // a_d: pointer to the PQDATUM variable that will hold the
    // datum corresponding to the highest-ranking item;
    // return value:
    // >= 0  Success. The variable that d points to now contains
    //       the datum associated with the highest-ranking item.
    // -1    Failure. Either the queue pointer provided was NULL,
    //       or the queue was empty. The chunk of memory that d
    //       points to has not been modified.

    if ( pqueue->_size == -1 || pqueue->_size == 1) return NULL;

    *a_d = pqueue->_d[1];
    return a_d;
}
