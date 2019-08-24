extern "C" {
#include "NanoEngine.h"
#include "..//Materials/TexturedMaterial.h"
}


 void Start() {

	TexturedMaterial* t_mat = NEW(TexturedMaterial);
	t_mat->texture = texture_LoadTextureDefault("Assets/models/Rat.png");

	Material* mat = NEW(Material);
	mat->data = t_mat;
	mat->fnc = Material_GetBindFnc(TexturedMaterial);
	mat->shader_id = DefaultShader;

	Mesh* m = mesh_LoadMesh("Assets/models/cube.obj");
	RenderComponent* rc = RenderComponent_Create(m, mat);


}
 
 void Update() {
	

 }