//#ifndef NANO_SHADER_DATA
//#define NANO_SHDAER_DATA
//
//#include "../GL.h"
//#include "../Utils.h"
//#include <string.h>
//
//#define shd_fnc(T) typedef void (*CompShader_##T)(T*)
//#define compile(T) int Compile_##T(T* sd, CompShader_##T fnc) {(fnc)(sd);	return 0;}
//#define CompileSD(T) Compile_##T
//
//
//typedef struct ShaderData
//{
//	GLuint model;
//	GLuint view;
//	GLuint projection;
//};
//
//shd_fnc(ShaderData);
//compile(ShaderData)
//
//ShaderData* d;
//
//void CmpS(ShaderData* s) {
//	
//}
//
//int v = CompileSD(ShaderData)(d, CmpS);
//
//#endif