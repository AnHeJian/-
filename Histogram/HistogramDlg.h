
// HistogramDlg.h: 头文件
//

#pragma once


// CHistogramDlg 对话框
class CHistogramDlg : public CDialog
{
// 构造
public:
	CHistogramDlg(CWnd* pParent = NULL);	// 标准构造函数
	bool readBmp();

public:
	CString srcimg_path;      //图像路径
	int width;				 //图像的宽
	int height;				 //图像的高
	WORD bCount;			 //图像类型，每像素位数
	RGBQUAD *bColorTable;	 //图像调色板（24位bmp图像没有，8位的有,）
	unsigned char *bPixelBuf;//图像像素数据
	int lineBytes;			 //图像每行的字节数
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTOGRAM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSrc();
	afx_msg void OnBnClickedButtonSrchist();
	afx_msg void OnBnClickedButtonDst();
};
