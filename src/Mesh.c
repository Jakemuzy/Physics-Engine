#include "Mesh.h"

Map* Meshs = NULL;

/* ----- Lifetime Handling ----- */ 

void MERR(char* msg) {
    printf("%s\n", msg);
}

/* ----- Mesh Logic ----- */

Mesh* MeshInit(char* name, float* points, int vcount, bool hasColor, bool hasNormal, bool hasTexture)
{
    if (!Meshs) 
        Meshs = MapInit();

    Mesh* mesh = malloc(sizeof(Mesh));
    mesh->name = strdup(name);
    mesh->vertCount = vcount;

    int stride = sizeof(float) * (3 + (hasColor?3:0) + (hasNormal?3:0) + (hasTexture?3:0));


    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &mesh->VBO);
    glBindVertexArray(mesh->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, vcount * stride, points, GL_STATIC_DRAW);

    unsigned int index = 0;
    long int offset = 0; 

    glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
    glEnableVertexAttribArray(index++);
    offset += 3 * sizeof(float);

    if (hasColor) {
        glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
        glEnableVertexAttribArray(index++);
        offset += 3 * sizeof(float);
        mesh->color = true;
    } else mesh->color = false;

    if (hasNormal) {
        glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
        glEnableVertexAttribArray(index++);
        offset += 3 * sizeof(float);
        mesh->normal = true;
    } else mesh->normal = false;

    if (hasTexture) {
        glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
        glEnableVertexAttribArray(index++);
        mesh->tcoord = true;
    } else mesh->tcoord = false; 

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    MapPush(Meshs, name, (void*)mesh);
    return mesh;
}


void MeshDraw(char* name)
{
    Mesh* mesh = (Mesh*)MapLook(Meshs, name);
    if(!mesh) { MERR("Mesh with name does not exist\n"); return; }


    glBindVertexArray(mesh->VAO);
    glDrawArrays(GL_TRIANGLES, 0, mesh->vertCount);
}

void MeshsTerminate()
{
    /* 
    TODO:
    glDeleteVertexArrays(1, mesh->VAO);
    glDeleteBuffers(1, mesh->VBO);
    */

    MapFree(Meshs);
}
