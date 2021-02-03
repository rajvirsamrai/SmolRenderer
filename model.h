#ifndef MODEL_H
#define MODEL_H

#include <vector>


/*
Represents a vector in R^3
*/
class Vec3 {
    public:
        float x;
        float y;
        float z;
};

/*
Represents a face. In the context of computer graphics and according to
Wikipedia a face is "A closed set of edges, in which a triangle face has three
edges, and a quad face has four edges." This class represents a triangle face.
*/
class Face {
    public:
        int v[3];
        int vt[3];
        int vn[3];
};

/*
Represents a 3D model as two arrays. The first holds vertices. The second holds
faces. Can load models saved in the Wavefront .obj file format.
*/
class Model {
    public:
        std::vector<Vec3> vertices;
        std::vector<Face> faces;
        void load(char* filename);
};

#endif