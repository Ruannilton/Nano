#include "Mesh.h"
#include "../Core/NanoIO.h"

#define LINE_READED_BUFF_SIZE 128

GLuint mesh_genVAO(Mesh* mesh) {
	GLuint vbo;
	GLuint ebo;
	GLuint vao;
	uint count = 0;

	GLsizeiptr v_size = mesh->vertices_count * sizeof(Vec3);
	GLsizeiptr n_size = mesh->normal_count * sizeof(Vec3);
	GLsizeiptr t_size = mesh->uv_count * sizeof(Vec2);
	GLsizeiptr c_size = mesh->color_count * sizeof(Vec3);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glBufferData(GL_ARRAY_BUFFER, v_size +n_size+t_size+c_size, 0, GL_STATIC_DRAW);
	
	glBufferSubData(GL_ARRAY_BUFFER, 0						 , v_size, mesh->vertices);
	glBufferSubData(GL_ARRAY_BUFFER, v_size                  , n_size, mesh->normals);
	glBufferSubData(GL_ARRAY_BUFFER, v_size + n_size         , t_size, mesh->uvs);
	glBufferSubData(GL_ARRAY_BUFFER, v_size + n_size + t_size, c_size, mesh->colors);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void*) 0); //vert pos
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void*) v_size);//vert normal
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vec2), (void*) (v_size + n_size));//vert uv
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void*) (v_size + n_size + t_size));//vert uv

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

	Vec3* vertList = ARRAY(Vec3,mesh_loader_pre_alloc+1);
	Vec3* normList = ARRAY(Vec3,mesh_loader_pre_alloc+1);
	Vec2* uvList   = ARRAY(Vec2,mesh_loader_pre_alloc+1);
	Face* faceList = ARRAY(Face,mesh_loader_pre_alloc+1);

	Mesh* mesh = NEW(Mesh);
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
				fscanf_s(file, "%f %f %f", &(vertList[vert_count].x), &(vertList[vert_count].y), &(vertList[vert_count].z));
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

	//REPEAT_1(vert_count) {
	//	DEBUG("v[%d] %f %f %f",i, vertList[i].x, vertList[i].y, vertList[i].z);
	//	
	//}
	//DEBUG("\n");
	//REPEAT_1 (index_count) {
	//	DEBUG("f[%d] %d/%d/%d   %d/%d/%d   %d/%d/%d",i, faceList[i].face1.x, faceList[i].face1.y, faceList[i].face1.z, faceList[i].face2.x, faceList[i].face2.y, faceList[i].face2.z, faceList[i].face3.x, faceList[i].face3.y, faceList[i].face3.z);
	//}

	mesh->vertices = ARRAY(Vec3, vert_count * 3);
	mesh->normals  = ARRAY(Vec3, norm_count * 3);
	mesh->uvs      = ARRAY(Vec3, uv_count * 3);
	mesh->index    = ARRAY(int , index_count * 9);
	mesh->colors = 0;

	mesh->vertices_count = index_count * 3;
	mesh->normal_count = index_count * 3;
	mesh->uv_count = index_count * 3;
	mesh->color_count = 0;
	mesh->index_count =index_count * 9;

	DEBUG("Mesh sizes > \nvert: %d\nnormal: %d\nuv: %d\nindex: %d", mesh->vertices_count, mesh->normal_count, mesh->uv_count, mesh->index_count);

	Face face;
	uint index_c = 0;
	uint data_c = 0;
	

	REPEAT_1(index_count) {
		 index_c = i;
		 face = faceList[i];

		 DEBUG("face[%d] %d/%d/%d   %d/%d/%d   %d/%d/%d", i, faceList[i].face1.x, faceList[i].face1.y, faceList[i].face1.z, faceList[i].face2.x, faceList[i].face2.y, faceList[i].face2.z, faceList[i].face3.x, faceList[i].face3.y, faceList[i].face3.z);

		 mesh->vertices[data_c] = vertList[face.face1.x];
		 mesh->uvs[data_c]      = uvList  [face.face1.y];
		 mesh->normals[data_c]  = normList[face.face1.z];
		 mesh->index[index_c] = index_c;

		 index_c++;
		// face = faceList[index_c];
		 mesh->vertices[data_c] = vertList[face.face2.x];
		 mesh->uvs[data_c]      = uvList[face.face2.y];
		 mesh->normals[data_c]  = normList[face.face2.z];
		 mesh->index[index_c] = index_c;

		 index_c++;
		// face = faceList[index_c];
		 mesh->vertices[data_c] = vertList[face.face3.x];
		 mesh->uvs[data_c]      = uvList[face.face3.y];
		 mesh->normals[data_c]  = normList[face.face3.z];
		 mesh->index[index_c] = index_c;
		
		 data_c += 3;
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





