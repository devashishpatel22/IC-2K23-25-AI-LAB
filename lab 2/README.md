
# Lab 2: AI Search Algorithms

## 1. Aim / Problem Statement
To implement and study BFS, DFS, Hill Climbing, Best-First Search, and A* search algorithms.

## 2. Algorithms

### 1. Breadth-First Search (BFS)
Explores nodes level by level using a FIFO queue. It finds a shortest path in an unweighted graph.

### 2. Depth-First Search (DFS)
Explores deeper nodes before backtracking using a stack.

### 3. Hill Climbing
Selects a neighboring state with a better heuristic value at each step. It may get stuck at a local optimum.

### 4. Best-First Search
Uses a priority queue to expand the node with the lowest heuristic value.

### 5. A* Search
Uses the evaluation function:
f(n) = g(n) + h(n)

Here, g(n) is the cost from the start node and h(n) is the estimated cost to the goal.

## 3. Programs
- `bfs.py`
- `dfs.py`
- `hill_climbing.py`
- `best_first_search.py`
- `a_star.py`

## 4. Results / Output
Each program demonstrates its respective search strategy on a sample graph.

Record actual outputs after running each program.

## 5. Performance Analysis
Compare the algorithms using:
- Path found
- Path length or total cost
- Nodes explored
- Execution time

Execution time and nodes explored should be measured during testing rather than estimated.

## 6. Screenshots / Graphs
Add screenshots of program outputs here after execution.

## 7. Learning Outcomes
- Understand uninformed and informed search strategies.
- Learn graph traversal using queues, stacks, and priority queues.
- Understand heuristic-based search.
- Compare search algorithms and their limitations.