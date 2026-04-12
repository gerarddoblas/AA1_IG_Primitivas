#include "Primitive.h"

//Funcion que lee una string para devolver el shader a cargar en la GPU
std::string Primitive::Load_File(const std::string& filePath) 
{
	std::ifstream file(filePath);
	std::string fileContent;
	std::string line;

	//Control Errores
	if (!file.is_open())
	{
		std::cerr << "No se pudo abrir el archivo " << filePath << std::endl;
		std::exit(EXIT_FAILURE);
	}

	//Leemos contenido del shader y lo guardamos
	while (std::getline(file,line))
	{
		fileContent += line + "\n";
	}

	//Cerramos string de datos y return contenido

	file.close();
	return fileContent;
}

GLuint Primitive::LoadFragmentShader(const std::string& filePath)
{
	//Crear vertex shader a la GPU
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Leo el archivo con el shader y lo almaceno
	std::string sShaderCode = Load_File(filePath);
	const char* cShaderSource = sShaderCode.c_str();

	//Vinculo el vertex shader a la GPU
	glShaderSource(fragmentShader, 1, &cShaderSource, nullptr);

	//Compilar vertex shader
	glCompileShader(fragmentShader);

	//Verificacion de la compilacion del shader
	GLint success;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (success)
	{
		return fragmentShader;
	}
	else
	{
		//Obtener longitud del log
		GLint logLength;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);

		//Obtenemos el log
		std::vector<GLchar> errorLog(logLength);
		glGetShaderInfoLog(fragmentShader, logLength, nullptr, errorLog.data());

		//Mostramos el log
		std::cerr << "Se ha producido el siguiente error : " << errorLog.data() << std::endl;

		std::exit(EXIT_FAILURE);

	}

}

GLuint Primitive::LoadGeometryShader(const std::string& filePath) //Podriamos poner aqui un enum para recbir y saber si es geometry o vertex shader
{
	//Crear vertex shader a la GPU
	GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

	//Leo el archivo con el shader y lo almaceno
	std::string sShaderCode = Load_File(filePath);
	const char* cShaderSource = sShaderCode.c_str();

	//Vinculo el vertex shader a la GPU
	glShaderSource(geometryShader, 1, &cShaderSource, nullptr);

	//Compilar vertex shader
	glCompileShader(geometryShader);

	//Verificacion de la compilacion del shader
	GLint success;
	glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);

	if (success)
	{
		return geometryShader;
	}
	else
	{
		//Obtener longitud del log
		GLint logLength;
		glGetShaderiv(geometryShader, GL_INFO_LOG_LENGTH, &logLength);

		//Obtenemos el log
		std::vector<GLchar> errorLog(logLength);
		glGetShaderInfoLog(geometryShader, logLength, nullptr, errorLog.data());

		//Mostramos el log
		std::cerr << "Se ha producido el siguiente error : " << errorLog.data() << std::endl;

		std::exit(EXIT_FAILURE);

	}

}

GLuint Primitive::LoadVertexShader(const std::string& filePath)
{
	//Crear vertex shader a la GPU
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Leo el archivo con el shader y lo almaceno
	std::string sShaderCode = Load_File(filePath);
	const char* cShaderSource = sShaderCode.c_str();

	//Vinculo el vertex shader a la GPU
	glShaderSource(vertexShader, 1, &cShaderSource, nullptr);

	//Compilar vertex shader
	glCompileShader(vertexShader);

	//Verificacion de la compilacion del shader
	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (success)
	{
		return vertexShader;
	}
	else
	{
		//Obtener longitud del log
		GLint logLength;
		glGetShaderiv(vertexShader,GL_INFO_LOG_LENGTH,&logLength);

		//Obtenemos el log
		std::vector<GLchar> errorLog(logLength);
		glGetShaderInfoLog(vertexShader, logLength, nullptr, errorLog.data() );

		//Mostramos el log
		std::cerr << "Se ha producido el siguiente error : " << errorLog.data() << std::endl;

		std::exit(EXIT_FAILURE);

	}

}

//Usando el struct encapsula los shaders creare el programa en la GPU que los usara
GLuint Primitive::CreateProgram(const ShaderProgram& shaders)
{
	//Creamos programa
	GLuint program = glCreateProgram();

	//Verificar si existe un vertex Shader a cargar
	if (shaders.vertexShader != 0)
	{
		glAttachShader(program,shaders.vertexShader);
	}
	
	if (shaders.geometryShader != 0)
	{
		glAttachShader(program, shaders.geometryShader);
	}

	if (shaders.fragmentShader != 0)
	{
		glAttachShader(program, shaders.fragmentShader);
	}

	//Linkear el programa
	glLinkProgram(program);

	//Obtener estado del programa
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (success)
	{
		//Liberar recursos

		if (shaders.vertexShader != 0)
		{
			glDetachShader(program, shaders.vertexShader);
		}

		if (shaders.geometryShader != 0)
		{
			glDetachShader(program, shaders.geometryShader);
		}

		if (shaders.fragmentShader != 0)
		{
			glDetachShader(program, shaders.fragmentShader);
		}

		return program;
	}
	else
	{
		//Obtenemos la longitud del log
		GLint logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

		//almacenamos log
		std::vector <GLchar> errorLog(logLength);
		glGetProgramInfoLog(program, logLength, nullptr, errorLog.data());

		//Printeamos log
		std::cerr << "Error al linkar programa: " << errorLog.data() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}
