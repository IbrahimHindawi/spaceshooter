#pragma once

#include <math.h>
#include <glad/glad.h>
#include <cglm/vec3.h>
#include <cglm/affine.h>
#include <cglm/cam.h>
#include <cglm/mat4.h>
#include <cglm/vec3.h>

#include "core.h"
#include "hkArray.h"

typedef struct {
    u32 vao;
    u32 vbo;
    u32 ebo;
    u32 vertex_count;
    u32 index_count;
    vec3 pos;
    vec3 vel;
} Mesh;

/*
 * Create a mesh that has Pos & UVs.
 */
Mesh meshCreate(f32 *vertices, u32 vertex_count, i32 *indices, u32 index_count) {
    Mesh mesh = {0};
    mesh.vertex_count = vertex_count;
    mesh.index_count = index_count;

    glGenVertexArrays(1, &mesh.vao);
    glGenBuffers(1, &mesh.vbo);
    glGenBuffers(1, &mesh.ebo);

    glBindVertexArray(mesh.vao);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertex_count * sizeof(f32), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.index_count * sizeof(i32), indices, GL_STATIC_DRAW);

    // pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);  

    // tex
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)(sizeof(f32) * 3));
    glEnableVertexAttribArray(1);  

    glBindVertexArray(0);

    return mesh;
}

void meshRender(Mesh *mesh, u32 texture, u32 shader_program) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glUseProgram(shader_program);
    glBindVertexArray(mesh->vao);
    glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

#define M 22
#define N (M * M)
typedef struct {
    u32 vao[N];
    u32 vbo[N];
    u32 ebo[N];
    u32 vertex_count[N];
    u32 index_count[N];
    vec3 pos[N];
    vec3 vel[N];
    mat4 model[N];
} Meshes;

typedef struct {
    mat4 view;
    // mat4 proj;
} XForms;

void meshesCreate(Meshes *meshes, f32 *vertices, u32 vertex_count, i32 *indices, u32 index_count) {
    for(i32 i = 0; i < N; ++i) {
        meshes->vertex_count[i] = vertex_count;
        meshes->index_count[i] = index_count;

        glGenVertexArrays(1, &meshes->vao[i]);
        glGenBuffers(1, &meshes->vbo[i]);
        glGenBuffers(1, &meshes->ebo[i]);

        glBindVertexArray(meshes->vao[i]);

        glBindBuffer(GL_ARRAY_BUFFER, meshes->vbo[i]);
        glBufferData(GL_ARRAY_BUFFER, meshes->vertex_count[i] * sizeof(f32), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshes->ebo[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshes->index_count[i] * sizeof(i32), indices, GL_STATIC_DRAW);

        // pos
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)0);
        glEnableVertexAttribArray(0);  

        // tex
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)(sizeof(f32) * 3));
        glEnableVertexAttribArray(1);  

        glBindVertexArray(0);
    }
    return;
}
