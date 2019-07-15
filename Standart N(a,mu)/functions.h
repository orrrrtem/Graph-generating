
#ifndef CPPPROJECT_FUNCTIONS_H
#define CPPPROJECT_FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <random>
#include <math.h>
#include <set>
#include <string>

using namespace std;



//creating graph with probability of edge creating p_in. Edge's wight characteristics are math expection and dispersion.
vector<vector<double>> create_graph(int n, double p_in, double mu_weight, double dispersion_of_weight){
    if(n < 0)
        exit(-1);
    if(p_in < 0 || p_in > 1)
        exit(-1);
    vector<vector<double>> graph(n, vector<double> (n, 0));

    random_device generator;
    bernoulli_distribution distribution_of_p_in(p_in);
    normal_distribution<double> distribution_of_weight(mu_weight, dispersion_of_weight);

    for(int i = 0; i < graph.size(); i++) {
        for (int j = i+1; j < graph.size(); j++){
            if (distribution_of_p_in(generator)){
                int k = 0;
                while(graph[i][j]<=0 || k < 100) {
                    graph[i][j] = distribution_of_weight(generator);
                    k++;
                }
                if(graph[i][j]<=0)
                    graph[i][j] = abs(distribution_of_weight(generator));
                graph[j][i]=graph[i][j];
            }
        }

    }


    return graph;

}

//creating block structure graph , where each block is subgraph from create_graph function.
// With addition of p_out - probability of edge between clusters and their weight characteristics
vector<vector<double>> create_block_graph(int num_clusters, int num_members,  double p_in, double p_out, double mu_weight_in, double dispersion_of_weight_in, double mu_weight_out, double dispersion_of_weight_out){
    if(num_clusters < 0)
        exit(-1);
    if(num_members < 0)
        exit(-1);
    if(p_out < 0 || p_out > 1)
        exit(-1);

    vector<vector<double>> graph(num_clusters * num_members, vector<double> (num_clusters*num_members, 0));
    vector<vector<double>> tmp;

    random_device generator;
    bernoulli_distribution distribution_of_p_out(p_out);
    normal_distribution<double> distribution_of_weight_out(mu_weight_out, dispersion_of_weight_out);

    for(int k=0; k < num_clusters; k++) {
        //block planting
        tmp = create_graph(num_members, p_in, mu_weight_in, dispersion_of_weight_in);
        for(int i = 0; i < tmp.size(); i++)
            for( int j = 0; j < tmp[i].size(); j++)
                graph[k * num_members + i][k * num_members + j] = tmp[i][j];


        //addition of external edges
        for(int i = k * num_members; i < tmp.size() + k * num_members; i++)
            for(int j = (k+1) * num_members; j < graph.size(); j++)
                if (distribution_of_p_out(generator)){
                    int count = 0;
                    while(graph[i][j]<=0 || count < 100) {
                        graph[i][j] = distribution_of_weight_out(generator);
                        count++;
                    }
                    if(graph[i][j]<=0)
                        graph[i][j] = abs(distribution_of_weight_out(generator));
                    graph[j][i]=graph[i][j];
                }
    }

    return graph;
}







map<int, set<int>> mix_graph(vector<vector<double>> graph, int num_clusters, int num_members){

    random_device generator;
    uniform_int_distribution<int> distribution(0,graph.size());

    map<int, set<int> > clusters;
    for(int i = 0; i < num_clusters; i++) {
        set<int> tmp;
        for (int j = i * num_members; j < (i + 1) * num_members; j++)
            tmp.insert(j);
        clusters.insert(make_pair(i,tmp));
        tmp.clear();
    }

    int rn; //random number
    for(int i = 0; i < num_clusters; i++){
        rn = distribution(generator);
        clusters.find(rn);
        int index = -2;

        //searching for node's cluster index4321§
        for(int k = 0; k < num_clusters; k++){
            for_each(
                clusters[k].begin(),
                clusters[k].end(),
                [&index,rn,k](set <int> nodes) {
                    std::set<int>::iterator it;
                    it = nodes.find(rn);
                    if (it != nodes.end())
                        index = k;
                }
            );
        }

        //exchange nodes between clusters

    }

    return clusters;
}


vector<set<int> >graph_mix(vector<vector<double>> graph, int num_clusters, int num_members){
    random_device generator;
    uniform_int_distribution<int> distribution(0,graph.size());

}






void print_graph(vector<vector<double>> gr){
    for(int i = 0; i < gr.size(); i++) {
        for (int j = 0; j < gr.size(); j++)
            cout << (int)gr[i][j] << "\t";
        cout << endl;
    }
}


#endif //CPPPROJECT_FUNCTIONS_H
