#pragma once;

#include <string>
#include <unordered_map>

struct ShaderSources
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
  public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

  private:
	unsigned int CreateShader(const std::string& filepath);
	unsigned int CompileSubShader(unsigned int type, const std::string& shader);
	ShaderSources ParseShader(const std::string& filepath);

	int GetUniformLocation(const std::string& name);

  private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	std::unordered_map<std::string, int> m_UniformLocationCache;
};
