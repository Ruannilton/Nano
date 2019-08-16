#ifndef NANO_RENDER_LIST
#define NANO_RENDER_LIST

#include "..//..//Utils.h"
#include "..//..//GL.h"
#include "..//..//Components/RenderComponent.h"

struct _Components{
	RenderComponent* comp;
	_Components* prox;
};

typedef struct _Components Components;

 struct _RenderNode
{
	Components* lastCmp;
	Components* renders;
	GLuint ShaderID;
	struct _RenderNode* prox;
};

typedef struct _RenderNode RenderNode;

typedef RenderNode RenderList;

void RenderList_Add(RenderList** list,RenderComponent* comp) {
	RenderNode** node = list;
	if (*node != NULL) {
		while (*node != NULL || (*node)->ShaderID != comp->Shader)
		{
			//DEBUG("SHADER NODE %d",comp->Shader);
			node = &(*node)->prox;
		}
	}

	if (*node == NULL) {
		//DEBUG("NEW NODE");
		(*node) = NEW(RenderNode);
		(*node)->prox = NULL;
		(*node)->ShaderID = comp->Shader;
		
		(*node)->renders = NEW(Components);
		(*node)->renders->comp = comp;
		(*node)->renders->prox = NULL;
		(*node)->lastCmp = (*node)->renders;
		return;
	}
	//DEBUG("ADD TO SHADER NODE");
	Components* last = (*node)->lastCmp;
	Components* New = NEW(Components);
	New->comp = comp;
	New->prox = NULL;
	last->prox = New;
	(*node)->lastCmp = New;

}
#endif 