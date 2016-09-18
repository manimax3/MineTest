#pragma once


class IKeyListener
{
public:
	IKeyListener() = default;
	virtual ~IKeyListener() = default;

private:
	friend class Input;

	virtual void onKeyPressed(int key) = 0;
	virtual void onKeyReleased(int key) = 0;

};
