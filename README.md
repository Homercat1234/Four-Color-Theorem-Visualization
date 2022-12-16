# GraphToImage
A program to convert a graph into a 2d graphics. AI assisted using ChatGPT

The generateRandomGraph function generates a random graph with a random number of vertices between 10 and 20 (inclusive) and random edges between the vertices. It does this by creating the vertices and adding them to the graph, and then generating random edges between the vertices by choosing a vertex and checking if it should be connected to another vertex with a 50% probability.

The generateVertexPositions function generates the x and y positions of the vertices as well as the size of each vertex based on the adjacency list of the graph. It does this by evenly spacing out the vertices around a circle centered at centerX and centerY with a radius of radius. The size of each vertex is determined by the number of edges it has.

The main function is responsible for rendering the graph on the screen using SDL (Simple DirectMedia Layer). It does this by first clearing the screen and setting the background color, and then drawing each vertex and its edges. The color of each vertex is determined by its color field, which is set by the getColors function using a breadth-first search (BFS) algorithm to implement the four color theorem. The four color theorem states that it is possible to color any planar graph (a graph that can be drawn on a plane without any of its edges intersecting) using at most four colors, such that no two adjacent vertices (vertices that are connected by an edge) have the same color.
