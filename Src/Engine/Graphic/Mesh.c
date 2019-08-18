#include "Mesh.h"
#include "../Core/NanoIO.h"


GLuint mesh_genVAO(Mesh* mesh) {
	GLuint vbo;
	GLuint ebo;
	GLuint vao;
	unsigned int count = 0;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	uint v_size = mesh->vertices_count*sizeof(uint);
	uint n_size = mesh->normal_count*sizeof(uint);
	uint t_size = mesh->uv_count*sizeof(uint);
	uint c_size = mesh->color_count*sizeof(uint);

	glBufferSubData(GL_ARRAY_BUFFER, 0,v_size, mesh->vertices);
	glBufferSubData(GL_ARRAY_BUFFER, v_size, n_size, mesh->normals);
	glBufferSubData(GL_ARRAY_BUFFER, v_size + n_size, t_size, mesh->uvs);
	glBufferSubData(GL_ARRAY_BUFFER, v_size + n_size + t_size, c_size, mesh->colors);

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
	char desc[3];

	unsigned int vert_count = 0;
	unsigned int index_count = 0;
	unsigned int norm_count = 0;
	unsigned int uv_count = 0;
	unsigned int i;

	vec3* vertList = (vec3*)malloc(sizeof(vec3*) * (mesh_loader_pre_alloc + 1));
	vec3* normList = (vec3*)malloc(sizeof(vec3*) * (mesh_loader_pre_alloc + 1));
	vec2* uvList = (vec2*)malloc(sizeof(vec2*) * (mesh_loader_pre_alloc + 1));
	vec3* faceList = (vec3*)malloc(sizeof(vec3*) * (9 * (mesh_loader_pre_alloc + 1)));

	Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
	int index_perline = 0;

#pragma region READ FILE
	while (!feof(file))
	{
		if (fscanf_s(file, "%s", &desc)) {

			if (strcmp(desc, "v") == 0) {
				vert_count += 3;
				fscanf_s(file, "%f %f %f", &vertList[vert_count][0], &vertList[vert_count][1], &vertList[vert_count][2]);
			}
			else if (strcmp(desc, "vn") == 0) {
				norm_count += 3;
				fscanf_s(file, "%f %f %f", &normList[norm_count][0], &normList[norm_count][1], &normList[norm_count][2]);
			}
			else if (strcmp(desc, "vt") == 0) {
				uv_count += 2;
				fscanf_s(file, "%f %f", &uvList[uv_count][0], &uvList[uv_count][1]);
			}
			else if (strcmp(desc, "f") == 0) {

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

				faceList[index_count][0] = vert1;
				faceList[index_count + 1][0] = vert2;
				faceList[index_count + 2][0] = vert3;
				faceList[index_count][1] = tex1;
				faceList[index_count + 1][1] = tex2;
				faceList[index_count + 2][1] = tex3;
				faceList[index_count][2] = norm1;
				faceList[index_count + 1][2] = norm2;
				faceList[index_count + 2][2] = norm3;
				index_count += 3;
			}
		}
	}
#pragma endregion

	mesh->normal_count = norm_count;
	mesh->vertices_count = vert_count;
	mesh->uv_count = uv_count;
	mesh->index_count = index_count;

	mesh->vertices = (float*)malloc(sizeof(float) *3*index_count);
	mesh->normals  = (float*)malloc(sizeof(float) *3*index_count);
	mesh->index    = (uint*) malloc(sizeof(uint)  *1*index_count);
	mesh->uvs 	   = (float*)malloc(sizeof(float) *2*index_count);
	

	unsigned int verti = 0;
	unsigned int vertu = 0;
	int iv, in, it;
	float v1, v2, v3, t1, t2, n1, n2, n3;

	for (i = 0; i < index_count; i++) {

		mesh->index[i] = i;

		iv = (int)faceList[i][0];
		it = (int)faceList[i][1];
		in = (int)faceList[i][2];

		v1 = vertList[iv][0];
		v2 = vertList[iv][1];
		v3 = vertList[iv][2];
		t1 = uvList[it][0];
		t2 = uvList[it][1];
		n1 = normList[in][0];
		n2 = normList[in][1];
		n3 = normList[in][2];

		if (uv_count && norm_count) {
			mesh->vertices[verti] = v1;
			mesh->vertices[verti + 1] = v2;
			mesh->vertices[verti + 2] = v3;

			mesh->normals[verti ] = n1;
			mesh->normals[verti + 1] = n2;
			mesh->normals[verti + 2] = n3;

			mesh->uvs[vertu] = t1;
			mesh->uvs[vertu+1] = t2;

			verti += 3;
			vertu += 2;
		}
		else if (uv_count) {
			mesh->vertices[verti] = v1;
			mesh->vertices[verti + 1] = v2;
			mesh->vertices[verti + 2] = v3;

			mesh->uvs[vertu] = t1;
			mesh->uvs[vertu+1] = t2;

			verti += 3;
			vertu += 2;

		}
		else if (norm_count) {
			mesh->vertices[verti] = v1;
			mesh->vertices[verti + 1] = v2;
			mesh->vertices[verti + 2] = v3;

			mesh->normals[verti ] = n1;
			mesh->normals[verti + 1] = n2;
			mesh->normals[verti + 2] = n3;
			
			verti += 3;
		}

	}

	free(vertList);
	free(normList);
	free(uvList);
	free(faceList);

	fclose(file);
	mesh_genVAO(mesh);
	printf("Loaded %s\n", path);
	return mesh;
}

void mesh_PrintMesh(Mesh* mesh) {
	printf("Index Count: %d\n", mesh->index_count);
	printf("Vertex Count: %d\n", mesh->vertices_count);
}





