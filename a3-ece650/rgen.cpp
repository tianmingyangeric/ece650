#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include<string.h>
#include<stdio.h>
#include <vector>
#include <fstream>
#include<sstream>
#include <typeinfo>
#include<string>
#include <iostream>
using namespace std;


int random_number(int start, int end, bool positive){
    ifstream urandom("/dev/urandom");

    if (urandom.fail()) {
        cerr << "Error: cannot open /dev/urandom\n";
        exit(0);
        return 1;
    }
    unsigned int num = 42;
    urandom.read((char*)&num, sizeof(int));
    int new_num = num%(end+1-start) + start;
    if (positive == false){
        if (new_num != 0){
            if (new_num%3 == 0)
                new_num = new_num - new_num*2;
        }}

    return new_num;
}


string random_street(int street_num){
    string street_name[25];
    street_name[0] = "St Edward Rd";
    street_name[1] = "Queen Street";
    street_name[2] = "Roxbury Ter";
    street_name[3] = "Champlain";
    street_name[4] = "Cheryl La";
    street_name[5] = "Davis Ct";
    street_name[6] = "Oakburn Ct";
    street_name[7] = "Navarre";
    street_name[8] = "Floydell";
    street_name[9] = "Main Street";
    street_name[10] = "Rushmonde";
    street_name[11] = "MWellsmere Rd";
    street_name[12] = "Islington Ave";
    street_name[13] = "William Parkway";
    street_name[14] = "Winston Ave";
    street_name[15] = "Highway 7";
    street_name[16] = " Harvester";
    street_name[17] = "Bovaid Dr";
    street_name[18] = "Rushmonde";
    street_name[19] = "Hulk Ave";
    street_name[20] = "MacNeil Way";
    street_name[21] = "Pleasanton";
    street_name[22] = "Wellsmere Rd";
    street_name[23] = "Allen Dr";
    street_name[24] = "Ruthven Park";	
    return street_name[street_num];
}

int cross(int x1,int y1,int x2,int y2,int x3,int y3){
	return (x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);
}

bool IsIntersect(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){
		bool result;
	    if(max(x1,x2)>=min(x3,x4) and max(x3,x4)>=min(x1,x2) and max(y1,y2)>=min(y3,y4) and max(y3,y4)>=min(y1,y2)){
	        if(cross(x1,y1,x2,y2,x3,y3)*cross(x1,y1,x2,y2,x4,y4)<=0 && cross(x3,y3,x4,y4,x1,y1)*cross(x3,y3,x4,y4,x2,y2)<=0)
	            result=true;
	        else result=false;}
	    else
	        result=false;
	    return result;
}

bool IsOverlap(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){
	int a;
	int b;

	if ((y2 - y1) == 0){
		 a = 0;}
	else if ((x2 -x1 ) == 0)
		{
			 a = 1;}
	else 
	{ a = (y2-y1)/(x2-x1);}
	if ((y4 - y3) == 0){
		 b = 0;}
	else if ((x4 -x3) == 0)
		{ b = 1;}
	else 
	{ b = (y4-y3)/(x4-x3);}

	if (a == b)
		return true;
	else 
		return false;
}

vector<int> string_array(string coord){
	vector<int> c_array;
	int index = 0;
	string s;
	coord.erase(0,1);
	coord.erase(coord.size()-1,1);
	istringstream f(coord);
	while (getline(f, s, ',')) {
		c_array.push_back(stoi(s));
		index = 1;
	  }
return c_array;


}
string random_coordinate(vector<vector <string> > street_coordinate,vector <string> coordinate,int k){
    string coord[30];
    int num =0;
    int num2 =0;
    string coord_1;
    string coord_2;
    for (int o=0; o <30;o ++){
        for (int p=0; p <2;p++)
        num = random_number(0,k,false);
        coord_1 = to_string(num);
        num2 = random_number(0,k,false);
        coord_2 = to_string(num2);
        coord[o] = "("+coord_1+","+coord_2+")";
    }
if (coordinate.size() == 0)
	return coord[rand()%30];
else if (street_coordinate.size() == 0 && coordinate.size() == 1){
	int counter = 0;
	while (counter <= 25){
		string coord_str = coord[rand()%30];
		counter = counter + 1;
		if (coordinate[0] != coord_str)
			return coord_str;
		}
	}
for (int count=0; count < 30; count++){
	string coord_str = coord[count];
	bool flag = true;
	for (int m=0; m < coordinate.size()-1; m++){
		int n = m + 1;
		bool is_intersect =  IsIntersect(string_array(coordinate[m])[0],string_array(coordinate[m])[1],\
			string_array(coordinate[n])[0],string_array(coordinate[n])[1],\
			string_array(coordinate.back())[0],string_array(coordinate.back())[1],\
			string_array(coord_str)[0],string_array(coord_str)[1]);
		bool is_overlap = IsOverlap(string_array(coordinate[m])[0],string_array(coordinate[m])[1],\
			string_array(coordinate[n])[0],string_array(coordinate[n])[1],\
			string_array(coordinate.back())[0],string_array(coordinate.back())[1],\
			string_array(coord_str)[0],string_array(coord_str)[1]);

		if (((is_intersect == true) && (n != coordinate.size()-1)) || (coord_str == coordinate.back()) )
           {
            flag = false;}}
	for (int i =0; i < street_coordinate.size(); i++){
		for (int j =0; j < street_coordinate[i].size()-1; j++){
		bool intersect =  IsIntersect(string_array(street_coordinate[i][j])[0],string_array(street_coordinate[i][j])[1],\
			string_array(street_coordinate[i][j+1])[0],string_array(street_coordinate[i][j+1])[1],\
			string_array(coordinate.back())[0],string_array(coordinate.back())[1],\
			string_array(coord_str)[0],string_array(coord_str)[1]);
		bool overlap = IsOverlap(string_array(street_coordinate[i][j])[0],string_array(street_coordinate[i][j])[1],\
            string_array(street_coordinate[i][j+1])[0],string_array(street_coordinate[i][j+1])[1],\
            string_array(coordinate.back())[0],string_array(coordinate.back())[1],\
            string_array(coord_str)[0],string_array(coord_str)[1]);

        if ((intersect == true && overlap == true ))
			{flag = false;}
	}}
	
	if (flag == true)
		{
			return coord_str;}

}
    cerr << "Error: can not generate correct number"<<endl;
    exit(0);
	return coord[rand()%30];
}
vector <string> split_lines(string command_line)
{
 	vector <string> strings;
 	istringstream f(command_line);
    string s;    
    while (getline(f, s, ' ')) {
        strings.push_back(s);}
return strings;}
int random_waittime(int time){
	sleep(time);
	return 0;
}
int main(int argc, char *argv[]){
    vector<vector <string> > street_coordinate;
	int default_street = 10;
    int default_time = 5;
    int default_lineseg = 5;
    int default_range = 20;
    for (int i=0; i < argc;i++){
    	if (strcmp( argv[i], "-s") == 0){
    		default_street = stoi(argv[i+1]);
    	}
    	else if (strcmp( argv[i], "-n") == 0 ){
    		default_lineseg = stoi(argv[i+1]);
    	}
    	else if (strcmp( argv[i], "-l") == 0 ){
    		default_time = stoi(argv[i+1]);
    	}
    	else if (strcmp( argv[i], "-c") == 0){
    		default_range = stoi(argv[i+1]);
    	}
    }
    int rand_street = random_number(2,default_street,true);
    for (int street_num = 0; street_num < rand_street; street_num ++){
    	string new_string;
    	string street_name = random_street(street_num);
    	int rand_coord = random_number(1,default_lineseg,true);
    	vector <string> coordinate;
    	for (int segment = 0; segment < rand_coord+1; segment ++){
    		string line_segment = random_coordinate(street_coordinate,coordinate,default_range);
    		coordinate.push_back(line_segment);
    		new_string = new_string + " " + line_segment;
    	}
		cout<<"a " <<"\""<< street_name<< "\""<< new_string<<endl;;
		street_coordinate.push_back(coordinate);
    	default_time = random_number(5,default_time,true);
    	random_waittime(default_time);
    }
    random_waittime(default_time);
    cout << "g"<<endl;

while(true){

}

 return 0;}