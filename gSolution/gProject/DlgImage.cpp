// DlgImage.cpp : implementation file
//

#include "stdafx.h"
#include "gProject.h"
#include "DlgImage.h"
#include "afxdialogex.h"


// CDlgImage dialog

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLGIMAGE, pParent)
{
	m_pParent = pParent; 
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
//	ON_BN_CLICKED(IDC_BTN_UP_PARENT, &CDlgImage::OnBnClickedBtnUpParent)
ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImage message handlers
#include "gProjectDlg.h"

//void CDlgImage::OnBnClickedBtnUpParent()
//{
//	// TODO: Add your control notification handler code here
//	static int n = 100; 
//	// call to parent dialog 
//	CgProjectDlg *pDlg = (CgProjectDlg*)m_pParent; 
//	pDlg->callFunc(n++);
//}


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	MoveWindow(0, 0, 640, 480);
	// create image in dialog screen 
	InitImage();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgImage::InitImage()
{
	int nWidth = 640;//
	int nHeight = 480;//  
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb);
	}
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	//memset(fm, 0xff, nWidth*nHeight);
	memset(fm, 0xff, sizeof(unsigned char)*nWidth*nHeight);
}

void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	if (m_image) {
		m_image.Draw(dc, 0, 0);
	}
	// use OnPaint draw result 
	drawData(&dc); // add header 
}

void CDlgImage::drawData(CDC* pDC) {
	//CRect rect(0, 0, 15, 100); 
	//pDC->Ellipse(rect);

	//unsigned char* fm = (unsigned char*)m_image.GetBits();

	//memset(fm, 0xff, nWidth*nHeight);
	//memset(fm, 0xff, sizeof(unsigned char)*m_image.GetWidth()*m_image.GetHeight());

	/*
	CRect rect;
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, COLOR_RED);	// make new pen: RGB: R=255 
	CPen* pOldPen = pDC->SelectObject(&pen);	// make a pointer point to old pen 
	for (int i = 0; i < m_nDataCount; i++) {
		rect.SetRect(m_ptData[i], m_ptData[i]);
		rect.InflateRect(2, 2);

		pDC->Ellipse(rect);
	}
	pDC->SelectObject(pOldPen);	// put back old pen from pointer 
	*/

	int radius = 20; 
	CRect rect;
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, COLOR_YELLOW);	// make new pen: RGB: R=255 
	CPen* pOldPen = pDC->SelectObject(&pen);	// make a pointer point to old pen 

	rect.SetRect(0, 0, radius, radius);
	rect.InflateRect(2, 2);
	pDC->Ellipse(rect);

	pDC->SelectObject(pOldPen);
}