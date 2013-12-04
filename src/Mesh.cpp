#include "Mesh.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void Mesh::load( const char* filename, const int numBoids, const float vDistance )
{
 
	cout << "Loading mesh"<<endl;
	string line;
	ifstream file(filename);
	Vector3f v;
	Vector3f center = Vector3f(0,0,0);
	Tuple3u vf;
	if( file.is_open()){
		while( getline(file, line)){
			stringstream ss(line);
			string start;
			ss >> start;
			if(start == "v"){
				ss >> v[0] >> v[1] >> v[2];
				vertices.push_back(v);
				center+= v;
				cout << "Vertex = " ;
				v.print();
			}
			else if(start == "f"){
				ss >> vf[0] >> vf[1] >> vf[2];
				faces.push_back(vf);
			}
		}
		center = center/vertices.size();
		bool rep = true;
		while(rep){
			rep = false;
			for (int i = 0; i <faces.size(); i++){
				Vector3f faceCenter = (0,0,0);
				for(int j = 0; j < 3; j++){
					faceCenter += vertices[faces[i][j]]/3.0f;
				}
				float distToCenter = 0;
				for(int j = 0; j < 3; j++){
					distToCenter = max(distToCenter, (faceCenter-vertices[faces[i][j]]).abs());
				}
				if(distToCenter > 1.5*vDistance){
					vertices.push_back(faceCenter);
					for(int k = 0; k < 3; k ++){
						vf[0] = faces[i][(0+k)%3];
						vf[1] = faces[i][(1+k)%3];
						vf[2] = vertices.size()-1;
						faces.push_back(vf);	
					}
					faces.erase(faces.begin()+i);
					rep = true;
				}
			}
			}
		
	}
}

void Mesh::addPoints(const int index, const float vDistance){
	
}
