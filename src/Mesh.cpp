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
	Vector3f shapeCenter = Vector3f(0,0,0);
	Tuple3u vf;
		
	std::vector<Tuple3u> uFaces;
	if( file.is_open()){
		while( getline(file, line)){
			stringstream ss(line);
			string start;
			ss >> start;
			if(start == "v"){
				ss >> v[0] >> v[1] >> v[2];
				vertices.push_back(v);
				shapeCenter+= v;
				cout << "Vertex = " ;
				v.print();
			}
			else if(start == "f"){
				ss >> vf[0] >> vf[1] >> vf[2];
				uFaces.push_back(vf);
				cout << "vf is " << vf[0] << "," <<vf[1] << "," << vf[2] << endl;
			}
		}
		shapeCenter = shapeCenter/vertices.size();
		while(uFaces.size() > 0) {
		  cout << uFaces.size() << endl;
		  Tuple3u f = uFaces.back();
		  uFaces.pop_back();
		  Vector3f center = (0,0,0);
		  for(int j = 0; j < 3; j++) {
		    center += vertices[f[j] - 1];
		    vertices[f[j] - 1].print();
		  }
		  center = center / 3.0f;
		  float radius = 0.0f;
		  for(int j = 0; j < 3; j++)
		    radius = max(radius, (vertices[f[j] - 1] - center).abs());
		  cout << radius << endl;
		  center.print();
		  
		  if(radius > vDistance) {
		    int n = vertices.size() + 1;
		    vertices.push_back((vertices[f[1] - 1] + vertices[f[0] - 1]) / 2.0f);
		    vertices.push_back((vertices[f[2] - 1] + vertices[f[1] - 1]) / 2.0f);
		    vertices.push_back((vertices[f[0] - 1] + vertices[f[2] - 1]) / 2.0f);
		    uFaces.push_back(Tuple3u(n, n+1, n+2));
		  }
		  faces.push_back(f);
		}
		vertices.push_back(shapeCenter);
	}
}


