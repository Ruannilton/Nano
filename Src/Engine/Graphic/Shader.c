#include "Shader.h"

unsigned int Shader_CompileShader(string path,string src, GLenum type) {
	GLuint id = glCreateShader(type);
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	int res;
	glGetShaderiv(id, GL_COMPILE_STATUS, &res);

	if (!res) {
		int len = 256;
		char log[256];
		glGetShaderInfoLog(id, len, &len, log);
		DEBUG_C(ANSI_RED,"ERROR COMPILE %s SHADER:\nAt: %s\n%s", (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT", path, log);
		
		glDeleteShader(id);
		return 0;
	}

	return id;
}

string PreCompiler(string str) {
	
	char file_name[64];
	char* loc_finded = strstr(str, "#include");
	char* new_ptr;
	char* ret = 0;
	if (loc_finded == NULL) return str;
	
	while (loc_finded != NULL) {
		char* ini = loc_finded + 8;
		int readed = 0;
		int ini_read_name = 0;
		int i = 0;

		while (true)
		{
			char v = ini[i];
			i++;
			if (v == ' ') continue;
			if (v == '\"' && ini_read_name == 0) {
				ini_read_name = 1;
				continue;
			}

			if (v == '\"' && ini_read_name) break;
			file_name[readed] = v;
			readed++;

		}
		char* end = ini + i;
		file_name[readed] = '\0';
		char* path = malloc(128);
		if (path) {
			strcpy(path, "Assets/Shaders/");
			path = strcat(path, file_name);
		}
		string module = IO_ReadFile(path);
		size_t  src_size = strlen(str);
		size_t  module_size = strlen(module);

		char* aux = malloc(src_size);
		if (aux) aux = strcpy(aux, end);


		 new_ptr = malloc(src_size + module_size + 4);

		if (new_ptr) {
			strcpy(new_ptr, str);
			loc_finded = strstr(new_ptr, "#include");
			strcpy(loc_finded, module);
			strcat(new_ptr, aux);
		}

		loc_finded = strstr(new_ptr, "#include");
		ret = new_ptr;
		free(aux);
		free(path);
		free(str);
	}
	
	
	return ret;
}

Shader Shader_CreateShader(string vs, string fs) {

	
	unsigned int prog = glCreateProgram();
	unsigned int vsID = 0;
	unsigned int fsID = 0;

	string vs_text = IO_ReadFile(vs);
	string fs_Text = IO_ReadFile(fs);

	vs_text = PreCompiler(vs_text);
	fs_Text = PreCompiler(fs_Text);
	
	vsID = Shader_CompileShader(vs, vs_text, GL_VERTEX_SHADER);
	fsID = Shader_CompileShader(fs, fs_Text, GL_FRAGMENT_SHADER);

	glAttachShader(prog, vsID);
	
	glAttachShader(prog, fsID);
	
	
	glLinkProgram(prog);
	
	glValidateProgram(prog);
	
	glDeleteShader(vsID);
	glDeleteShader(fsID);
	
	GLenum err = glGetError();
	
	if (err != GL_NO_ERROR)
	{
		GLchar* str = glErrorStringREGAL(err);
		DEBUG_C(ANSI_RED, "%s", str);
	}
	else
		DEBUG_C(ANSI_LIGHT_GREEN, "SHADER(%d) LOADED", prog);
	return prog;

	free(vs_text);
	free(fs_Text);
}

