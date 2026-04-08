#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

struct ShaderProgram
{
	GLuint vertexShader = 0;
	GLuint geometryShader = 0;
	GLuint fragmentShader = 0;
};

void Resize_Window(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight) {

	//Definir nuevo tamaño del viewport
	glViewport(0, 0, iFrameBufferWidth, iFrameBufferHeight);
}

//Funcion que lee una string para devolver el shader a cargar en la GPU
std::string Load_File(const std::string& filePath) 
{
	std::ifstream file(filePath);
	std::string fileContent;
	std::string line;

	//Control Errores
	if (!file.is_open())
	{
		std::cerr << "No se pudo abrir el archivo pta vida tt" << filePath << std::endl;
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

GLuint LoadFragmentShader(const std::string& filePath)
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

GLuint LoadGeometryShader(const std::string& filePath) //Podriamos poner aqui un enum para recbir y saber si es geometry o vertex shader
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

GLuint LoadVertexShader(const std::string& filePath)
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
GLuint CreateProgram(const ShaderProgram& shaders)
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

	if (shaders.geometryShader != 0)
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


		if (shaders.geometryShader != 0)
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

void main()
{
	srand(time(NULL));

	glm::vec2 direction = {0.0f,0.0f};
	std::cout << "Contenido del fichero: " << Load_File("MyFirstVertexShader.glsl") << std::endl;

	//Inicializamos GLFW para gestionar ventanas e inputs
	glfwInit();

	
	//Configuramos la ventana
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//Inicializamos la ventana
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Engine", NULL, NULL);

	//Asignamos función de callback para cuando el frame buffer es modificado
	glfwSetFramebufferSizeCallback(window, Resize_Window);

	//Definimos espacio de trabajo
	glfwMakeContextCurrent(window);

	//Permitimos a GLEW usar funcionalidades experimentales
	glewExperimental = GL_TRUE;

	//Activamos cull face
	glEnable(GL_CULL_FACE);

	//Indicamos lado del culling
	glCullFace(GL_BACK);

	//Inicializamos GLEW y controlamos errores
	if (glewInit() == GLEW_OK) {

		//Compilar shaders
		ShaderProgram myFirstProgram;
		myFirstProgram.vertexShader = LoadVertexShader("MyFirstVertexShader.glsl");
		myFirstProgram.geometryShader = LoadGeometryShader("MyFirstGeometryShader.glsl");
		myFirstProgram.geometryShader = LoadFragmentShader("MyFirstFragmentShader.glsl");

		//Compilar programa
		GLuint myFirstCompiledProgram;
		myFirstCompiledProgram = CreateProgram(myFirstProgram);


		//Obtener referencia a la variable
		GLint offfsetReference = glGetUniformLocation(myFirstCompiledProgram, "offset");

		//Definimos color para limpiar el buffer de color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		GLuint vaoPuntos, vboPuntos, vboAleatorios;

		//Definimos cantidad de vao a crear y donde almacenarlos 
		glGenVertexArrays(1, &vaoPuntos);


		//Indico que el VAO activo de la GPU es el que acabo de crear
		glBindVertexArray(vaoPuntos);

		//Definimos cantidad de vbo a crear y donde almacenarlos
		glGenBuffers(1, &vboPuntos);
		

		//Indico que el VBO activo es el que acabo de crear y que almacenará un array. Todos los VBO que genere se asignaran al último VAO que he hecho glBindVertexArray
		glBindBuffer(GL_ARRAY_BUFFER, vboPuntos);		
		

		//Posición X e Y del punto
		GLfloat punto[] = {
			0.0f,   0.5f,
			-0.433f, -0.25f, 
			 0.433f, -0.25f  
			/*
			-0.5f,  0.5f, 
			-0.5f, -0.5f, 
			 0.0f,  0.5f, 
			 0.0f, -0.5f, 
			 0.5f,  0.5f, 
			 0.5f, -0.5f  
			 */
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(punto), punto, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		

		glGenBuffers(1, &vboAleatorios);
		glBindBuffer(GL_ARRAY_BUFFER, vboAleatorios);
		GLfloat randomData[12];
		for (int i = 0; i < 12; i++)
		{
			randomData[i] = static_cast<GLfloat>(rand()) / RAND_MAX * 0.5f;
		}

		glGenBuffers(1, &vboAleatorios);
		glBindBuffer(GL_ARRAY_BUFFER, vboAleatorios);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//Ponemos los valores en el VBO creado
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(randomData), randomData, GL_STATIC_DRAW);

		//Indicamos donde almacenar y como esta distribuida la información
		
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

		//Indicamos que la tarjeta gráfica puede usar el atributo 0
		
		glEnableVertexAttribArray(1);

		//Desvinculamos VAO
		glBindVertexArray(0);

		//Desvinculamos VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//Generamos el game loop
		while (!glfwWindowShouldClose(window)) {

			//Pulleamos los eventos (botones, teclas, mouse...)
			glfwPollEvents();

			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				direction.x += -.005f;
			}

			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				direction.x += .005f;
			}

			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				direction.y += .005f;
			}

			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				direction.y += -.005f;
			}

			

			//Limpiamos los buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			glUseProgram(myFirstCompiledProgram);

			//Declaramos vector2
			
			glm::vec2 offset = glm::vec2(0.4f, 0.5f);
			offset = direction;
			//Modificar variable offset
			glUniform2fv(offfsetReference,1, &offset[0]);


			//Definimos que queremos usar el VAO con los puntos
			glBindVertexArray(vaoPuntos);

			//Definimos que queremos dibujar
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

			//Dejamos de usar el VAO indicado anteriormente
			glBindVertexArray(0);

			//Cambiamos buffers
			glFlush();
			glfwSwapBuffers(window);
		}

		//Desactivat y liberar programa
		glUseProgram(0);
		glDeleteProgram(myFirstCompiledProgram);

	}else {
		std::cout << "Ha petao." << std::endl;
		glfwTerminate();
	}
	//Finalizamos GLFW
	glfwTerminate();
}




