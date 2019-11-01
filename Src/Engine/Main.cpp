extern "C" {
#include "NanoEngine.h"
#include "..//Materials/TexturedMaterial.h"
}


 void Start() {

	TexturedMaterial* t_mat = NEW(TexturedMaterial);
	t_mat->texture = texture_LoadTextureDefault("Assets/Images/Rat.png");

	Material* mat = Material_Create(DefaultShader, Material_GetBindFnc(TexturedMaterial), t_mat);
	
	Mesh* m = mesh_LoadMesh("Assets/models/cube.obj");
	RenderComponent* rc = RenderComponent_Create(m, mat);
	
	AddToRender(rc);

	
}
 
 void Update() {
	
	 
 }