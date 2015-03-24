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
	int imageWidth, imageHeight;
	bpp = 4;
	spriteID = loadTexture(a_fileName, imageWidth, imageHeight, bpp);
	//uniform values for vertices
	sWidth = width;
	sHeight = height;

	vertex[0].position = glm::vec4(x - sWidth, y - sHeight, 0, 1);
	vertex[1].position = glm::vec4(x - sWidth, y + sHeight, 0, 1);
	vertex[2].position = glm::vec4(x + sWidth, y + sHeight, 0, 1);
	vertex[3].position = glm::vec4(x + sWidth, y - sHeight, 0, 1);
	vertex[0].color = vertex[1].color = vertex[2].color = vertex[3].color = glm::vec4(1, 1, 1, 1);
	vertex[0].UV = glm::vec2(0, 0);
	vertex[1].UV = glm::vec2(0, 1);
	vertex[2].UV = glm::vec2(1, 1);
	vertex[3].UV = glm::vec2(1, 0);

	//create VBO and IBO for object
	glGenBuffers(1, &uiVBO);
	glGenBuffers(1, &uiIBO);
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

	//check if Index buffer succeeded
	if (uiIBO != 0)
	{
		//bind IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);
		//allocate space for index info on the graphics card
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(char), NULL, GL_STATIC_DRAW);
		//get pointer to newly allocated space on the graphics card
		GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		//specify the order we'd like to draw our vertices.
		//In this case they are in sequential order
		for (int i = 0; i < 4; i++)
		{
			((char*)iBuffer)[i] = i;
		}
		//unmap and unbind
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	//check if vertex buffer succeeded
	if (uiVBO != 0)
	{
		//bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);

		//allocate space on graphics card
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* 4, NULL, GL_STATIC_DRAW);

		//get pointer to allocate space on graphics card
		GLvoid* vSBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		//copy to graphics card
		memcpy(vSBuffer, vertex, sizeof(Vertex)* 4);

		//unmap and unbind
		glUnmapBuffer(GL_ARRAY_BUFFER);

	}

	//bind VBO
	glBindTexture(GL_TEXTURE_2D, spriteID);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);


	//enable vertex array state
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


	//specify where our vertex array is
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 4));
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
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 8));

	//draw to the screen
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, NULL);

	//unbind buffers 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}