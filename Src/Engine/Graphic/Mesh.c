#include "Mesh.h"
#include "../Core/NanoIO.h"

#define LINE_READED_BUFF_SIZE 128

GLuint mesh_genVAO(Mesh* mesh) {
	GLuint vbo;
	GLuint ebo;
	GLuint vao;
	uint count = 0;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	GLsizeiptr v_size = mesh->vertices_count*sizeof(Vec3);
	GLsizeiptr n_size = mesh->normal_count*sizeof(Vec3);
	GLsizeiptr t_size = mesh->uv_count*sizeof(Vec2);
	GLsizeiptr c_size = mesh->color_count*sizeof(uint);
	
	glBufferSubData(GL_ARRAY_BUFFER, 0,v_size, mesh->vertices);
	if (mesh->normal_count)glBufferSubData(GL_ARRAY_BUFFER, v_size, n_size, mesh->normals);
	if (mesh->uv_count)glBufferSubData(GL_ARRAY_BUFFER, v_size + n_size, t_size, mesh->uvs);
	if (mesh->color_count)glBufferSubData(GL_ARRAY_BUFFER, v_size + n_size + t_size, c_size, mesh->colors);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->index_count * sizeof(unsigned int), mesh->index, GL_STATIC_DRAW);


	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	mesh->mesh_id = vao;
	return vao;
}

Mesh* mesh_LoadMesh(string path) {
	FILE* file;
	fopen_s(&file, path, "r");
	char line_readed[LINE_READED_BUFF_SIZE];

	uint vert_count = 0;
	uint index_count = 0;
	uint norm_count = 0;
	uint uv_count = 0;
	uint i;

	Vec3* vertList = (Vec3*)malloc(sizeof(Vec3*) * (mesh_loader_pre_alloc + 1));
	Vec3* normList = (Vec3*)malloc(sizeof(Vec3*) * (mesh_loader_pre_alloc + 1));
	Vec2* uvList   = (Vec2*)malloc(sizeof(Vec2*) * (mesh_loader_pre_alloc + 1));
	Face* faceList = (Face*)malloc(sizeof(Face*) * (mesh_loader_pre_alloc + 1));

	Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
	mesh->color_count = 0;
	mesh->uv_count = 0;
	mesh->normal_count = 0;
	mesh->colors = 0;
	mesh->index_count = 0;
	int index_perline = 0;


	while (!feof(file))
	{
		if (fscanf_s(file, "%s", &line_readed, LINE_READED_BUFF_SIZE)) {

			if (strcmp(line_readed, "v") == 0) {
				fscanf_s(file, "%f %f %f", &vertList[vert_count].x, &vertList[vert_count].y, &vertList[vert_count].z);
				vert_count++;
			}
			else if (strcmp(line_readed, "vn") == 0) {
				fscanf_s(file, "%f %f %f", &normList[norm_count].x, &normList[norm_count].y, &normList[norm_count].z);
				norm_count++;
			}
			else if (strcmp(line_readed, "vt") == 0) {				
				fscanf_s(file, "%f %f", &uvList[uv_count].x, &uvList[uv_count].y);
				uv_count++;
			}
			else if (strcmp(line_readed, "f") == 0) {

				int vert1, tex1, norm1, vert2, tex2, norm2, vert3, tex3, norm3;

				if (uv_count == 0 && norm_count == 0) {
					int matches = fscanf_s(file, "%d %d %d", &vert1, &vert2, &vert3);
					tex1 = norm1 = -1;
					tex2 = norm2 = -1;
					tex3 = norm3 = -1;
				}
				else if (uv_count == 0) {
					int matches = fscanf_s(file, " %d//%d %d//%d %d//%d", &vert1, &norm1, &vert2, &norm2, &vert3, &norm3);
					tex1 = -1;
					tex2 = -1;
					tex3 = -1;
				}
				else if (norm_count == 0) {
					int matches = fscanf_s(file, "%d/%d %d/%d %d/%d", &vert1, &tex1, &vert2, &norm2, &vert3, &norm3);
					norm1 = -1;
					norm2 = -1;
					norm3 = -1;
				}
				else {
					int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d", &vert1, &tex1, &norm1, &vert2, &tex2, &norm2, &vert3, &tex3, &norm3);
				}

				faceList[index_count].face1.x = vert1;
				faceList[index_count].face1.y = tex1;
				faceList[index_count].face1.z = norm1;

				faceList[index_count].face2.x = vert2;
				faceList[index_count].face2.y = tex2;
				faceList[index_count].face2.z = norm2;

				faceList[index_count].face3.x = vert3;
				faceList[index_count].face3.y = tex3;
				faceList[index_count].face3.z = norm3;

				index_count ++;
			}
		}
	}

	mesh->vertices = (float*)malloc(sizeof(Vec3) * vert_count);
	mesh->normals  = (float*)malloc(sizeof(Vec3) * norm_count);
	mesh->uvs      = (float*)malloc(sizeof(Vec2) * uv_count);
	mesh->index    = (int*)malloc  (sizeof(int)*3*index_count);
	mesh->colors = 0;

	mesh->vertices_count = vert_count;
	mesh->normal_count = norm_count;
	mesh->uv_count = uv_count;
	mesh->color_count = 0;
	mesh->index_count = 3 * index_count;

	Face face;
	uint c = 0;
	REPEAT(i,index_count*3,3) {
		 c = i;
		 face = faceList[c];
		 mesh->vertices[c] = vertList[face.face1.x];
		 mesh->uvs[c]      = uvList  [face.face1.y];
		 mesh->normals[c]  = normList[face.face1.z];
		 mesh->index[c] = c;

		 c++;
		 face = faceList[c];
		 mesh->vertices[c] = vertList[face.face2.x];
		 mesh->uvs[c] = uvList[face.face2.y];
		 mesh->normals[c] = normList[face.face2.z];
		 mesh->index[c] = c;

		 c++;
		 face = faceList[c];
		 mesh->vertices[c] = vertList[face.face3.x];
		 mesh->uvs[c] = uvList[face.face3.y];
		 mesh->normals[c] = normList[face.face3.z];
		 mesh->index[c] = c;
	}
	
	free(vertList);
	free(normList);
	free(uvList);
	free(faceList);

	fclose(file);
	//mesh_genVAO(mesh);
	printf("Loaded %s\n", path);
	return mesh;
}

void mesh_PrintMesh(Mesh* mesh) {
	printf("Index Count: %d\n", mesh->index_count);
	printf("Vertex Count: %d\n", mesh->vertices_count);
}





