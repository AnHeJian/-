
// HistogramDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Histogram.h"
#include "HistogramDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CHistogramDlg 对话框



CHistogramDlg::CHistogramDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_HISTOGRAM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHistogramDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SRC, &CHistogramDlg::OnBnClickedButtonSrc)
	ON_BN_CLICKED(IDC_BUTTON_SRCHIST, &CHistogramDlg::OnBnClickedButtonSrchist)
	ON_BN_CLICKED(IDC_BUTTON_DST, &CHistogramDlg::OnBnClickedButtonDst)
END_MESSAGE_MAP()


// CHistogramDlg 消息处理程序

BOOL CHistogramDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CRect temprect(0, 0, 1200, 600);
	CWnd::SetWindowPos(NULL, 0, 0, temprect.Width(), temprect.Height(), SWP_NOZORDER | SWP_NOMOVE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHistogramDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHistogramDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHistogramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHistogramDlg::OnBnClickedButtonSrc()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnInitDialog();
	
	CImage  srcimage;
	CRect rect;

	// TODO: 在此添加控件通知处理程序代码
	CFileDialog open_img(
		true, NULL, NULL, OFN_OVERWRITEPROMPT,
		//_T("bmp文件(*.bmp)|*.bmp||"),
		_T("bmp文件(*.bmp)|*.bmp|图片文件(*.png; *.jpg; *.jpeg)|*.png; *.jpg; *.jpeg||"),
		NULL);

	if (open_img.DoModal() == IDOK)
		srcimg_path = open_img.GetPathName();


	if (!srcimg_path.IsEmpty())
	{
		//根据路径载入图片  
		srcimage.Load(srcimg_path);
		
		//获取图片的宽 高度  
		width = srcimage.GetWidth();
		height = srcimage.GetHeight();

		//获取Picture Control控件的大小  
		GetDlgItem(IDC_PICTURE_SRC)->GetWindowRect(&rect);
		//将客户区选中到控件表示的矩形区域内  
		ScreenToClient(&rect);
		//窗口移动到控件表示的区域  
		GetDlgItem(IDC_PICTURE_SRC)->MoveWindow(rect.left, rect.top, width, height, TRUE);
		CWnd *pWnd = NULL;
		pWnd = GetDlgItem(IDC_PICTURE_SRC);//获取控件句柄  
		pWnd->GetClientRect(&rect);//获取句柄指向控件区域的大小  

		CDC *pDc = NULL;
		pDc = pWnd->GetDC();//获取picture的DC  

		srcimage.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  

		ReleaseDC(pDc);

		readBmp();
		GetDlgItem(IDC_BUTTON_SRCHIST)->EnableWindow(true); 
		GetDlgItem(IDC_BUTTON_DST)->EnableWindow(true);
	}
}

bool CHistogramDlg::readBmp()
{
	FILE *fp;
	char * BmpName;

	int len = WideCharToMultiByte(CP_ACP, 0, srcimg_path, -1, NULL, 0, NULL, NULL);
	BmpName = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, srcimg_path, -1, BmpName, len, NULL, NULL);

	
	fopen_s(&fp, BmpName, "rb");
	if (fp == NULL)
		return false;
	

	BITMAPFILEHEADER bf;                        //图像文件头  
	BITMAPINFOHEADER bi;                        //图像文件信息头 
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, fp);//读取BMP文件头文件  
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp);//读取BMP文件头文件信息 

	width = bi.biWidth;						//读取图像的宽
	height = bi.biHeight;						//读取图像的高
	bCount = bi.biBitCount;						//读取图像的每个像素的位数

	/*对8位的BMP图读取调色板，调色板一共256个颜色，
	每个颜色占4个字节（RGBQUAD），分别是Blue值，Green值，Red值，透明度*/
	if (bCount == 8)
	{
		bColorTable = new RGBQUAD[256];
		fread(bColorTable, sizeof(RGBQUAD), 256, fp);
	}
	else if (bCount == 24)
		bColorTable = NULL;
	else
		return false;

	/*lineBytes表示每一行的字节数，BMP图像每行的字节数都要是4的倍数，
	公式中的 (bWidth * bCount / 8 + 3) / 4是将每的字节数目根据根据整型除法的原则进行规约
	例如：宽为510的8位BMP图像规约后，每行的字节数目就是512。*/
	lineBytes = ((width * bCount / 8 + 3) / 4) * 4;


	bPixelBuf = new unsigned char[lineBytes * height];//分配图像像素数据缓冲区大小
	fread(bPixelBuf, 1, lineBytes*height, fp);        //开始读取像素数据  

	return true;
}

void CHistogramDlg::OnBnClickedButtonSrchist()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CHistogramDlg::OnBnClickedButtonDst()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取Picture Control控件的大小  
	CRect rect;
	CImage  dstimage;

	dstimage.Load(srcimg_path);

	GetDlgItem(IDC_PICTURE_DST)->GetWindowRect(&rect);
	//将客户区选中到控件表示的矩形区域内  
	ScreenToClient(&rect);
	//窗口移动到控件表示的区域  
	GetDlgItem(IDC_PICTURE_DST)->MoveWindow(rect.left, rect.top, width, height, TRUE);
	CWnd *pWnd = NULL;
	pWnd = GetDlgItem(IDC_PICTURE_DST);//获取控件句柄  
	pWnd->GetClientRect(&rect);//获取句柄指向控件区域的大小  

	CDC *pDc = NULL;
	pDc = pWnd->GetDC();//获取picture的DC  

	dstimage.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  

	ReleaseDC(pDc);
}
