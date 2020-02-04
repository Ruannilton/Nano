#include "Mesh.h"
#include "../Core/NanoIO.h"

#define LINE_READED_BUFF_SIZE 128

#define SHADER_POS_LOC 0
#define SHADER_COLOR_LOC 1
#define SHADER_TEX_LOC 2
#define SHADER_NORM_LOC 3

GLuint mesh_genVAO(Mesh* mesh) {
	GLuint vbo;
	GLuint ebo;
	GLuint vao;
	uint count = 0;

	GLsizeiptr v_size = mesh->vertices_count * sizeof(Vec3);
	GLsizeiptr n_size = mesh->normal_count * sizeof(Vec3);
	GLsizeiptr t_size = mesh->uv_count * sizeof(Vec2);
	GLsizeiptr c_size = mesh->color_count * sizeof(Vec3);
	GLsizeiptr i_size = mesh->index_count * sizeof(uint);


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, v_size+n_size+t_size+c_size, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0						 , v_size, mesh->vertices);
	glBufferSubData(GL_ARRAY_BUFFER, v_size                  , n_size, mesh->normals);
	glBufferSubData(GL_ARRAY_BUFFER, v_size + n_size         , t_size, mesh->uvs);
	glBufferSubData(GL_ARRAY_BUFFER, v_size + n_size + t_size, c_size, mesh->colors);

	glVertexAttribPointer(SHADER_POS_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void*)0); //vert pos
	glEnableVertexAttribArray(SHADER_POS_LOC);

	glVertexAttribPointer(SHADER_NORM_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void*)v_size);//vert normal
	glEnableVertexAttribArray(SHADER_NORM_LOC);

	glVertexAttribPointer(SHADER_TEX_LOC, 2, GL_FLOAT, GL_TRUE, sizeof(Vec2), (void*)(v_size + n_size));//vert uv
	glEnableVertexAttribArray(SHADER_TEX_LOC);

	glVertexAttribPointer(SHADER_COLOR_LOC, 3, GL_FLOAT, GL_TRUE, sizeof(Vec3), (void*)(v_size + n_size + t_size));//vert color
	glEnableVertexAttribArray(SHADER_COLOR_LOC);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_size, mesh->index, GL_STATIC_DRAW);

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
	
	int size = mesh_loader_pre_alloc + 1;
	Vec3* vertList = ARRAY(Vec3,mesh_loader_pre_alloc+1);
	Vec3* normList = ARRAY(Vec3,mesh_loader_pre_alloc+1);
	Vec2* uvList   = ARRAY(Vec2,mesh_loader_pre_alloc+1);
	Vertex* faceList = ARRAY(Vertex,mesh_loader_pre_alloc+1);
	Mesh* mesh = NEW(Mesh);

	VERIFY(mesh, NULL);
	VERIFY(vertList, NULL);
	VERIFY(normList, NULL);
	VERIFY(uvList, NULL);
	VERIFY(faceList, NULL);

	
	mesh->color_count = 0;
	mesh->uv_count = 0;
	mesh->normal_count = 0;
	mesh->colors = 0;
	mesh->index_count = 0;
	int index_perline = 0;

	int quadFace = 0;
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

				int vert1, tex1, norm1, vert2, tex2, norm2, vert3, tex3, norm3,vert4,tex4,norm4;
				

				if (uv_count == 0 && norm_count == 0) {
					int matches = fscanf_s(file, "%d %d %d %d", &vert1, &vert2, &vert3,&vert4);
					tex1 = norm1 = -1;
					tex2 = norm2 = -1;
					tex3 = norm3 = -1;
					tex4 = norm4 = -1;
				}
				else if (uv_count == 0) {
					int matches = fscanf_s(file, " %d//%d %d//%d %d//%d %d//%d", &vert1, &norm1, &vert2, &norm2, &vert3, &norm3, &vert4, &norm4);
					tex1 = -1;
					tex2 = -1;
					tex3 = -1;
					tex4 = -1;
				}
				else if (norm_count == 0) {
					int matches = fscanf_s(file, "%d/%d %d/%d %d/%d %d/%d", &vert1, &tex1, &vert2, &tex2, &vert3, &tex3,&vert4,&tex4);
					norm1 = -1;
					norm2 = -1;
					norm3 = -1;
				}
				else {

					int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &vert1, &tex1, &norm1, &vert2, &tex2, &norm2, &vert3, &tex3, &norm3,&vert4,&tex4,&norm4);
					if (matches == 12) quadFace = 1;
					else quadFace = 0;
				}

				faceList[index_count].pos = vertList[vert1 - 1]; 
				faceList[index_count].uv = uvList[tex1 - 1];
				faceList[index_count].normal = normList[norm1 - 1];
				faceList[index_count].color = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
				index_count++;

				faceList[index_count].pos = vertList[vert2 - 1];
				faceList[index_count].uv = uvList[tex2 - 1];
				faceList[index_count].normal = normList[norm2 - 1];
				faceList[index_count].color = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
				index_count++;

				faceList[index_count].pos = vertList[vert3 - 1];
				faceList[index_count].uv = uvList[tex3 - 1];
				faceList[index_count].normal = normList[norm3 - 1];
				faceList[index_count].color = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
				index_count ++;

				if (quadFace) {
					faceList[index_count].pos = vertList[vert1 - 1];
					faceList[index_count].uv = uvList[tex1 - 1];
					faceList[index_count].normal = normList[norm1 - 1];
					faceList[index_count].color = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
					index_count++;
					
					faceList[index_count].pos = vertList[vert3 - 1];
					faceList[index_count].uv = uvList[tex3 - 1];
					faceList[index_count].normal = normList[norm3 - 1];
					faceList[index_count].color = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
					index_count++;

					faceList[index_count].pos = vertList[vert4 - 1];
					faceList[index_count].uv = uvList[tex4 - 1];
					faceList[index_count].normal = normList[norm4 - 1];
					faceList[index_count].color = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
					index_count++;
				}
			}
		}
	}
	
	mesh->vertices = ARRAY(Vec3, index_count);
	mesh->normals  = ARRAY(Vec3, index_count);
	mesh->uvs      = ARRAY(Vec2, index_count);
	mesh->index    = ARRAY(int , index_count);
	mesh->colors = ARRAY(Vec4, index_count);;

	mesh->vertices_count = index_count;
	mesh->normal_count = index_count;
	mesh->index_count = index_count;
	mesh->uv_count = index_count;
	mesh->color_count = index_count;
	

	DEBUG("Mesh sizes > \nvert: %d\nnormal: %d\nuv: %d\nindex: %d", mesh->vertices_count, mesh->normal_count, mesh->uv_count, mesh->index_count);

	
	
	for (uint i = 0; i < index_count;i++) {
		 mesh->vertices[i] = faceList[i].pos;
		 mesh->uvs[i]      = faceList[i].uv;
		 mesh->normals[i]  = faceList[i].normal;
		 mesh->colors[i] = faceList[i].color;
		 mesh->index[i] = i;
	}
	
	free(vertList);
	free(normList);
	free(uvList);
	free(faceList);

	fclose(file);
	mesh_genVAO(mesh);

	DEBUG_C(ANSI_LIGHT_GREEN, "Loaded Model: %s", path);
	return mesh;
}

Mesh* mesh_LoadPrimitive(uint primitive) {

	Mesh* mesh = NEW(Mesh);
	VERIFY(mesh, NULL);

	if (primitive == PRIMITIVE_PLANE) {

		mesh->index = ARRAY(uint, 6);
		VERIFY(mesh->index, NULL);
		mesh->index[0] = 3;
		mesh->index[1] = 1;
		mesh->index[2] = 0;
		mesh->index[3] = 3;
		mesh->index[4] = 2;
		mesh->index[5] = 1;
		mesh->index_count = 6;

		mesh->vertices = ARRAY(Vec3, 4);
		VERIFY(mesh->vertices, NULL);
		mesh->vertices[0] = (Vec3){ 0.5f,  0.5f, 0.0f };
		mesh->vertices[1] = (Vec3){ 0.5f, -0.5f, 0.0f };
		mesh->vertices[2] = (Vec3){ -0.5f, -0.5f, 0.0f };
		mesh->vertices[3] = (Vec3){ -0.5f,  0.5f, 0.0f };
		mesh->vertices_count = 4;

		mesh->colors = ARRAY(Vec4, 4);
		VERIFY(mesh->colors, NULL);
		mesh->colors[0] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[1] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[2] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[3] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->color_count = 4;

		mesh->uvs = ARRAY(Vec2, 4);
		VERIFY(mesh->uvs, NULL);
		mesh->uvs[0] = (Vec2){ 0.0f,0.0f };
		mesh->uvs[1] = (Vec2){ 1.0f,0.0f };
		mesh->uvs[2] = (Vec2){ 1.0f,1.0f };
		mesh->uvs[3] = (Vec2){ 0.0f,1.0f };
		mesh->uv_count = 4;

		mesh->normals = ARRAY(Vec3, 4);
		VERIFY(mesh->normals, NULL);
		mesh->normals[0] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[1] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[2] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[3] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normal_count = 4;

	}
	else if (primitive == PRIMITIVE_CUBE) {
		
		mesh->vertices = ARRAY(Vec3, 24);
		mesh->colors = ARRAY(Vec4, 24);
		mesh->normals = ARRAY(Vec3, 24);
		mesh->uvs = ARRAY(Vec2, 24);
		mesh->index = ARRAY(uint, 36);

		VERIFY(mesh->vertices, NULL);
		VERIFY(mesh->colors, NULL);
		VERIFY(mesh->uvs, NULL);
		VERIFY(mesh->index, NULL);
		VERIFY(mesh->normals, NULL);

		mesh->vertices_count = 24;
		mesh->color_count = 24;
		mesh->normal_count = 24;
		mesh->uv_count = 24;
		mesh->index_count = 36;
		
		int vert_c = 0, index_c = 0;

		//front
		mesh->vertices[0+ vert_c] = (Vec3){ -0.5f, -0.5f, 0.5f };
		mesh->vertices[1+ vert_c] = (Vec3){ 0.5f, -0.5f, 0.5f };
		mesh->vertices[2+ vert_c] = (Vec3){ 0.5f, 0.5f, 0.5f };
		mesh->vertices[3+ vert_c] = (Vec3){ -0.5f, 0.5f, 0.5f };
		
		mesh->colors[0 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f ,1.0f};
		mesh->colors[1 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f ,1.0f};
		mesh->colors[2 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f ,1.0f};
		mesh->colors[3 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f ,1.0f};

		mesh->normals[0 + vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[1 + vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[2 + vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[3 + vert_c] = (Vec3){ 0.0f,0.0f,1.0f };

		mesh->uvs[0 + vert_c] = (Vec2){ 1.0f,1.0f };
		mesh->uvs[1 + vert_c] = (Vec2){ 0.0f,1.0f };
		mesh->uvs[2 + vert_c] = (Vec2){ 0.0f,0.0f };
		mesh->uvs[3 + vert_c] = (Vec2){ 1.0f,0.0f };
		
		mesh->index[0+index_c] = 0 + vert_c;
		mesh->index[1+index_c] = 1 + vert_c;
		mesh->index[2+index_c] = 3 + vert_c;
		mesh->index[3+index_c] = 1 + vert_c;
		mesh->index[4+index_c] = 2 + vert_c;
		mesh->index[5+index_c] = 3 + vert_c;

		vert_c += 4;
		index_c += 6;

		//back
		mesh->vertices[0 + vert_c] = (Vec3){ 0.5f, 0.5f, -0.5f };
		mesh->vertices[1 + vert_c] = (Vec3){ 0.5f, -0.5f, -0.5f };
		mesh->vertices[2 + vert_c] = (Vec3){ -0.5f, -0.5f, -0.5f };
		mesh->vertices[3 + vert_c] = (Vec3){ -0.5f, 0.5f, -0.5f };

		mesh->colors[0 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[1 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[2 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[3 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };

		mesh->normals[0+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[1+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[2+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[3+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };

		mesh->uvs[0+ vert_c] = (Vec2){ 1.0f,1.0f };
		mesh->uvs[1+ vert_c] = (Vec2){ 0.0f,1.0f };
		mesh->uvs[2+ vert_c] = (Vec2){ 0.0f,0.0f };
		mesh->uvs[3+ vert_c] = (Vec2){ 1.0f,0.0f };

		mesh->index[0 + index_c] = 0 + vert_c;
		mesh->index[1 + index_c] = 1 + vert_c;
		mesh->index[2 + index_c] = 3 + vert_c;
		mesh->index[3 + index_c] = 1 + vert_c;
		mesh->index[4 + index_c] = 2 + vert_c;
		mesh->index[5 + index_c] = 3 + vert_c;

		vert_c += 4;
		index_c += 6;

		//right
		mesh->vertices[0+ vert_c] = (Vec3){ 0.5f, -0.5f, 0.5f };
		mesh->vertices[1+ vert_c] = (Vec3){ 0.5f, -0.5f, -0.5f };
		mesh->vertices[2+ vert_c] = (Vec3){ 0.5f, 0.5f, -0.5f };
		mesh->vertices[3+ vert_c] = (Vec3){ 0.5f, 0.5f, 0.5f };

		mesh->colors[0 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[1 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[2 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[3 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };

		mesh->normals[0+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[1+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[2+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[3+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };

		mesh->uvs[0+ vert_c] = (Vec2){ 1.0f,1.0f };
		mesh->uvs[1+ vert_c] = (Vec2){ 0.0f,1.0f };
		mesh->uvs[2+ vert_c] = (Vec2){ 0.0f,0.0f };
		mesh->uvs[3+ vert_c] = (Vec2){ 1.0f,0.0f };

		mesh->index[0 + index_c] = 0 + vert_c;
		mesh->index[1 + index_c] = 1 + vert_c;
		mesh->index[2 + index_c] = 3 + vert_c;
		mesh->index[3 + index_c] = 1 + vert_c;
		mesh->index[4 + index_c] = 2 + vert_c;
		mesh->index[5 + index_c] = 3 + vert_c;

		vert_c += 4;
		index_c += 6;
		//left
		mesh->vertices[0+ vert_c] = (Vec3){ -0.5f, -0.5f, 0.5f };
		mesh->vertices[1+ vert_c] = (Vec3){ -0.5f, 0.5f, 0.5f  };
		mesh->vertices[2+ vert_c] = (Vec3){ -0.5f, 0.5f, -0.5f };
		mesh->vertices[3+ vert_c] = (Vec3){ -0.5f, -0.5f, -0.5f};

		mesh->colors[0 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[1 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[2 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[3 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };

		mesh->normals[0+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[1+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[2+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[3+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };

		mesh->uvs[0+ vert_c] = (Vec2){ 1.0f,1.0f };
		mesh->uvs[1+ vert_c] = (Vec2){ 0.0f,1.0f };
		mesh->uvs[2+ vert_c] = (Vec2){ 0.0f,0.0f };
		mesh->uvs[3+ vert_c] = (Vec2){ 1.0f,0.0f };

		mesh->index[0 + index_c] = 0 + vert_c;
		mesh->index[1 + index_c] = 1 + vert_c;
		mesh->index[2 + index_c] = 3 + vert_c;
		mesh->index[3 + index_c] = 1 + vert_c;
		mesh->index[4 + index_c] = 2 + vert_c;
		mesh->index[5 + index_c] = 3 + vert_c;

		vert_c += 4;
		index_c += 6;
		//top
		mesh->vertices[0+ vert_c] = (Vec3){ -0.5f, 0.5f, 0.5f };
		mesh->vertices[1+ vert_c] = (Vec3){ 0.5f, 0.5f, 0.5f };
		mesh->vertices[2+ vert_c] = (Vec3){ 0.5f, 0.5f, -0.5f };
		mesh->vertices[3+ vert_c] = (Vec3){ -0.5f, 0.5f, -0.5f };

		mesh->colors[0 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[1 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[2 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[3 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };

		mesh->normals[0+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[1+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[2+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[3+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };

		mesh->uvs[0+ vert_c] = (Vec2){ 1.0f,1.0f };
		mesh->uvs[1+ vert_c] = (Vec2){ 0.0f,1.0f };
		mesh->uvs[2+ vert_c] = (Vec2){ 0.0f,0.0f };
		mesh->uvs[3+ vert_c] = (Vec2){ 1.0f,0.0f };

		mesh->index[0 + index_c] = 0 + vert_c;
		mesh->index[1 + index_c] = 1 + vert_c;
		mesh->index[2 + index_c] = 3 + vert_c;
		mesh->index[3 + index_c] = 1 + vert_c;
		mesh->index[4 + index_c] = 2 + vert_c;
		mesh->index[5 + index_c] = 3 + vert_c;
		
		vert_c += 4;
		index_c += 6;

		//bot
		mesh->vertices[0+ vert_c] = (Vec3){ -0.5f, -0.5f, 0.5f };
		mesh->vertices[1+ vert_c] = (Vec3){ 0.5f, -0.5f, 0.5f };
		mesh->vertices[2+ vert_c] = (Vec3){ 0.5f, -0.5f, -0.5f };
		mesh->vertices[3+ vert_c] = (Vec3){ -0.5f, -0.5f, -0.5f };

		mesh->colors[0 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[1 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[2 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };
		mesh->colors[3 + vert_c] = (Vec4){ 1.0f,1.0f,1.0f,1.0f };

		mesh->normals[0+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[1+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[2+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };
		mesh->normals[3+ vert_c] = (Vec3){ 0.0f,0.0f,1.0f };

		mesh->uvs[0+ vert_c] = (Vec2){ 1.0f,1.0f };
		mesh->uvs[1+ vert_c] = (Vec2){ 0.0f,1.0f };
		mesh->uvs[2+ vert_c] = (Vec2){ 0.0f,0.0f };
		mesh->uvs[3+ vert_c] = (Vec2){ 1.0f,0.0f };

		mesh->index[0 + index_c] = 3 + vert_c;
		mesh->index[1 + index_c] = 1 + vert_c;
		mesh->index[2 + index_c] = 0 + vert_c;
		mesh->index[3 + index_c] = 3 + vert_c;
		mesh->index[4 + index_c] = 2 + vert_c;
		mesh->index[5 + index_c] = 1 + vert_c;
		
	}
	mesh_genVAO(mesh);

	return mesh;
}

void mesh_PrintMesh(Mesh* mesh) {
	printf("Index Count: %d\n", mesh->index_count);
	printf("Vertex Count: %d\n", mesh->vertices_count);
}





