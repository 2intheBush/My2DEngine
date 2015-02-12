#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include <map>
#include "sprite.h"
#include "tinyxml2.h"

class Sprite;

enum AnimationType
{
	walking,
	idle,
};

struct frame
{
	unsigned int frameNumber;
	glm::vec2 vertexOne_UV;
	glm::vec2 vertexTwo_UV;
	glm::vec2 vertexThree_UV;
	glm::vec2 vertexFour_UV;
};

class animate
{
public:
	// have an overloaded constructor!!!

	std::vector<frame> FramesInAnimation;
	std::map<AnimationType, std::vector<frame>>MapOfFrames;
	std::map<AnimationType, Sprite> AnimatedSpriteMap;

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement * docAtlas, * firstElement, * siblingElement;
	Sprite aSprite;
	void LoadAnimationUV(const char *a_fileName, AnimationType currentState);
	void PlayAnimation(AnimationType desiredState);

	void dump_to_stdout(const char* a_fileName);
};

#endif