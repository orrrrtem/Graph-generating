#include <iostream>
#include "functions.h"



int main() {
    std::cout << "Hello, World!" << std::endl;

    vector <vector < double>> gr, gr2;
    gr = create_graph(10,0.8,100,20);
    print_graph(gr);
    cout << gr.size() << endl;
    for(int i = 0; i < gr.size(); i++)
        cout << (int)gr[0][i] << " ";
    cout << endl;
    cout << endl;

    gr2 = create_block_graph(6,2,0.9,1,100,30,50,30);
    map<int, set<int>> clusters;
    clusters = mix_graph(gr2,6,2);
    for(int i = 0; i < 6; i++) {
        cout << i <<"th cluster: ";
        for_each(
                clusters[i].begin(),
                clusters[i].end(),
                [](int const &j) { std::cout << j << " "; }
        );
        cout << endl;
    }
    cout << endl;
    cout << endl;
    print_graph(gr2);


    return 0;
}