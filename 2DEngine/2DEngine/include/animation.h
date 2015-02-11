#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include <map>

class Sprite;

struct frame
{
	int frameNumber;
	glm::vec2 vone_UV;
	glm::vec2 vtwo_UV;
	glm::vec2 vthree_UV;
	glm::vec2 vfour_UV;
};

class animate
{
public:
	Sprite mSprite;
	std::map<int, frame>FrameData;

	void LoadAnimation(const char *);
};

#endif