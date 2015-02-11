#include "framework.h"



int GLF::InitWindow(int screenWidth, int screenHeight, const char* title)
{
	if (!glfwInit())
	{
		return -1;
	}

	window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	//make the window's context current
	glfwMakeContextCurrent(window);

	//Start GLEW
	if (glewInit() != GLEW_OK)
	{
		//OpenGL didn't Start up... Shutdown GLFW and return an error code
		glfwTerminate();
		return -1;
	};
	ortho = getOrtho(0, screenWidth, 0, screenHeight, 0, 100);
	uiProgramTextured = CreateProgram("VertexShader.glsl", "TexturedFragmentShader.glsl");
	MatrixIDTextured = glGetUniformLocation(uiProgramTextured, "MVP");

	//class shader program
	glUseProgram(uiProgramTextured);
	//ortho project onto shader
	glUniformMatrix4fv(MatrixIDTextured, 1, GL_FALSE, ortho);

	//alpha blend
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	return 0;
}
const float* GLF::getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar)
{
	//to correspond with mat4 in the shader
	float * toReturn = new float[12];
	toReturn[0] = 2.0 / (right - left);
	toReturn[1] = toReturn[2] = toReturn[3] = toReturn[4] = 0;
	toReturn[5] = 2.0 / (top - bottom);
	toReturn[6] = toReturn[7] = toReturn[8] = toReturn[9] = 0;
	toReturn[10] = 2.0 / (a_fFar - a_fNear);
	toReturn[11] = 0;
	toReturn[12] = -1 * ((right + left) / (right - left));
	toReturn[13] = -1 * ((top + bottom) / (top - bottom));
	toReturn[14] = -1 * ((a_fFar + a_fNear) / (a_fFar - a_fNear));
	toReturn[15] = 1;
	return toReturn;
}
GLuint GLF::CreateShader(GLenum a_eShaderType, const char *a_strShaderFile)
{
	std::string strShaderCode;
	//open shader file
	std::ifstream shaderStream(a_strShaderFile);
	//if that worked ok, load file line by line
	if (shaderStream.is_open())
	{
		std::string Line = "";
		while (std::getline(shaderStream, Line))
		{
			strShaderCode += "\n" + Line;
		}
		shaderStream.close();
	}

	//convert to cstring
	char const *szShaderSourcePointer = strShaderCode.c_str();

	//create shader ID
	GLuint uiShader = glCreateShader(a_eShaderType);
	//load source code
	glShaderSource(uiShader, 1, &szShaderSourcePointer, NULL);

	//compile shader
	glCompileShader(uiShader);

	//check for compilation errors and output them
	GLint iStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iStatus);
	if (iStatus == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(uiShader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (a_eShaderType)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return uiShader;
}
GLuint GLF::CreateProgram(const char *a_vertex, const char *a_frag)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, a_vertex));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, a_frag));

	//create shader program ID
	GLuint uiProgram = glCreateProgram();

	//attach shaders
	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
		glAttachShader(uiProgram, *shader);

	//link program
	glLinkProgram(uiProgram);

	//check for link errors and output them
	GLint status;
	glGetProgramiv(uiProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(uiProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(uiProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glDetachShader(uiProgram, *shader);
		glDeleteShader(*shader);
	}

	return uiProgram;
}
void GLF::Shutdown()
{
	glfwTerminate();
}
bool GLF::UpdateFramework()
{
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	return !(glfwWindowShouldClose(window));
}
void GLF::SetScreenColor(float a_red, float a_green, float a_blue, float a_alpha)
{
	glClearColor(a_red, a_green, a_blue, a_alpha);
	glClear(GL_COLOR_BUFFER_BIT);
	command.HandleInput(window);
	hDirection = command.horzAxis;
	vDirection = command.vertAxis;
}
void GLF::SwapBuffers()
{
	glfwSwapBuffers(window);
	lastFrame = currentFrame;
	//poll for and process events
	glfwPollEvents();
}

unsigned int GLF::CreateSprite(const char* a_fileName, int width, int height)
{
	Sprite s(a_fileName, width, height);
	mSpriteList.emplace_back(s);
	return mSpriteList.size() - 1;
}

void GLF::DrawSprite(unsigned int s)
{
	mSpriteList[s].Draw();
}

void GLF::MoveSprite(unsigned int s, float x, float y)
{
	mSpriteList[s].x = x;
	mSpriteList[s].y = y;
	UpdateVertex(s);
 }

void GLF::UpdateVertex(unsigned int s)
{
	mSpriteList[s].vertex[0].position = glm::vec4(mSpriteList[s].x - mSpriteList[s].sWidth, mSpriteList[s].y - mSpriteList[s].sHeight, 0, 1);
	mSpriteList[s].vertex[1].position = glm::vec4(mSpriteList[s].x - mSpriteList[s].sWidth, mSpriteList[s].y + mSpriteList[s].sHeight, 0, 1);
	mSpriteList[s].vertex[2].position = glm::vec4(mSpriteList[s].x + mSpriteList[s].sWidth, mSpriteList[s].y + mSpriteList[s].sHeight, 0, 1);
	mSpriteList[s].vertex[3].position = glm::vec4(mSpriteList[s].x + mSpriteList[s].sWidth, mSpriteList[s].y - mSpriteList[s].sHeight, 0, 1);
}
