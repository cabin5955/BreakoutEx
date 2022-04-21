//
//  mesh.cpp
//  BreakoutEx
//
//  Created by chen caibin on 2022/3/6.
//

#include "mesh.hpp"
#include <stdio.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "global.hpp"

using namespace std;

static Mesh *build_mesh(
        vector<glm::vec3> &positions, vector<glm::vec2> &texcoords, vector<glm::vec3> &normals,
        vector<glm::vec4> &tangents, vector<glm::vec4> &joints, vector<glm::vec4> &weights,
        vector<int> &position_indices, vector<int> &texcoord_indices, vector<int> &normal_indices)
{
    glm::vec3 bbox_min = glm::vec3(+1e6, +1e6, +1e6);
    glm::vec3 bbox_max = glm::vec3(-1e6, -1e6, -1e6);
    unsigned long num_indices = position_indices.size();
    unsigned long num_faces = num_indices / 3;
    Vertex *vertices;
    Mesh *mesh;
    int i;

    assert(num_faces > 0 && num_faces * 3 == num_indices);
    assert(position_indices.size() == num_indices);
    assert(texcoord_indices.size() == num_indices);
    assert(normal_indices.size() == num_indices);

    vertices = (Vertex*)malloc(sizeof(Vertex) * num_indices);
    for (i = 0; i < num_indices; i++)
    {
        int position_index = position_indices[i];
        int texcoord_index = texcoord_indices[i];
        int normal_index = normal_indices[i];
        
        assert(position_index >= 0 && position_index < positions.size());
        assert(texcoord_index >= 0 && texcoord_index < texcoords.size());
        assert(normal_index >= 0 && normal_index < normals.size());
        
        vertices[i].position = positions[position_index];
        vertices[i].texcoord = texcoords[texcoord_index];
        vertices[i].normal = normals[normal_index];
    
        if (tangents.size()>0) {
            int tangent_index = position_index;
            assert(tangent_index >= 0 && tangent_index < tangents.size());
            vertices[i].tangent = tangents[tangent_index];
        } else {
            vertices[i].tangent = glm::vec4(1, 0, 0, 1);
        }

        if (joints.size()>0) {
            int joint_index = position_index;
            assert(joint_index >= 0 && joint_index < joints.size());
            vertices[i].joint = joints[joint_index];
        } else {
            vertices[i].joint = glm::vec4(0, 0, 0, 0);
        }

        if (weights.size()>0) {
            int weight_index = position_index;
            assert(weight_index >= 0 && weight_index < weights.size());
            vertices[i].weight = weights[weight_index];
        } else {
            vertices[i].weight = glm::vec4(0, 0, 0, 0);
        }
        bbox_min = glm::min(bbox_min, vertices[i].position);
        bbox_max = glm::max(bbox_max, vertices[i].position);
        
    }

    mesh = (Mesh*)malloc(sizeof(Mesh));
    mesh->num_faces = (int)num_faces;
    mesh->vertices = vertices;
    mesh->center = (bbox_min+bbox_max)/ 2.0f;

    return mesh;
}

static Mesh *load_obj(const char *filename) {
    vector<glm::vec3> positions ;
    vector<glm::vec2> texcoords;
    vector<glm::vec3> normals;
    vector<glm::vec4> tangents;
    vector<glm::vec4> joints;
    vector<glm::vec4> weights;
    vector<int> position_indices;
    vector<int> texcoord_indices;
    vector<int> normal_indices;
    char line[LINE_SIZE];
    Mesh *mesh;
    FILE *file;

    file = fopen(filename, "rb");
    assert(file != NULL);
    while (1) {
        int items;
        if (fgets(line, LINE_SIZE, file) == NULL) {
            break;
        } else if (strncmp(line, "v ", 2) == 0) {               /* position */
            glm::vec3 position;
            items = sscanf(line, "v %f %f %f",
                           &position.x, &position.y, &position.z);
            assert(items == 3);
            positions.push_back(position);
            
        } else if (strncmp(line, "vt ", 3) == 0) {              /* texcoord */
            glm::vec2 texcoord;
            items = sscanf(line, "vt %f %f",
                           &texcoord.x, &texcoord.y);
            assert(items == 2);
            texcoords.push_back(texcoord);
        } else if (strncmp(line, "vn ", 3) == 0) {              /* normal */
            glm::vec3 normal;
            items = sscanf(line, "vn %f %f %f",
                           &normal.x, &normal.y, &normal.z);
            assert(items == 3);
            normals.push_back(normal);
        } else if (strncmp(line, "f ", 2) == 0) {               /* face */
            int i;
            int pos_indices[3], uv_indices[3], n_indices[3];
            items = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                           &pos_indices[0], &uv_indices[0], &n_indices[0],
                           &pos_indices[1], &uv_indices[1], &n_indices[1],
                           &pos_indices[2], &uv_indices[2], &n_indices[2]);
            assert(items == 9);
            for (i = 0; i < 3; i++) {
                position_indices.push_back(pos_indices[i] - 1);
                texcoord_indices.push_back(uv_indices[i] - 1);
                normal_indices.push_back(n_indices[i] - 1);
            }
        } else if (strncmp(line, "# ext.tangent ", 14) == 0) {  /* tangent */
            glm::vec4 tangent;
            items = sscanf(line, "# ext.tangent %f %f %f %f",
                           &tangent.x, &tangent.y, &tangent.z, &tangent.w);
            assert(items == 4);
            tangents.push_back(tangent);
        } else if (strncmp(line, "# ext.joint ", 12) == 0) {    /* joint */
            glm::vec4 joint;
            items = sscanf(line, "# ext.joint %f %f %f %f",
                           &joint.x, &joint.y, &joint.z, &joint.w);
            assert(items == 4);
            joints.push_back(joint);
        } else if (strncmp(line, "# ext.weight ", 13) == 0) {   /* weight */
            glm::vec4 weight;
            items = sscanf(line, "# ext.weight %f %f %f %f",
                           &weight.x, &weight.y, &weight.z, &weight.w);
            assert(items == 4);
            weights.push_back(weight);
        }
        UNUSED_VAR(items);
    }
    fclose(file);

    mesh = build_mesh(positions, texcoords, normals, tangents, joints, weights,
                      position_indices, texcoord_indices, normal_indices);

    return mesh;
}

const char *get_extension(const char *filename) {
    const char *dot_pos = strrchr(filename, '.');
    return dot_pos == NULL ? "" : dot_pos + 1;
}

Mesh *mesh_load(const char *filename) {
    const char *extension = get_extension(filename);
    if (strcmp(extension, "obj") == 0) {
        char fullPath[256] = {0};
        strcpy(fullPath, Global::RES_PATH);
        char *fullFilename = strcat(fullPath, filename);
        return load_obj(fullFilename);
    } else {
        assert(0);
        return NULL;
    }
}

void mesh_release(Mesh *mesh) {
    free(mesh->vertices);
    free(mesh);
}

/* vertex retrieving */

int mesh_get_num_faces(Mesh *mesh) {
    return mesh->num_faces;
}

Vertex *mesh_get_vertices(Mesh *mesh) {
    return mesh->vertices;
}

glm::vec3 mesh_get_center(Mesh *mesh) {
    return mesh->center;
}
