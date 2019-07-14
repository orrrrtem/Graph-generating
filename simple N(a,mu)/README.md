# Creating block-partitioning graph with addition settings of in,out weights.
Here, both weights are created with standard normal distribution.

Procedure is in few paths: 
1.Creating subgraphs, which nodes will be in one cluster, lately.
2. The union of subgraphs in one big graph with adding them in order on main diagonal of adjetency matrix. All other edges are filled with zeroes.
3. Creating edges out of clusters with standart normal distribution with another EX, DX.

Next path is not implemented due to the absence of quality affect.
4. Mixing nodes, but saving information about clusters memberships. So, this step was created to break diaganal kind of adjetency matrix wich can probably disrupt measurement accuracy.
