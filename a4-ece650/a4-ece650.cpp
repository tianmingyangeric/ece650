#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include <iostream>
#include <string>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <stdlib.h>
#include <memory>
using namespace std;
using namespace Minisat;

vector < vector<int> > defind_edges(string content,int num_vertices){
	vector <int> edge_pair(2);/*define edge pairs */
	vector < vector<int> > edge_storage;
	string edge = content;
  string empty_str = "{}";
  if (edge == empty_str){

    return edge_storage;

  }
	edge.erase(0,2);
	edge.erase(edge.size() - 2,2);
    for (int i = 0; i<edge.size();i++){
		if (edge[i] == '<' || edge[i] == '>'){
			edge.erase(i,1);}
	}
	istringstream f(edge);
    string s;
    int flag = 1;
    while (getline(f, s, ',')) {
        if (stoi(s) >= num_vertices)
           {break;}
    	if (flag == 1) {
    		edge_pair[0] = stoi(s);
    		flag = 0;
    	}
    	else{
    		edge_pair[1] = stoi(s);
    		flag = 1;
    		edge_storage.push_back(edge_pair);
    	}}
     return edge_storage;   
}
void get_vertex_cover(int vertices,vector < vector<int> > edge_storage){

    for (int k = 1; k <= vertices; ++k){
          Minisat::vec<Minisat::Lit> literals;

          Minisat::Solver solver;
          for (int ver = 0; ver< vertices; ++ver){
            for (int k_value = 0; k_value < k; ++k_value){
              static_cast<void>(solver.newVar());
            }
          }
    //At least one vertex is the ith vertex in the vertex cover
    for (int i = 0; i< k; ++i ){
        for (int j =0; j< vertices; ++j){
            literals.push(Minisat::mkLit(Minisat::Var(k*j + i)));
        }
          solver.addClause(literals);
          literals.clear();

    }
    //No one vertex can appear twice in a vertex cover
    for (int m =0;m<vertices;++m){
        for (int p =0;p<k;++p){
            for (int q =0;q<k;++q){
                if(q<p){
                literals.push(~Minisat::mkLit(Minisat::Var(k*m + q)));
                literals.push(~Minisat::mkLit(Minisat::Var(k*m + p)));
                solver.addClause(literals);
                literals.clear();

            }
    }}}
    //No more than one vertex appears in themth position of the vertex cover.
    for (int m =0;m<k;++m){
        for (int p =0;p<vertices;++p){
            for (int q =0;q<vertices;++q){
                if(q<p){
                literals.push(~Minisat::mkLit(Minisat::Var(k*p + m)));
                literals.push(~Minisat::mkLit(Minisat::Var(k*q + m)));
                solver.addClause(literals);
                literals.clear();
            }
    }}}
          for (int j = 0; j < edge_storage.size(); ++j) {
            for (int you = 0; you < k; ++you) {
              literals.push(Minisat::mkLit(Minisat::Var(k*edge_storage[j][0] + you)));
              literals.push(Minisat::mkLit(Minisat::Var(k*edge_storage[j][1] + you)));
            }
            solver.addClause(literals); 
            literals.clear();

          }
          auto sat = solver.solve();

          if (sat) {
            for (int i = 0; i < vertices; ++i)
              for (int j = 0; j < k; ++j) {
                if (!(Minisat::toInt(solver.modelValue(i*k + j))))
                  cout << i << " ";
              }
            cout << endl;
            break;
          }
          
    }
}
int main(){
string command;
string content;
while(true){
	cin >> command>>content;
	vector < vector<int> > edge_storage;
	int vertices;
	if (command == "V"){
		vertices = stoi(content);
	}
	if (command == "E"){
		edge_storage = defind_edges(content,vertices);
    if (edge_storage.size() == 0){
      cout<<"Error: Wrong Edge"<<endl;
    }
    else {

    get_vertex_cover(vertices,edge_storage);}

  }
}
return 0;
}





