#pragma once
class iMap
{
public:
	iMap();
	virtual ~iMap();

	virtual bool GetHeight(IN float x, OUT float& y, IN float z) = 0;
};

