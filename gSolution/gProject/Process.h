#pragma once
#include "afx.h"
#include<iostream>


class CProcess :
	public CObject
{
public:
	CProcess();
	virtual ~CProcess();

	int getCenterMass(CImage *pImage, int centerX, int centerY, int radius, int &cenMassX, int &cenMassY); // variable is a pointer 
};

