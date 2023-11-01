
// gProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gProject.h"
#include "gProjectDlg.h"
#include "afxdialogex.h"
#include "Process.h"

#include<iostream>
using namespace std; 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CgProjectDlg dialog



CgProjectDlg::CgProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GPROJECT_DIALOG, pParent)
	, m_nRadius(40)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RADIUS, m_nRadius);
}

BEGIN_MESSAGE_MAP(CgProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BTN_DLG, &CgProjectDlg::OnBnClickedBtnDlg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_MAKE_CIRCLE, &CgProjectDlg::OnBnClickedBtnMakeCircle)
	ON_EN_CHANGE(IDC_EDIT_RADIUS, &CgProjectDlg::OnEnChangeEditRadius)
	ON_EN_UPDATE(IDC_EDIT_RADIUS, &CgProjectDlg::OnEnUpdateEditRadius)
END_MESSAGE_MAP()


// CgProjectDlg message handlers

BOOL CgProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	MoveWindow(0, 0, 1280, 800); // Main dialog set at 0, 0, size 1280x800 

	m_pDlgImage = new CDlgImage(this); // init --> need to add delete later. 
	m_pDlgImage->Create(IDD_DLGIMAGE, this); // id, windows 
	m_pDlgImage->ShowWindow(SW_SHOW); // show the dialog 
	
	// move dlgImage dialog to left place 
	m_pDlgImage->MoveWindow(0, 0, 640, 480);

	InitBackgroundNoise();
	//calculate the CenterMass by default: 
	CProcess process; 
	
	m_pDlgImage->m_nRadius = m_nRadius; 
	int ret = process.getCenterMass(&m_pDlgImage->m_image, m_pDlgImage->m_nMassCenterX, 
		m_pDlgImage->m_nMassCenterY, m_pDlgImage->m_nRadius,
		m_pDlgImage->m_nMassCenterX, m_pDlgImage->m_nMassCenterY);

	cout << "Init  center of mass " << m_pDlgImage->m_nMassCenterX << "," << m_pDlgImage->m_nMassCenterY <<endl;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CgProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CgProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CgProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CgProjectDlg::OnBnClickedBtnDlg()
//{
//	// TODO: Add your control notification handler code here
//	// gitTest 
//	m_pDlgImage->ShowWindow(SW_SHOW); // show windows whenever click on button. 
//}


void CgProjectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	if (m_pDlgImage)
		delete m_pDlgImage;
}

void CgProjectDlg::callFunc(int n) {
	int nData = n; 
	std::cout << n << std::endl; 
}

void CgProjectDlg::OnBnClickedBtnMakeCircle()
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits(); // need unsigned char to access image data 
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();;
	int nPitch = m_pDlgImage->m_image.GetPitch();;

	m_pDlgImage->m_nRadius = m_nRadius;
	CProcess process;
	int ret = process.getCenterMass(&m_pDlgImage->m_image, m_pDlgImage->m_nCenterX,
		m_pDlgImage->m_nCenterY, m_pDlgImage->m_nRadius,
		m_pDlgImage->m_nMassCenterX, m_pDlgImage->m_nMassCenterY);

	cout << "Update center of mass " << m_pDlgImage->m_nMassCenterX << "," << m_pDlgImage->m_nMassCenterY << endl;


	//memset(fm, 0xff, sizeof(unsigned char) * nWidth * nHeight);
	UpdateData(TRUE); // update variable value 
	
	
	m_pDlgImage->Invalidate();
	
}

void CgProjectDlg::InitBackgroundNoise() {
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits(); // need unsigned char to access image data 
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();;
	int nPitch = m_pDlgImage->m_image.GetPitch();;

	memset(fm, 0, sizeof(unsigned char) * nWidth * nHeight);
	//memset(fm, 0xff, nWidth * nHeight);
	for (int k = 0; k < MAX_POINT; k++) {
		int x = rand() % nWidth;
		int y = rand() % nHeight;
		int val = rand() % 0xff;
			if (val >=100)
				fm[y*nPitch + x] = val;
	}
}



void CgProjectDlg::OnEnChangeEditRadius()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	/*
	CString radiusStr;
	m_editRadius.GetWindowText(radiusStr);

	// Convert the text to an integer
	int newRadius = _tstoi(radiusStr);

	// Ensure the new radius is within the valid range (10 to 200)
	if (newRadius < 10)
		newRadius = 10;
	else if (newRadius > 200)
		newRadius = 200;

	// Update the member variable and the Edit control
	m_nRadius = newRadius;
	CString newRadiusStr;
	newRadiusStr.Format(_T("%d"), m_nRadius);
	m_editRadius.SetWindowText(newRadiusStr);

	// Redraw the circle
	Invalidate();
	*/


	//UpdateData(TRUE);
	/*
	if (m_nRadius < 10)
		m_nRadius = 10;
	else if (m_nRadius > 200)
		m_nRadius = 200;

	m_pDlgImage->m_nRadius = m_nRadius;
	
	UpdateData(FALSE); 
	*/
	//Invalidate();
}


void CgProjectDlg::OnEnUpdateEditRadius()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	
	if (m_nRadius < 10)
	m_nRadius = 10;
	else if (m_nRadius > 200)
	m_nRadius = 200;

	m_pDlgImage->m_nRadius = m_nRadius;

	//UpdateData(FALSE);
}
