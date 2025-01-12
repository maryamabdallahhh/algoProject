 #include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

 struct Edge {
    int src, dest, weight;
};

 struct Subset {
    int parent, rank;
};

 int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

 void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

 bool compareEdges(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}

 void kruskalMST(vector<Edge>& edges, int V) {
    vector<Edge> result; 
    int e = 0;  
    int i = 0;  

     sort(edges.begin(), edges.end(), compareEdges);

     Subset* subsets = new Subset[V];
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

     while (e < V - 1 && i < edges.size()) {
         Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

         if (x != y) {
            result.push_back(next_edge);
            Union(subsets, x, y);
            e++;
        }
    }

     cout << "Edges in the MST:\n";
    for (auto edge : result)
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;

    delete[] subsets;
}

 int main() {
    int V = 4; 
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}
    };

    kruskalMST(edges, V);

    return 0;
}
