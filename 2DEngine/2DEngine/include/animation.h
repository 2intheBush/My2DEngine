#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include <map>

class Sprite;

struct frame
{
	int frameNumber;
	glm::vec2 v_1UV;
	glm::vec2 v_2UV;
	glm::vec2 v_3UV;
	glm::vec2 v_4UV;


};

class animate
{
public:
	Sprite mSprite;
	std::map<int, frame>FrameData;

	void LoadFrameMap(const char * a_fileName);
};

#endif