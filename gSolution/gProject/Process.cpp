#include "stdafx.h"
#include "Process.h"

#include<iostream>

using namespace std;

CProcess::CProcess()
{
}


CProcess::~CProcess()
{
}


int CProcess::getCenterMass(CImage *pImage, int centerX, int centerY, int radius, int &cenMassX, int &cenMassY) 
{
	unsigned char* fm = (unsigned char*)pImage->GetBits();
	int nWidth = pImage->GetWidth();
	int nHeight = pImage->GetHeight();
	int nPitch = pImage->GetPitch();

	int nTh = 0; 

	//CRect rect(0, 0, nWidth, nHeight);//  left top right bottom. 

	CRect rect(centerX-radius, centerY - radius, centerX+radius, centerY+ radius);//  left top right bottom. 

	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	for (int j = rect.top; j <= rect.bottom; j++) {
		for (int i = rect.left; i <= rect.right; i++) {
			// inside circle 
			if ((j- centerY)*(j-centerY) + (i-centerX)*(i-centerX) < radius*radius)
			if (fm[j*nPitch + i] > nTh) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}
	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;

	cenMassX = round(dCenterX);
	cenMassY = round(dCenterY);

	//cout << dCenterX << "\t" << dCenterY << endl;
	return 0; 
}