#define NANO_RENDER_TREE

#ifndef NANO_RENDER_TREE
#define NANO_RENDER_TREE

#include <malloc.h>
#include "..//..//Utils.h"
#include "../../GL.h"
#include "..//..//Components/RenderComponent.h"
/*
Shader -> Mesh -> Texture -> Transform
*/

typedef struct _no
{
	_no* next;
	_no* prev;
	_no* child;
	unsigned int id;
	void* value;
}TreeNode;


typedef struct RenderTree {
	TreeNode* Shaders;
};

RenderTree* RenderTree_Create() {
	RenderTree* rt;
	rt = (RenderTree*)malloc(sizeof(RenderTree));
	rt->Shaders = 0;
	return rt;
}

TreeNode* RenderTree_AddNode(TreeNode* node,unsigned int value) {
	
	if (node == NULL) {
		node = (TreeNode*)malloc(sizeof(TreeNode));
		node->child = 0;
		node->next = 0;
		node->prev = 0;
		node->value = malloc(sizeof(unsigned int));
		node->id = value;
		*((unsigned int*)node->value) = value;
		return node;
	}
	
	TreeNode* current = node;
	TreeNode* prev = current;

	while (current != 0) {
		if (node->id == value) {
			DEBUG("Node existente\n");
			return current;
		} 
		prev = current;
		current = current->next;
	}
	current = (TreeNode*)malloc(sizeof(TreeNode));
	current->child = 0;
	current->next = 0;
	current->prev = prev;
	node->id = value;
	node->value = malloc(sizeof(unsigned int));
	memcpy(node->value, (void*)value);
	*(unsigned int*)current->value = value;
	return current;
}

TreeNode* RenderTree_AddTranformNode(TreeNode* node,unsigned int vaoID, mat4* value) {
	if (node == NULL) {
		node = (TreeNode*)malloc(sizeof(TreeNode));
		node->child = 0;
		node->next = 0;
		node->prev = 0;
		node->id = vaoID;
		node->value = value;
		return node;
	}

	TreeNode* current = node;
	TreeNode* prev = current;

	while (current != 0) {
		if (current->id == vaoID){
			DEBUG("Node existente\n");
			return current;
		}
		prev = current;
		current = current->next;
	}
	current = (TreeNode*)malloc(sizeof(TreeNode));
	current->child = 0;
	current->next = 0;
	current->prev = prev;
	current->value = value;
	current->id = vaoID;
	return current;
}

void RenderTree_AddRenderComp(RenderTree* rt,RenderComponent* rc) {
	if (rt->Shaders == NULL) DEBUG("Null\n");
	TreeNode* shader = RenderTree_AddNode(rt->Shaders, rc->Shader); DEBUG("Added shader\n");
	TreeNode* mesh = RenderTree_AddNode(shader->child, rc->Vao); DEBUG("Added mesh\n");
	TreeNode* tex = RenderTree_AddNode(mesh->child, rc->Texture); DEBUG("Added tex\n");
	RenderTree_AddTranformNode(tex->child,rc->Vao, &rc->Model); DEBUG("Added model\n");
}

#endif // !NANO_RENDER_TREE
