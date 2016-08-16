#pragma once

class Condition
{
public:
	Condition(Node *node);

	virtual bool checkStrict() = 0;
	virtual bool checkScore() = 0;

protected:


};
