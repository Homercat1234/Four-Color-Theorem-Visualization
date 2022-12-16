#include <SDL2/SDL.h>
#include <vector>
#include <queue>
#include <unordered_set>
#include <random>
#include <ctime>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int VERTEX_RADIUS = 20;
const int NUM_COLORS = 4;

// Class to represent a vertex in the graph
class Vertex
{
public:
    vector<Vertex *> neighbors;
    int data;
    int x;
    int y;
    int color;
    int size;

    Vertex(int data, int x = 0, int y = 0)
    {
        this->data = data;
        this->x = x;
        this->y = y;
    }
};

// Class to represent a graph
class Graph
{
public:
    vector<Vertex *> vertices;

    void addVertex(Vertex *v)
    {
        vertices.push_back(v);
    }

    void addEdge(Vertex *v1, Vertex *v2)
    {
        v1->neighbors.push_back(v2);
        v2->neighbors.push_back(v1);
    }

    // Function to implement four color theorem using BFS
    void getColors(Vertex *start)
    {
        queue<Vertex *> q;
        unordered_set<Vertex *> visited;

        start->color = 0;
        q.push(start);
        visited.insert(start);

        while (!q.empty())
        {
            Vertex *v = q.front();
            q.pop();

            // Color the current vertex
            for (int i = 0; i < NUM_COLORS; i++)
            {
                if (i != v->color)
                {
                    bool valid = true;
                    for (Vertex *neighbor : v->neighbors)
                    {
                        if (neighbor->color == i)
                        {
                            valid = false;
                            break;
                        }
                    }

                    if (valid)
                    {
                        v->color = i;
                        break;
                    }
                }
            }

            // Add the neighbors of the current vertex to the queue
            for (Vertex *neighbor : v->neighbors)
            {
                if (visited.find(neighbor) == visited.end())
                {
                    q.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }
    }
};

// Function to check if two line segments intersect
bool intersects(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    // Calculate the intersecting point of the two line segments
    long long denominator1 = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    long long denominator2 = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (denominator1 == 0 || denominator2 == 0) return false; // line segments are parallel

    long long intersectX = ((long long)x1 * y2 - (long long)y1 * x2) * (x3 - x4) - ((long long)x1 - x2) * ((long long)x3 * y4 - (long long)y3 * x4);
    long long intersectY = ((long long)x1 * y2 - (long long)y1 * x2) * (y3 - y4) - ((long long)y1 - y2) * ((long long)x3 * y4 - (long long)y3 * x4);

    // Check if the intersecting point is within the bounds of both line segments
    if ((min(x1, x2) <= intersectX && intersectX <= max(x1, x2))
            && (min(y1, y2) <= intersectY && intersectY <= max(y1, y2))
            && (min(x3, x4) <= intersectX && intersectX <= max(x3, x4))
            && (min(y3, y4) <= intersectY && intersectY <= max(y3, y4)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

Graph generateRandomGraph()
{
    Graph g;

    // Set the seed to time(0)
    srand(time(0));

    // Generate a random number of vertices
    int numVertices = rand() % 11 + 10; // generates a random number between 10 and 20 (inclusive)

    // Create the vertices and add them to the graph
    for (int i = 0; i < numVertices; i++)
    {
        Vertex *v = new Vertex(i);
        g.addVertex(v);
    }

    // Generate random edges between the vertices
    for (int i = 0; i < numVertices; i++)
    {
        Vertex *v1 = g.vertices[i];
        for (int j = i + 1; j < numVertices; j++)
        {
            Vertex *v2 = g.vertices[j];
            if (rand() % 2 == 0) // generates a random boolean value
            {
                // Check if adding this edge would make the graph non-planar
                bool doesIntersect = false;
                for (Vertex *v : g.vertices)
                {
                    if (v == v1 || v == v2)
                        continue;

                    // Check if the edge intersects with any other edge in the graph
                    for (Vertex *neighbor : v->neighbors)
                    {
                        if (intersects(v1->x, v1->y, v2->x, v2->y, v->x, v->y, neighbor->x, neighbor->y))
                        {
                            doesIntersect = true;
                            break;
                        }
                    }

                    if (doesIntersect)
                        break;
                }

                if (!doesIntersect)
                {
                    // Add the edge if it doesn't intersect with any other edge
                    g.addEdge(v1, v2);
                }
            }
        }
    }

    return g;
}

// Function to generate the x and y positions of the vertices as well as the size of each vertex based on the adjacency list
void generateVertexPositions(Graph &g, int centerX = SCREEN_WIDTH / 2, int centerY = SCREEN_HEIGHT / 2, int radius = SCREEN_WIDTH / 2 - VERTEX_RADIUS)
{
    int numVertices = g.vertices.size();
    int currentAngle = 0;

    for (Vertex *v : g.vertices)
    {
        // Calculate the angle step based on the number of neighbors
        int numNeighbors = v->neighbors.size();
        int angleStep = 360 / numNeighbors;

        // Calculate the x and y positions based on the current angle and the given center coordinates and radius
        v->x = centerX + radius * cos(currentAngle * M_PI / 180);
        v->y = centerY + radius * sin(currentAngle * M_PI / 180);

        // Calculate the size of the vertex based on the number of neighbors it has
        v->size = VERTEX_RADIUS * 2 + numNeighbors * VERTEX_RADIUS;
        v->x -= v->size / 2;
        v->y -= v->size / 2;

        currentAngle += angleStep;
    }
}

int main(int argc, char **argv)
{
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Adjacency List to 2D Array",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    // Create a graph
    Graph g = generateRandomGraph();

    // Generate the x and y positions of the vertices
    generateVertexPositions(g);

    // Set the renderer draw color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    // Set the background color to black
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = SCREEN_WIDTH;
    rect.h = SCREEN_HEIGHT;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    // Generate the colors of the vertex
    g.getColors(g.vertices[0]);

    // Define the four colors
    int colors[4][3] = {{233, 150, 122}, {139, 0, 139}, {255, 255, 255}, {0, 100, 0}};

    // Draw the vertices
    for (Vertex *v : g.vertices)
    {
        // Draw the vertex
        SDL_SetRenderDrawColor(renderer, colors[v->color][0], colors[v->color][2], colors[v->color][3], SDL_ALPHA_OPAQUE);
        SDL_Rect vertexRect = {v->x - v->size, v->y - v->size, v->size * 2, v->size * 2};
        SDL_RenderFillRect(renderer, &vertexRect);
    }

    // Update the screen
    SDL_RenderPresent(renderer);

    // Handle events
    SDL_Event e;
    bool quit = false;
    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
