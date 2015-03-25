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

	//alpha blend
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	frameProgram = CreateProgram("VertexShader.glsl", "TexturedFragmentShader.glsl");
	MatrixIDTextured = glGetUniformLocation(frameProgram, "MVP");

	return 0;
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
			strShaderCode += Line + "\n";
		}
		shaderStream.close();
		strShaderCode += '\0';
	}

	//convert to cstring
	const char *szShaderSourcePointer = strShaderCode.c_str();
	//strcpy(szShaderSourcePointer,strShaderCode.c_str())
	//char const *szShaderSourcePointer;
	//szShaderSourcePointer = strShaderCode.c_str();

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

unsigned int GLF::CreateSprite(const char* a_fileName, int width, int height, GLuint frameProgram)
{
	Sprite s(a_fileName, width, height, frameProgram);
	mSpriteList.emplace_back(s);
	MatrixIDTextured = s.MatrixIDText;
	return mSpriteList.size() - 1;
}

void GLF::DrawSprites(unsigned int s)
{
	mSpriteList[s].Draw();
}

void GLF::MoveSprite(unsigned int s, glm::vec2 x_y)
{
	//mSpriteList[s].x = x_y[0];
	//mSpriteList[s].y = x_y[1];
	mSpriteList[s].Translation(x_y);
	mSpriteList[s].UpdateMatrix();
 }

void GLF::CreateAnimation(const char * a_fileName, AnimationType currentState, float width, float height)
{

	Animation.LoadAnimationUV(a_fileName, currentState);
	//Sprite s(a_fileName, width, height);
	//Animation.AnimatedSpriteMap.emplace(std::pair<AnimationType, Sprite>(currentState, s));
}

void LoadAnimationSprite(const char * a_fileName, AnimationType currentState)
{
	
}

void GLF::DrawAnimatedSprite(AnimationType currentState)
{
	Animation.PlayAnimation(currentState);
}

void GLF::GetCursPos(double &xPos, double &yPos)
{
	glfwGetCursorPos(window, &xPos, &yPos);
}

