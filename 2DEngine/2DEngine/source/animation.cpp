#include "animation.h"

void animate::dump_to_stdout(const char* a_fileName)
{

	int status = doc.LoadFile(a_fileName);

	if (status != tinyxml2::XML_NO_ERROR)
	{
		printf("fuck");
		doc.PrintError();
		return;
	}
	else
	{
		printf("it worked...");
	}
}
void animate::LoadAnimationUV(const char* a_fileName,AnimationType currentState)
{
	dump_to_stdout(a_fileName);
	docAtlas = doc.FirstChildElement();
	firstElement = docAtlas->FirstChildElement();
	frame TempF;
	for (siblingElement = firstElement; siblingElement != nullptr; siblingElement = siblingElement->NextSiblingElement())
	{
		int x, y, width, height;
		width = siblingElement->IntAttribute("width");
		height = siblingElement->IntAttribute("height");
		
		//vertex one
		x = siblingElement->IntAttribute("x");
		y = siblingElement->IntAttribute("y") - height;
		TempF.vertexOne_UV = glm::vec2(x, y);

		//vertex two
		x = siblingElement->IntAttribute("x");
		TempF.vertexTwo_UV = glm::vec2(x, y);

		//vertex three
		x = siblingElement->IntAttribute("x") + width;
		y = siblingElement->IntAttribute("y");
		TempF.vertexThree_UV = glm::vec2(x, y);

		//vertex four
		x = siblingElement->IntAttribute("x") + width;
		y = siblingElement->IntAttribute("y") - height;
		TempF.vertexFour_UV = glm::vec2(x, y);

		//sprite data
		//m = TempF.mSprite;
		FramesInAnimation.emplace_back(TempF);
		TempF.frameNumber++;
	}
	MapOfFrames.emplace(std::pair<AnimationType, std::vector<frame>>(currentState, FramesInAnimation));
}

void animate::PlayAnimation(AnimationType desiredState)
{
	
	AnimatedSpriteMap[desiredState].UpdateUV(MapOfFrames[desiredState][0].vertexOne_UV,
											MapOfFrames[desiredState][0].vertexTwo_UV,
											MapOfFrames[desiredState][0].vertexThree_UV,
											MapOfFrames[desiredState][0].vertexFour_UV);
	AnimatedSpriteMap[desiredState].Draw();
}