#pragma once
class IDebugPort
{
public:
	
	virtual void Setup() = 0;
	virtual void Println(String& pMessage) = 0;

};

