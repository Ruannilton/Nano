#ifndef NANO_RENDER_TREE
#define NANO_RENDER_TREE

#include "../GL.h"

inline int maior(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

#define HEIGHT_TREE(TYPE)inline int height_tree_##TYPE(TYPE* root){\
if((root == NULL) || (root->left == NULL && root->right == NULL)) return 0;\
return 1 + maior(height_tree_##TYPE(root->left), height_tree_##TYPE(root->left));\
}
#define height_tree(T) height_tree_##T

#define FIND_IN_TREE(TYPE)inline TYPE* find_in_tree_##TYPE(TYPE* root, unsigned int val) {if (root->value == val) return root;if (root->left != NULL)  return find_in_tree_##TYPE(root->left, val); if (root->right != NULL) return find_in_tree_##TYPE(root->right, val); return NULL;}
#define find_in_tree(T) find_in_tree_##T

#define COUNT_NO(TYPE)inline int count_no_##TYPE(TYPE* root) {if (root == NULL) return 0;else return 1 + count_no_##TYPE(root->left) + count_no_##TYPE(root->right);}
#define count_no(T) count_no_##T


#define ADD_IN_TREE(TYPE)inline int add_in_tree_##TYPE (TYPE* root,TYPE* node) {\
if (node->value < root->value) {\
	if (root->left == NULL) {\
		root->left = node;return 1;\
	}\
	else {\
		if(height_tree(TYPE)(root->left)-height_tree(TYPE)(root->right) == 1){\
		TYPE* aux = root;\
		root = aux->left;\
		root->right = aux;\
		root->left = node;\
			return 1;\
		}\
		return add_in_tree_##TYPE(root->left, node);\
	}\
}else {\
	if (root->right == NULL) {\
		root->right = node;return 1;\
	}else {\
		if(height_tree(TYPE)(root->right)-height_tree(TYPE)(root->left) == 1){\
		TYPE* aux = root;\
		root = aux->right;\
		root->left = aux;\
		root->right = node;\
		return 1;\
		}\
		return add_in_tree_##TYPE(root->right, node);\
	}\
}}
#define add_in_tree(T) add_in_tree_##T


#define CLEAR_TREE(TYPE,CHILD)inline void clear_tree_##TYPE (TYPE* root){\
	if (root == NULL) return;\
	if (root->child != NULL)  clear_tree_##CHILD(root->child);\
	if (root->left == NULL && root->right == NULL) {\
		free(root);\
		return;\
	}\
	clear_tree_##TYPE(root->left);\
	clear_tree_##TYPE(root->right);\
	free(root);\
	return;\
} 
#define clear_tree(T) clear_tree_##T

#define REMOVE_IN_TREE(TYPE,CHILDTYPE)inline int remove_in_tree_##TYPE(TYPE* root,unsigned int val){\
	if (root == NULL) return 0;\
	if (root->value == val) {\
		if (root->left == NULL && root->right == NULL) {\
			clear_tree(CHILDTYPE)(root->child);\
			root = NULL;\
			free(root);\
			return 1;\
		}\
		if (root->left != NULL && root->right == NULL) {\
			TYPE* aux = root;\
			root = root->left;\
			clear_tree(CHILDTYPE)(root->child);\
			free(aux);\
			return 1;\
		}\
		else if (root->left == NULL && root->right != NULL) {\
			TYPE* aux = root;\
			root = root->right;\
			clear_tree(CHILDTYPE)(root->child);\
			free(aux);\
			return 1;\
		}\
		else {\
			TYPE* aux = root;\
			root->left->right = root->right->left;\
			root->right->left = root->left->right;\
			root = root->right;\
			clear_tree(CHILDTYPE)(root->child);\
			free(aux);\
		}}\
}
#define remove_in_tree(T) remove_in_tree_##T


typedef struct ModelList {
	ModelList* left;
	ModelList* right;
	mat4* value;
	unsigned int id;
};

typedef struct TextureList {
	TextureList* left;
	TextureList* right;
	GLuint value = -1;
	ModelList* child;
};

typedef struct VaoList {
	VaoList* left;
	VaoList* right;
	GLuint value = -1;
	TextureList* child;
	unsigned int indexCount;
};

typedef struct ShaderList {
	ShaderList* left;
	ShaderList* right;
	GLuint value = -1;
	VaoList* child;
};

typedef struct {
	ShaderList* shaderList;
	int ShaderCount = 0;
	int VaoCount = 0;
	int TextureCount = 0;
	int ModelCount = 0;
}RenderTree;


RenderTree renderTree = { NULL,0,0,0,0 };

inline void clear_tree_ModelList(ModelList* root) {
	
	if (root == NULL) return;
	if (root->left == NULL && root->right == NULL) {
		free(root);
		return;
	}
	clear_tree_ModelList(root->left);
	clear_tree_ModelList(root->right);
	free(root);
	return;
} 
inline int remove_in_tree_ModelList(ModelList* root, mat4* val) {
	
	if (root == NULL) return 0;
	if (root->value == val) {
		if (root->left == NULL && root->right == NULL) {
			root = NULL;
			free(root);
			return 1;
		}\
		if (root->left != NULL && root->right == NULL) {
			ModelList* aux = root;
			root = root->left;
			free(aux);
			return 1;
		}
		else if (root->left == NULL && root->right != NULL) {
			ModelList* aux = root;
			root = root->right;
			free(aux);
			return 1;
		}
		else {
			ModelList* aux = root;
			root->left->right = root->right->left;
			root->right->left = root->left->right;
			root = root->right;
			free(aux);
		}}
}
inline inline ModelList* find_in_tree_ModelList(ModelList* root, mat4* val) {
	if (root->value == val) return root;
	if (root->left != NULL) return find_in_tree_ModelList(root->left, val);
	if (root->right != NULL) return find_in_tree_ModelList(root->right, val);
	return NULL;
}

HEIGHT_TREE(ModelList);
ADD_IN_TREE(ModelList);
COUNT_NO(ModelList);


FIND_IN_TREE(TextureList);
HEIGHT_TREE(TextureList);
ADD_IN_TREE(TextureList);
COUNT_NO(TextureList);
CLEAR_TREE(TextureList, ModelList);
REMOVE_IN_TREE(TextureList, ModelList);

FIND_IN_TREE(VaoList);
HEIGHT_TREE(VaoList);
ADD_IN_TREE(VaoList);
COUNT_NO(VaoList);
CLEAR_TREE(VaoList, TextureList);
REMOVE_IN_TREE(VaoList, TextureList);

FIND_IN_TREE(ShaderList);
HEIGHT_TREE(ShaderList);
ADD_IN_TREE(ShaderList);
COUNT_NO(ShaderList);
CLEAR_TREE(ShaderList, VaoList);
REMOVE_IN_TREE(ShaderList, VaoList);

void AddShader(ShaderList* shader) {
	if (renderTree.shaderList == NULL) {
		renderTree.shaderList = shader;
		renderTree.ShaderCount++;
		return;
	}
	if (find_in_tree(ShaderList)(renderTree.shaderList, shader->value)) return;
	add_in_tree(ShaderList)(renderTree.shaderList, shader);
	renderTree.ShaderCount++;
}
void AddVAO(ShaderList* shader, VaoList* vao) {
	AddShader(shader);
	if (shader->child == NULL) {
		shader->child = vao;
		renderTree.VaoCount++;
		return;
	}
	if (find_in_tree(VaoList)(shader->child, vao->value))return;
	add_in_tree(VaoList)(shader->child, vao);
	renderTree.VaoCount++;
}
#endif // !NANO_RENDER_TREE
