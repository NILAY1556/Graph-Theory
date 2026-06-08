# Lab 2 — BFS: Breadth-First Search

## Concepts
- **BFS (Breadth-First Search)** — explore a graph level by level
- **Queue** — FIFO (First In First Out) data structure; BFS's backbone
- **Visited array** — tracks which vertices have already been seen
- **Level / Distance** — BFS naturally computes the shortest hop-count from the source

---

## Theory

Think of BFS like a **ripple in water**: you throw a stone (source vertex) and the water spreads outward one ring at a time.

```
Level 0:  source
Level 1:  all direct neighbors
Level 2:  neighbors of neighbors
...
```

**Algorithm steps:**
1. Mark source as visited; add to queue.
2. While queue is not empty:
   - Dequeue front vertex **u**.
   - For each neighbor **v** of u:
     - If v is unvisited: mark visited, enqueue.
3. The order in which vertices are dequeued = BFS traversal order.

**Why BFS?**
- Finds the **shortest path** (fewest hops) in an unweighted graph.
- Checks **connectivity** — if BFS visits all vertices, graph is connected.

**Complexity** — Time: O(V + E) | Space: O(V)

---

## Code Walk-through (`lab2.c`)

### Storage
```c
int adj[MAX_V][MAX_V];  // adj[u][i] = i-th neighbor of u
int adjSize[MAX_V];     // how many neighbors u has
int visited[MAX_V];     // 1 = already explored
int queue[MAX_V];       // simple array-based queue
```

### `addEdge(u, v)`
```c
adj[u][adjSize[u]++] = v;
adj[v][adjSize[v]++] = u;   // undirected: add both sides
```

### `bfs(source, V)` — step by step
| Step | Code | What happens |
|------|------|--------------|
| Init | `visited[source]=1; queue[rear++]=source` | Seed the queue |
| Dequeue | `u = queue[front++]` | Take next vertex to process |
| Record | `result[resultSize++] = u` | Save visit order |
| Explore | loop over `adj[u]` | Enqueue unvisited neighbors |

### Example trace (graph in code)
```
Edges: 0-1, 0-2, 1-2, 1-3, 2-4, 3-4
BFS from 0:
  Visit 0 → enqueue 1, 2
  Visit 1 → enqueue 3  (0,2 already seen)
  Visit 2 → enqueue 4  (0,1 already seen)
  Visit 3 → (1,4 seen)
  Visit 4 → done
Output: [0, 1, 2, 3, 4]
```

---

## Compile & Run
```bash
gcc lab2.c -o lab2
./lab2
```
