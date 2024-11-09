#ifndef _PQUEUE_H_
#define _PQUEUE_H_

// #include <stdio.h>
#include <bench_malloc.h>
#include <klib.h>

////////////////////////////////////////////////////////////////////////////////
//
// PQUEUE
//
////////////////////////////////////////////////////////////////////////////////

typedef struct {
  int _node;
  double _dist;
} PQDATUM;

static inline void PQDATUM_init(PQDATUM *pqdatum) {
  pqdatum->_node = -1;
  pqdatum->_dist = -1;
}
static inline int node(PQDATUM *pqdatum) { return pqdatum->_node; }
static inline double dist(PQDATUM *pqdatum) { return pqdatum->_dist; }
static inline void set_node(PQDATUM *pqdatum, int node) {
  pqdatum->_node = node;
}
static inline void set_dist(PQDATUM *pqdatum, double dist) {
  pqdatum->_dist = dist;
}

typedef struct {
  int _size, _avail, _step;
  PQDATUM *_d;
} PQUEUE;

static inline void PQUEUE_init(PQUEUE *pqueue) {
  pqueue->_size = -1;
  pqueue->_avail = -1;
  pqueue->_step = -1;
}
static inline int size(PQUEUE *pqueue) { return pqueue->_size; }
static inline int avail(PQUEUE *pqueue) { return pqueue->_avail; }
static inline int step(PQUEUE *pqueue) { return pqueue->_step; }
static inline PQDATUM *d(PQUEUE *pqueue) { return pqueue->_d; }
PQUEUE *pqinit(PQUEUE *pqueue, int n);
int pqinsert(PQUEUE *pqueue, PQDATUM a_d, int *pos);
PQDATUM *pqremove(PQUEUE *pqueue, PQDATUM *a_d, int *pos);
int pqdeckey(PQUEUE *pqueue, PQDATUM a_d, int *pos);
PQDATUM *pqpeek(PQUEUE *pqueue, PQDATUM *a_d);
static inline double get_distance(PQDATUM d) { return dist(&d); }
static inline int pqempty(PQUEUE *pqueue) { return (pqueue->_size == 1); }
static inline void pqfree(PQUEUE *pqueue, int *pos) {
  bench_free(pqueue->_d);
  bench_free(pos);
}

#endif
