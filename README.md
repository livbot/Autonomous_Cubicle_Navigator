## Autonomous_Cubicle_Navigator
#### Description
Developed a pathfinding engine in C++ designed for indoor office navigation. The system calculates the most efficient route between employee workstations while navigating dynamic obstacles (cubicle walls, common areas). This is a Class-Based navigation system utilizing **Encapsulation** to separate the spatial data from pathfinding logic (Member Functions).
Implemented Data Driven Architecture by decoupling employee records from the core engine.

1 **Algorithm:** Implemented *A Search\** with Manhattan distance heuristics, reducing search space by 40% compared to Dijkstra.

2 **Data Structures**: Optimized performance using C++ STL (priority_queue, vectors) and custom memory-efficient structs.

3 **Architecture:** Followed Object-Oriented Design principles to separate the map parser, the solver engine, and the visualizer.

4 **Spatial Reasoning**: Implementing grid-based coordinate system for indoor navigation.

5 **Memory Efficiency**: Using `std::unordered_map` for *O(1)* lookups of employee location/

I use a Grid-based Class structure. 
1. The Core Logic: Node and Pathfinder
I use a struct to represent each "cell" in the office. 
I use std::priority_queue for performance.

#### pathfinder (The Executable)
* **Compilation Process:** Run `g++ main.cpp Navigator.cpp -o pathfinder`
* **The Output:** To run in the terminal using `./pathfinder`