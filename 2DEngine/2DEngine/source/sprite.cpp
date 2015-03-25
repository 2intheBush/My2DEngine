#include "sprite.h"

unsigned int Sprite::loadTexture(const char* o_fileName, int & a_iWidth, int & a_iHeight, int & a_iBPP)
{
	unsigned int uiTextureID = 0;
	//check file exists
	if (o_fileName != nullptr)
	{
		//read in image data from file
		unsigned char* pImageData = SOIL_load_image(o_fileName, &a_iWidth, &a_iHeight, &a_iBPP, SOIL_LOAD_RGBA);

		//check for successful read
		if (pImageData)
		{
			//create opengl texture handle
			uiTextureID = SOIL_create_OGL_texture(pImageData, a_iWidth, a_iHeight, a_iBPP,
				SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
			//clear what was read in from file now that it is stored in the handle
			SOIL_free_image_data(pImageData);
		}

		//check for errors
		if (uiTextureID == 0)
		{
			std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
		}
		return uiTextureID;
	}
}

Sprite::Sprite(const char* a_fileName, int width, int height)
{
	//class shader program
	glUseProgram(uiProgramTextured);

	int imageWidth, imageHeight;
	bpp = 4;
	spriteID = loadTexture(a_fileName, imageWidth, imageHeight, bpp);
	//uniform values for vertices
	sWidth = width;
	sHeight = height;

	vertex[0].position = glm::vec2(-.5, -.5);
	vertex[1].position = glm::vec2(-.5, .5);
	vertex[2].position = glm::vec2(.5, .5);
	vertex[3].position = glm::vec2(.5, -.5);
	vertex[0].color = vertex[1].color = vertex[2].color = vertex[3].color = glm::vec4(1, 1, 1, 1);
	vertex[0].UV = glm::vec2(0, 0);
	vertex[1].UV = glm::vec2(0, 1);
	vertex[2].UV = glm::vec2(1, 1);
	vertex[3].UV = glm::vec2(1, 0);

	//create VBO and IBO for object
	glGenBuffers(1, &uiVBO);
	glGenBuffers(1, &uiIBO);
	glGenVertexArrays(1, &uiVAO);
	glBindVertexArray(uiVAO);

	GLint positionAttrib = glGetAttribLocation(uiProgramTextured, "postion");
	glEnableVertexAttribArray(positionAttrib);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	GLint colorAttrib = glGetAttribLocation(uiProgramTextured, "colour");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 4));

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 8));


	ortho = getOrtho(0, 1024, 0, 720, 0, 100);
	uiProgramTextured = CreateProgram("VertexShader.glsl", "TexturedFragmentShader.glsl");
	MatrixIDTextured = glGetUniformLocation(uiProgramTextured, "MVP");

	viewMatrix = glm::lookAt(glm::vec3(0,0,1), glm::vec3(0,0,0), glm::vec3(0,1,0));
	transform = glm::mat4(1);
	translate = glm::vec3(0,0,0);
	scale = glm::vec3(width, height, 1);

	UpdateMatrix();

	//unbind buffers 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite::UpdateMatrix()
{
	glBindVertexArray(uiVAO);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);

	glm::mat4 translateMatrix(1.f);
	translateMatrix = glm::translate(glm::mat4(), translate);
	glm::mat4 scaleMatrix(1.f);
	scaleMatrix = glm::scale(scaleMatrix, scale);
	glm::mat4 rotateMatrix(1.f);
	rotateMatrix = glm::rotate(rotateMatrix, 0.0f, glm::vec3(0, 0, 1));
	transform = translateMatrix * rotateMatrix * scaleMatrix;

	MVPMatrix = ortho * viewMatrix * transform;

	glUniformMatrix4fv(MatrixIDTextured, 1, GL_FALSE, glm::value_ptr(MVPMatrix));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite::Translation(glm::vec2 x_y)
{
	translate = glm::vec3(x_y, 0);
	UpdateMatrix();
}

glm::mat4 Sprite::getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar)
{
	//to correspond with mat4 in the shader
	return glm::ortho(left, right, bottom, top, a_fNear, a_fFar);
}

GLuint Sprite::CreateShader(GLenum a_eShaderType, const char *a_strShaderFile)
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

GLuint Sprite::CreateProgram(const char *a_vertex, const char *a_frag)
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

void Sprite::UpdateUV(glm::vec2 vOne, glm::vec2 vTwo, glm::vec2 vThree, glm::vec2 vFour)
{
	vertex[0].UV = vOne;
	vertex[1].UV = vTwo;
	vertex[2].UV = vThree;
	vertex[3].UV = vFour;
}

void Sprite::Draw()
{
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_ALPHA);
	glFrontFace(GL_CW);

	//bind VBO
	glBindTexture(GL_TEXTURE_2D, spriteID);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBindVertexArray(uiVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);

	//ortho project onto shader
	//ortho needs to be MVP matrix 
	glUniformMatrix4fv(MatrixIDTextured, 1, GL_FALSE, glm::value_ptr(MVPMatrix));


	//now we have UVs, we need to send that info to the graphics card
	/*
	this is where you tell the GPU how to extract each piece of data from the blob of data you are sending it,
	each Vertex struct has data and you have to tell it how it's structured as a whole, not each piece.
	the last param is where each piece of data starts in memory per vertex chunk.
	for each vertex chunk the vertices start at beginning (0) and are size of 4 floats, then there is color info
	this starts after the vertices, so it's 0 + the 4 floats and itself is size of 4 floats, then it's the
	UV coords which will start after (0 + 4 + 4) = 8.
	*/
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(std::vector<glm::vec2>), (void*)(sizeof(float)* 8));


	//draw to the screen
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, NULL);

	//unbind buffers 
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}