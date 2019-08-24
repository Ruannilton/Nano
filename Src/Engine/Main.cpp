extern "C" {
#include "NanoEngine.h"
}


 void Start() {

	
	Mesh* m = mesh_LoadMesh("Assets/models/cube.obj");
	RenderComponent* rc = RenderComponent_Create(m, NULL);
}
 
 void Update() {
	

 }