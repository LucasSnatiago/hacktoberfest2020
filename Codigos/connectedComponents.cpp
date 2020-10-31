// A C++ program to check if a given graph is Eulerian or not
#include<iostream>
#include <list>
using namespace std;


/**
 * Utilizei extensos trechos de codigo do geeksforgeeks, disponibilizados livremente na internet para consulta.
 * Disponíveis em https://www.geeksforgeeks.org/program-to-count-number-of-connected-components-in-an-undirected-graph/
 */


// A class that represents an undirected graph
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // A dynamic array of adjacency lists
public:
    // Constructor and destructor
    explicit Graph(int V)   {this->V = V; adj = new list<int>[V]; }
    ~Graph() { delete [] adj; } // To avoid memory leak

    // function to add an edge to graph
    void addEdge(int v, int w);

    // Method to check if this graph is Eulerian or not
    int isEulerian();

    // Method to check if all non-zero degree vertices are connected
    bool isConnected();

    // Function to do DFS starting from v. Used in isConnected();
    void DFSUtil(int v, bool visited[]);

    int NumberOfconnectedComponents();

    void connectedComponentsFromVertex(int v);
};

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
}

void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

// Method to check if all non-zero degree vertices are connected.
// It mainly does DFS traversal starting from
bool Graph::isConnected()
{
    // Mark all the vertices as not visited
    bool visited[V];
    int i;
    for (i = 0; i < V; i++)
        visited[i] = false;

    // Find a vertex with non-zero degree
    for (i = 0; i < V; i++)
        if (!adj[i].empty())
            break;

    // If there are no edges in the graph, return true
    if (i == V)
        return true;

    // Start DFS traversal from a vertex with non-zero degree
    DFSUtil(i, visited);

    // Check if all non-zero degree vertices are visited
    for (i = 0; i < V; i++)
        if (!visited[i] && !adj[i].empty())
            return false;

    return true;
}

/* The function returns one of the following values
   0 --> If grpah is not Eulerian
   1 --> If graph has an Euler path (Semi-Eulerian)
   2 --> If graph has an Euler Circuit (Eulerian)  */
int Graph::isEulerian()
{
    // Check if all non-zero degree vertices are connected
    if (!isConnected())
        return 0;

    // Count vertices with odd degree
    int odd = 0;
    for (int i = 0; i < V; i++)
        if (adj[i].size() == 1)
            odd++;

    // If count is more than 2, then graph is not Eulerian
    if (odd > 2)
        return 0;

    // If odd count is 2, then semi-eulerian.
    // If odd count is 0, then eulerian
    // Note that odd count can never be 1 for undirected graph
    return (odd)? 1 : 2;
}

void Graph::connectedComponentsFromVertex(int v){
    list<int>::iterator i;

    char temp;

    for (i = adj[v].begin(); i != adj[v].end(); ++i){
        temp = (char)*i + 'a';
        cout << temp << ',';
    }
}

// Function to return the number of
// connected components in an undirected graph
int Graph::NumberOfconnectedComponents()
{

    // Mark all the vertices as not visited
    bool* visited = new bool[V];
    char atual;

    // To store the number of connected components
    int count = 0;
    for (int v = 0; v < V; v++)
        visited[v] = false;

    for (int v = 0; v < V; v++) {
        if (visited[v] == false) {
            atual = (char)v + 'a';
            cout << atual << ',';

            connectedComponentsFromVertex(v);
            cout << endl;
            DFSUtil(v, visited);
            count += 1;
        }
    }

    return count;
}

// Function to run test cases
[[maybe_unused]] void test(Graph &g)
{
    int res = g.isEulerian();
    if (res == 0)
        cout << "graph is not Eulerian\n";
    else if (res == 1)
        cout << "graph has a Euler path\n";
    else
        cout << "graph has a Euler cycle\n";
}

[[maybe_unused]] bool isLetter(char letter){
    return (letter >= 'a' && letter <= 'z' )||(letter >= 'A' && letter <= 'Z' );
}


/*
 * 3
 *
 * 3 1
 * a c
 *
 * 10 10
 * a b
 * a c
 * a g
 * b c
 * c g
 * e d
 * d f
 * h i
 * i j
 * j h
 *
 * 6 4
 * a b
 * b c
 * c a
 * e f
 *
 * */


// Driver program to test above function
int main()
{
    // primeira linha da entrada
    int numTestes;
    cin >> numTestes;


    int numVert, numArestas;
    char verticeOrigemC, verticeDestinoC;
    int verticeOrigem, verticeDestino;

    Graph* totalGrafos[numTestes];

    for(int i = 0; i< numTestes; i++){

        //primeira linha são dois numeros.
        cin >> numVert;
        cin >> numArestas;

        totalGrafos[i] = new Graph(numVert);
        Graph* temp = totalGrafos[i];

        //num arestas é o total de casos da entrada
        for(int j = 0; j < numArestas; j++){
            cin >> verticeOrigemC;
            cin >> verticeDestinoC;

            // convertendo o char em inteiro
            verticeOrigem = (int) verticeOrigemC - 'a';
            verticeDestino = (int) verticeDestinoC - 'a';

            temp->addEdge(verticeOrigem, verticeDestino);
        }


    }

    //printar e fazer os cálculos
    for(int i = 0; i<numTestes; i++){
        cout << "Case #" << i +1<< ":" <<endl;
        cout << totalGrafos[i]->NumberOfconnectedComponents();
        cout << " connected components\n" <<endl;
    }


    return 0;
} 
