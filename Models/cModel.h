#pragma once

#include <string>

class cModel
{
public:
	cModel(void);
	~cModel(void);

	virtual void Animate (float t) { };
	virtual void Draw () {};
	virtual void ChangeAnimation (std::string animation) { };

protected:
	int m_texture;
};
