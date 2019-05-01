#include <iostream>
#include<string.h>
#include<string>
#include<stdio.h>
#include <vector>
#include<sstream>
#include <typeinfo>
#include <regex>
#include <regex.h>
#include <queue> 
#include <deque>     
#include <list>      
using namespace std;

class Storage {
  public:
    int amount_vertices;
    vector<int> edge_pair_storage;
} rect;

bool define_edges(vector <string> command, vector <int> edge_storage[],int num_vertices)
{
	vector <int> edge_pair(2);/*define edge pairs */
	string edge = command[1];
    string empty_str = "{}";
    if (edge == empty_str){
        return false;}
	edge.erase(0,2);
	edge.erase(edge.size() - 2,2);
    for (int i = 0; i<edge.size();i++){
		if (edge[i] == '<' || edge[i] == '>'){
			edge.erase(i,1);}
	}
    /* pharse the command, delete {},<> and split with , in commands */
 	istringstream f(edge);
    string s;
    int flag = 1;
    while (getline(f, s, ',')) {
        if (stoi(s) >= num_vertices)
           { cout<<"Error: Edge is greater than number of vertices"<<endl;
            return false;}
    	if (flag == 1) {
    		edge_pair[0] = stoi(s);
    		flag = 0;
    	}
    	else{
    		edge_pair[1] = stoi(s);
    		flag = 1;
    		edge_storage[edge_pair[0]].push_back(edge_pair[1]);
    		edge_storage[edge_pair[1]].push_back(edge_pair[0]);
    	}}
     return true;   
}
bool Breadth_First_Search(vector<int> edge_storage[], int start, int end, int num_vertices,int array_p[]) 
{ /* use breadth first search to visit all vertices */

    list<int> queue; 
    bool visited[num_vertices]; 
    for (int i = 0; i < num_vertices; i++) { 
        visited[i] = false; 
        array_p[i] = -1;} 
    visited[start] = true; 
    queue.push_back(start); 
      while (!queue.empty()) { 
        int a = queue.front(); 
        queue.pop_front(); 
        for (int i = 0; i < edge_storage[a].size(); i++) { 
            if (visited[edge_storage[a][i]] == false) { 
                visited[edge_storage[a][i]] = true; 
                array_p[edge_storage[a][i]] = a; 
                queue.push_back(edge_storage[a][i]); 
                if (edge_storage[a][i] == end) 
                   return true; 
            } 
        } 
    } 
    return false; 
} 

void Shortest_Path(vector<int> edge_storage[], int start,  int end, int num_vertices) 
{   /* find and print the shortest path */
    int array_p[num_vertices]; 
    if (Breadth_First_Search(edge_storage, start, end, num_vertices, array_p) == false) { 
        cout << "Error: Path do not exit"<<endl;
        return; } 
    // vector path stores the shortest path 
    vector<int> s_path; 
    int tmp = end; 
    s_path.push_back(tmp); 
    while (array_p[tmp] != -1) { 
        s_path.push_back(array_p[tmp]); 
        tmp = array_p[tmp]; 
    } 
    for (int i = s_path.size() - 1; i >= 0; i--) {
        cout << s_path[i]; 
        if (i != 0)
            cout << "-";}
    cout <<endl;
} 
vector <string> split_lines(string command_line)
/* use to get input and sepreate the action and values */

{
 	vector <string> strings;
 	istringstream f(command_line);
    string s;    
    while (getline(f, s, ' ')) {
        strings.push_back(s);}
return strings;}

int main()
{   int num_vertices;
    vector<int> edge_storage[10000];
	while(true){
		char command_line[99999];
	 	cin.getline(command_line, 99999);
	 	string str(command_line);
		vector<string> command = split_lines(command_line);
        if ((command[0][0]) != 's'){
            cout<< command_line<<endl;
        }
        /* determine the sepcific action.*/
		switch(command[0][0]){
         /* V : define number of vertices */
		case 'V':{
            for (int i = 0; i < 10000; i++){
                edge_storage[i].clear();}
			num_vertices = stoi(command[1]);
	    	break;}
        /* E : define edges */
		case 'E':
			{ for (int i = 0; i < 10000; i++){
                edge_storage[i].clear();}
				if (define_edges(command, edge_storage,num_vertices))
			         {
                        break;}
                else {
                num_vertices = 0;
                for (int i = 0; i < 10000; i++){
                edge_storage[i].clear();
                }
                break;}
        }
         /* s : find and print the shortest path */
		case 's':
        {
		  Shortest_Path(edge_storage, stoi(command[1]), stoi(command[2]), num_vertices);  
			break;}
		default : 
			cout << "Error: Wrong Input !!!" << endl;
		}
}
 	return 0;}