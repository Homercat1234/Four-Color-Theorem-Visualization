# Four-Color Theorem Visualization
This program visualizes the four-color theorem, which states that any map can be colored using only four colors, such that no two adjacent regions have the same color. The program generates a random graph and uses a breadth-first search (BFS) algorithm to color the vertices of the graph according to the four-color theorem.

## Prerequisites
[SDL2](https://www.libsdl.org/) (Simple DirectMedia Layer) library for rendering the graph.

## Building and Running
To build and run the program, follow these steps:

1. Install the SDL2 library.
2. Clone this repository to your local machine.
3. Navigate to the root directory of the repository.
4. Run the following command to build the program:
```
g++ program.cpp -o program -lSDL2
```
5. Run the following command to run the program:
```
./program
```
## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
* The algorithm for coloring the vertices of the graph using the four-color theorem is based on the [BFS algorithm](https://en.wikipedia.org/wiki/Breadth-first_search) for graph traversal.
* The function for checking if two line segments intersect is based on the [cross product](https://en.wikipedia.org/wiki/Cross_product) of the two line segments.
* A large portion of the code for this program was generated by the [GPT language model](https://chat.openai.com/).
