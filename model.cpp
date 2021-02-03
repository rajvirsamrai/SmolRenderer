#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "model.h"


/*
Given a filepath, load the corresponding model data. This load function can
handle models saved in the Wavefront .obj file format.
*/
void Model::load(char* filename){
    std::ifstream data (filename);
    std::string line;
    std::string token;
    std::string first_two_chars;

    if(!data.is_open()){
        std::cerr << "Unable to open the file with the following path: " << filename << "\n";
        exit(1);
    }

    while(std::getline(data, line)){
        std::stringstream stream_of_line(line);
        first_two_chars = line.substr(0, 2);
        if (first_two_chars == "v "){
            Vec3 new_vert;

            stream_of_line >> token;
            stream_of_line >> token;
            new_vert.x = std::stof(token);
            stream_of_line >> token;
            new_vert.y = std::stof(token);
            stream_of_line >> token;
            new_vert.z = std::stof(token);

            this->vertices.push_back(new_vert);
        } else if (first_two_chars == "f "){
            Face new_face;
            int i = 0;

            stream_of_line >> token;
            while(stream_of_line >> token){
                int first_slash = token.find("/");
                int second_slash = token.find("/", first_slash+1);
                new_face.v[i] = std::stoi(token.substr(0, first_slash));
                new_face.vt[i] = std::stoi(token.substr(first_slash+1, second_slash-first_slash-1));
                new_face.vn[i] = std::stoi(token.substr(second_slash+1, -1));
                i++;
            }

            this->faces.push_back(new_face);
        }
    }

    data.close();
}