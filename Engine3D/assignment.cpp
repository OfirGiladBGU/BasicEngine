#include "assignment.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "../Game/game.h"

using namespace std;
using namespace glm;

void SceneData::read_scene(string file_name) {
    int index = -1;
    string text_line, text_argument;
    vector<string> scene_line;
    ifstream scene_file(file_name);

    cout << "File data:" << endl;

    // Use a while loop together with the getline() function to read the file line by line
    while (getline(scene_file, text_line)) {
        cout << text_line << endl;

        std::stringstream text_line_stream(text_line);

        while (getline(text_line_stream, text_argument, ' ')) {
            if (index == 4) {
                scene_data.push_back(scene_line);
                scene_line.clear();
            }
            scene_line.push_back(text_argument);
            index = (index + 1) % 5;
        } 
    }
    for (int i = 0; i < scene_data.size(); i++) {
        // e = eye - XYZ + Bonus Mode Flag
        if (scene_data[i][0] == "e") {
            eye = vec3(stof(scene_data[i][1]), stof(scene_data[i][2]), stof(scene_data[i][3]));
            bonus_mode_flag = stof(scene_data[i][4]);
        }
        // a = ambient - RGBA
        if (scene_data[i][0] == "a") {
            ambient = vec4(stof(scene_data[i][1]), stof(scene_data[i][2]), stof(scene_data[i][3]), stof(scene_data[i][4]));
        }
        // r = reflective object - XYZR
        if (scene_data[i][0] == "r") {
            reflective_objects.push_back(vec4(stof(scene_data[i][1]), stof(scene_data[i][2]), stof(scene_data[i][3]), stof(scene_data[i][4])));
        }
        // t = transparent object - XYZR
        if (scene_data[i][0] == "t") {
            transparent_objects.push_back(vec4(stof(scene_data[i][1]), stof(scene_data[i][2]), stof(scene_data[i][3]), stof(scene_data[i][4])));
        }
        // o = object - XYZR (R>0 -> Spheres) / ABCD (D<0 -> Planes)
        if (scene_data[i][0] == "o") {
            objects.push_back(vec4(stof(scene_data[i][1]), stof(scene_data[i][2]), stof(scene_data[i][3]), stof(scene_data[i][4])));
        }
        // c = color (ambient and diffuse of object) - RGBA (A -> Shininess)
        if (scene_data[i][0] == "c") {
            colors.push_back(vec4(stof(scene_data[i][1]), stof(scene_data[i][2]), stof(scene_data[i][3]), stof(scene_data[i][4])));
        }
        // d = direction (of light sources)
        if (scene_data[i][0] == "d") {
            directions.push_back(vec4(stof(scene_data[i][1]), stof(scene_data[i][2]), stof(scene_data[i][3]), stof(scene_data[i][4])));
        }
        // p = position (of spotlights only) - XYZW
        if (scene_data[i][0] == "p") {
            positions.push_back(vec4(stof(scene_data[i][1]), stof(scene_data[i][2]), stof(scene_data[i][3]), stof(scene_data[i][4])));
        }
        // i = intensity (of light sources) - RGBA
        if (scene_data[i][0] == "i") {
            intensities.push_back(vec4(stof(scene_data[i][1]), stof(scene_data[i][2]), stof(scene_data[i][3]), stof(scene_data[i][4])));
        }
    }    
}

void SceneData::find_pixel_size(int width, int height) {
    image_width = width;
    image_width = height;

    pixel_width = 2 / width;
    pixel_height = 2 / height;
}

void SceneData::ImageRayCasting() {
    //vec2 point_on_screen = vec2(1 - (pixel_width / 2), 1 - (pixel_height / 2));

    for (float i = 0; i < image_width; i++) {
        for (float j = 0; j < image_height; j++) {
            vec3 Ray = ConstructRayThroughPixel(i, j);

        }
    }
}

// top-left (-1, 1)
vec3 SceneData::ConstructRayThroughPixel(int i, int j) {
    vec3 top_left_point = vec3(-1 + (pixel_width / 2), 1 - (pixel_height / 2), 0);

    vec3 hit_on_screen = top_left_point + vec3(i * pixel_width, -1 * (j * pixel_height), 0);

    // 

    return hit_on_screen;
}

Image RayCast(Scene scene, int width, int height)
{
    Image image = new Image(width, height);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            vec3 ray = ConstructRayThroughPixel(i, j);
            vec3 hit = FindIntersection(ray, scene);
            image[i][j] = GetColor(scene, ray, hit);
        }
    }
    return image;
}

vec3 ConstructRayThroughPixel(int i, int j) {

}

vec3 FindIntersection(vec3 ray, scene);