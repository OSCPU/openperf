// ported from https://github.com/lab104yifan/ACM/blob/93daae9b997aa4df1af96d3140ad81b3506cee49/UVA10779.cpp

#include <bench.h>
#include <stdbool.h>

static const struct {
  int size;
  int ans;
  uint64_t ref_time;
} *ps, settings[BENCH_NR_SETTING] = {
         {10, 402, 0},
         {60, 12911, 110},
         {209, 99568, 648311},
         {219, 106697, 38544532},
};

static int N;
const int INF = 0x3f3f3f;

typedef struct Edge {
  int from;
  int to;
  int cap;
  int flow;
} Edge;

static inline int min(int x, int y) {
  return x < y ? x : y;
}

typedef struct Dinic {
  int n, m, s, t;
  Edge *edges;
  int *head, *nxt, *d, *cur, *queue;
  bool *vis;
} Dinic;

static Dinic *G;
static int ans;

static void init(Dinic *this, int n) {
  int nold = (n - 2) / 2;
  int maxm = (nold * nold + nold * 2) * 2;

  this->edges = (Edge *)malloc(sizeof(Edge) * maxm);
  this->head = (int *)malloc(sizeof(int) * n);
  this->nxt = (int *)malloc(sizeof(int) * maxm);
  this->vis = (bool *)malloc(sizeof(bool) * n);
  this->d = (int *)malloc(sizeof(int) * n);
  this->cur = (int *)malloc(sizeof(int) * n);
  this->queue = (int *)malloc(sizeof(int) * n);

  this->n = n;
  for (int i = 0; i < n; i++) {
    this->head[i] = -1;
  }
  this->m = 0;
}

static void AddEdge(Dinic *this, int u, int v, int c) {
  if (c == 0)
    return;
  this->edges[this->m] = (Edge){u, v, c, 0};
  this->nxt[this->m] = this->head[u];
  this->head[u] = this->m++;
  this->edges[this->m] = (Edge){v, u, 0, 0};
  this->nxt[this->m] = this->head[v];
  this->head[v] = this->m++;
}

static bool BFS(Dinic *this) {
  for (int i = 0; i < this->n; i++)
    this->vis[i] = 0;
  int qf = 0, qr = 0;
  this->queue[qr++] = this->s;
  this->d[this->s] = 0;
  this->vis[this->s] = 1;
  while (qf != qr) {
    int x = this->queue[qf++];
    for (int i = this->head[x]; i != -1; i = this->nxt[i]) {
      Edge *e = &(this->edges[i]);
      if (!this->vis[e->to] && e->cap > e->flow) {
        this->vis[e->to] = 1;
        this->d[e->to] = this->d[x] + 1;
        this->queue[qr++] = e->to;
      }
    }
  }
  return this->vis[this->t];
}

static int DFS(Dinic *this, int x, int a) {
  if (x == this->t || a == 0)
    return a;
  int flow = 0, f;
  for (int i = this->cur[x]; i != -1; i = this->nxt[i]) {
    Edge *e = &(this->edges[i]);
    if (this->d[x] + 1 == this->d[e->to] && (f = DFS(this, e->to, min(a, e->cap - e->flow))) > 0) {
      e->flow += f;
      this->edges[i ^ 1].flow -= f;
      flow += f;
      a -= f;
      if (a == 0)
        break;
    }
  }
  return flow;
}

static int Maxflow(Dinic *this, int s, int t) {
  this->s = s;
  this->t = t;
  int flow = 0;
  while (BFS(this)) {
    for (int i = 0; i < this->n; i++)
      this->cur[i] = this->head[i];
    flow += DFS(this, s, INF);
  }
  return flow;
}

void bench_init(int setting) {
  ps = &settings[setting];
  N = ps->size;
  bench_srand(1);
  int s = 2 * N, t = 2 * N + 1;
  G = (Dinic *)malloc(sizeof(Dinic));
  init(G, 2 * N + 2);
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) {
      AddEdge(G, i, N + j, bench_rand() % 10);
    }

  for (int i = 0; i < N; i++) {
    AddEdge(G, s, i, bench_rand() % 1000);
    AddEdge(G, N + i, t, bench_rand() % 1000);
  }
}

uint64_t bench_run() {
  ans = Maxflow(G, 2 * N, 2 * N + 1);
  return ps->ref_time;
}

int bench_validate() {
  printf("ans = %d\n", ans);
  free(G->edges);
  free(G->head);
  free(G->nxt);
  free(G->vis);
  free(G->d);
  free(G->cur);
  free(G->queue);
  free(G);
  return ans == ps->ans ? 0 : 1;
}
