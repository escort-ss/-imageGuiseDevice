// picodeDlg.cpp: 实现文件
//

#include<opencv2\highgui\highgui.hpp>
#include "pch.h"
#include "framework.h"
#include "picode.h"
#include "picodeDlg.h"
#include "afxdialogex.h"
#include <opencv2/highgui/highgui_c.h>
#include<opencv2\opencv.hpp>
#include"iostream"
#include <direct.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CpicodeDlg 对话框

CpicodeDlg::CpicodeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PICODE_DIALOG, pParent)
{
	statusini();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CpicodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CpicodeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON9, &CpicodeDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON4, &CpicodeDlg::OnBnClickedToCode)
	ON_BN_CLICKED(IDC_BUTTON6, &CpicodeDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON3, &CpicodeDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE4, &CpicodeDlg::OnEnChangeMfceditbrowse4)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE2, &CpicodeDlg::OnEnChangeMfceditbrowse2)
	ON_BN_CLICKED(IDC_BUTTON10, &CpicodeDlg::OnBnClickedButton10)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE3, &CpicodeDlg::OnEnChangeMfceditbrowse3)
	ON_BN_CLICKED(IDC_BUTTON12, &CpicodeDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CpicodeDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CpicodeDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CpicodeDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON11, &CpicodeDlg::OnBnClickedButton11)
	ON_EN_UPDATE(IDC_MFCEDITBROWSE2, &CpicodeDlg::OnEnUpdateMfceditbrowse2)
	ON_EN_UPDATE(IDC_MFCEDITBROWSE4, &CpicodeDlg::OnEnUpdateMfceditbrowse4)
	ON_EN_UPDATE(IDC_MFCEDITBROWSE3, &CpicodeDlg::OnEnUpdateMfceditbrowse3)
	ON_BN_CLICKED(IDC_BUTTON2, &CpicodeDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

// CpicodeDlg 消息处理程序

BOOL CpicodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CpicodeDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CpicodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CpicodeDlg::OnBnClickedButton9()//decode
{
;
	CString a;
	a = char(NULL);
	USES_CONVERSION;
	if (*toDecodePic.data == FALSE)
	{
		AfxMessageBox(_T("没有选择需要解密的图片"));
		backPic = block.clone();
		return;
	}
	decodedPic = decode(toDecodePic, ampTimes);
	if (*decodedPic.data == FALSE)
	{
		GetDlgItem(IDC_IMG1)->ShowWindow(FALSE);
		GetDlgItem(IDC_IMG1)->ShowWindow(TRUE);
		return;
	}
	GetDlgItem(IDC_IMG1)->ShowWindow(FALSE);
	GetDlgItem(IDC_IMG1)->ShowWindow(TRUE);
	showImgInFrame(decodedPic, 1);
	backPic = block.clone();
	GetDlgItemText(IDC_MFCEDITBROWSE3, filePathD = char(NULL));
	return;
	// TODO: 在此添加控件通知处理程序代码
	//defstatus();;//第一个是内容，第二个是标题内容
	// TODO: 在此添加控件通知处理程序代码
}

void CpicodeDlg::OnBnClickedToCode()//save coded pic
{
	uchar* a = (codedPic.data);
	if (!*a)
	{
		AfxMessageBox(_T("没有可保存的已加密图片"));
		return;
	}
	USES_CONVERSION;
	const char* path = _getcwd(NULL, 0);
	CString text1, text2, text3, text4, text5, text6;
	text1 = "缩放倍率：";
	text4 = "已保存图片于:";
	text5 = "倍.png";
	text6.Format(_T("%d"), ampTimes);
	text3 = _getcwd(NULL, 0);
	text2 = text1 + text6;
	cv::String c;
	c = W2A(text2);
	const char* d = c.data();
	cv::imwrite((d + std::string("倍.png")), codedPic, { 9 });
	text3 = text4 + path + "\\" + text2 + text5;
	codedPic = block.clone();
	backPic = block.clone();
	AfxMessageBox(text3);
	GetDlgItem(IDC_IMG2)->ShowWindow(FALSE);
	GetDlgItem(IDC_IMG2)->ShowWindow(TRUE);
	GetDlgItem(IDC_IMG3)->ShowWindow(FALSE);
	GetDlgItem(IDC_IMG3)->ShowWindow(TRUE);
	// TODO: 在此添加控件通知处理程序代码
}

void CpicodeDlg::OnBnClickedButton6()
{
	filePathB = char(1);
	AfxMessageBox(_T("已选择使用默认底片"));
	// TODO: 在此添加控件通知处理程序代码
}

void CpicodeDlg::OnBnClickedButton3()//code
{
	CString a;
	a = char(NULL);
	USES_CONVERSION;
	if (*uncodePic.data == FALSE)
	{
		AfxMessageBox(_T("没有选择需要加密的图片"));
		return;
	}
	if (filePathB == a)
	{
		AfxMessageBox(_T("没有选择底片文件！,将使用默认底片"));
		backPic = randomColorBackPic(uncodePic);
		backPic = resizePic(backPic, uncodePic, ampTimes);
		codedPic = code(backPic, uncodePic, ampTimes);
		GetDlgItem(IDC_IMG3)->ShowWindow(FALSE);
		GetDlgItem(IDC_IMG3)->ShowWindow(TRUE);
		showImgInFrame(codedPic, 3);
		backPic = block.clone();
		GetDlgItemText(IDC_MFCEDITBROWSE2, filePathC = char(NULL));
		return;
	}
	if (filePathB == char(1))
	{
		backPic = randomColorBackPic(uncodePic);

		backPic = resizePic(backPic, uncodePic, ampTimes);

		codedPic = code(backPic, uncodePic, ampTimes);
		GetDlgItem(IDC_IMG3)->ShowWindow(FALSE);
		GetDlgItem(IDC_IMG3)->ShowWindow(TRUE);
		showImgInFrame(codedPic, 3);
		backPic = block.clone();
		return;
	}
	backPic = resizePic(backPic, uncodePic, ampTimes);
	codedPic = code(backPic, uncodePic, ampTimes);
	GetDlgItem(IDC_IMG3)->ShowWindow(FALSE);
	GetDlgItem(IDC_IMG3)->ShowWindow(TRUE);
	showImgInFrame(codedPic, 3);
	backPic = block.clone();
	return;

	// TODO: 在此添加控件通知处理程序代码
}

void CpicodeDlg::OnEnChangeMfceditbrowse4()//open the backpic
{
	USES_CONVERSION;
	GetDlgItemText(IDC_MFCEDITBROWSE4, filePathB);
	backPic = cv::imread(W2A(filePathB));
	CImage cimg2;
	GetDlgItem(IDC_IMG2)->ShowWindow(FALSE);
	GetDlgItem(IDC_IMG2)->ShowWindow(TRUE);
	showImgInFrame(backPic, 2);
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CpicodeDlg::OnEnChangeMfceditbrowse2()//open the toDecodePic
{
	USES_CONVERSION;
	GetDlgItemText(IDC_MFCEDITBROWSE2, filePathC);
	uncodePic = cv::imread(W2A(filePathC));
	//GetDlgItem(IDC_IMG1)->ShowWindow(FALSE);
	//GetDlgItem(IDC_IMG1)->ShowWindow(TRUE);
	showImgInFrame(uncodePic, 1);

	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CpicodeDlg::OnBnClickedButton10()//save decodedPic
{
	uchar* a = (decodedPic.data);
	if (!*a)
	{
		AfxMessageBox(_T("没有可保存的已解密图片"));
		return;
	}
	USES_CONVERSION;
	const char* path = _getcwd(NULL, 0);
	CString  text3, text4, text5;
	text4 = "已保存图片于:";
	text5 = "Decoded.png";
	text3 = _getcwd(NULL, 0);
	cv::String c;
	c = W2A(text5);
	const char* d = c.data();
	cv::imwrite(d, decodedPic, {9});
	text3 = text4 + path + "\\" + text5;
	decodedPic = block.clone();
	backPic = block.clone();
	AfxMessageBox(text3);
	GetDlgItem(IDC_IMG1)->ShowWindow(FALSE);
	GetDlgItem(IDC_IMG1)->ShowWindow(TRUE);
	GetDlgItem(IDC_IMG2)->ShowWindow(FALSE);
	GetDlgItem(IDC_IMG2)->ShowWindow(TRUE);
	// TODO: 在此添加控件通知处理程序代码
}

void CpicodeDlg::OnEnChangeMfceditbrowse3()//open codedPic to decode
{
	USES_CONVERSION;
	GetDlgItemText(IDC_MFCEDITBROWSE3, filePathD);
	toDecodePic = cv::imread(W2A(filePathD));
	GetDlgItem(IDC_IMG3)->ShowWindow(FALSE);
	GetDlgItem(IDC_IMG3)->ShowWindow(TRUE);
	showImgInFrame(toDecodePic, 3);
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CpicodeDlg::OnBnClickedButton12()
{
	ampTimes = 4;
	AfxMessageBox(_T("当前缩放倍率4"));
	// TODO: 在此添加控件通知处理程序代码
}

void CpicodeDlg::OnBnClickedButton13()
{
	ampTimes = 6;
	AfxMessageBox(_T("当前缩放倍率6"));
	// TODO: 在此添加控件通知处理程序代码
}

void CpicodeDlg::OnBnClickedButton14()
{
	ampTimes = 8;
	AfxMessageBox(_T("当前缩放倍率8"));
	// TODO: 在此添加控件通知处理程序代码
}

void CpicodeDlg::OnBnClickedButton15()
{
	ampTimes = 10;
	AfxMessageBox(_T("当前缩放倍率10"));
	// TODO: 在此添加控件通知处理程序代码
}

void CpicodeDlg::OnBnClickedButton11()
{
	ampTimes = 2;
	AfxMessageBox(_T("当前缩放倍率2"));
	// TODO: 在此添加控件通知处理程序代码
}

void CpicodeDlg::OnEnUpdateMfceditbrowse2()
{
	USES_CONVERSION;
	GetDlgItemText(IDC_MFCEDITBROWSE2, filePathC);
	uncodePic = cv::imread(W2A(filePathC));
	GetDlgItem(IDC_IMG1)->ShowWindow(FALSE);
	GetDlgItem(IDC_IMG1)->ShowWindow(TRUE);
	showImgInFrame(uncodePic, 1);
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CpicodeDlg::OnEnUpdateMfceditbrowse4()
{
	USES_CONVERSION;
	GetDlgItemText(IDC_MFCEDITBROWSE4, filePathB);
	backPic = cv::imread(W2A(filePathB));
	CImage cimg2;
	GetDlgItem(IDC_IMG2)->ShowWindow(FALSE);
	GetDlgItem(IDC_IMG2)->ShowWindow(TRUE);
	cimg2 = showImgInFrame(backPic, 2);
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CpicodeDlg::OnEnUpdateMfceditbrowse3()
{
	USES_CONVERSION;
	GetDlgItemText(IDC_MFCEDITBROWSE3, filePathD);
	toDecodePic = cv::imread(W2A(filePathD));
	GetDlgItem(IDC_IMG3)->ShowWindow(FALSE);
	GetDlgItem(IDC_IMG3)->ShowWindow(TRUE);
	showImgInFrame(toDecodePic, 3);
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
}




void CpicodeDlg::OnBnClickedButton1()
{
	CDialogEx::OnOK();
	// TODO: 在此添加控件通知处理程序代码
}
