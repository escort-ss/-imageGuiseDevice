// picodeDlg.h: 头文件
//
#pragma once
#include"opencv2/opencv.hpp"
#include "resource.h"
// CpicodeDlg 对话框
class CpicodeDlg : public CDialogEx
{
	// 构造
public:
	CpicodeDlg(CWnd* pParent = nullptr);

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PICODE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	cv::Mat	uncodePic;
	cv::Mat backPic;
	cv::Mat codedPic;
	cv::Mat decodedPic;
	cv::Mat toDecodePic;
	cv::Mat block;
	int ampTimes;
	int backPicS;
	int codedPicS;
	int uncodePicS;
	CString filePathC;
	CString filePathD;
	CString filePathB;

	afx_msg void OnBnClickedButton9();
	CImage showImgInFrame(cv::Mat imgcopy, int select)
	{
		cv::Mat img = imgcopy.clone();
		int width = img.cols;
		int height = img.rows;
		int channels = img.channels();
		CImage cImage;
		cImage.Create(width, height, 8 * channels); //默认图像像素单通道占用1个字节

		//copy values
		uchar* ps;
		uchar* pimg = (uchar*)cImage.GetBits(); //A pointer to the bitmap buffer
		int step = cImage.GetPitch();

		for (int i = 0; i < height; ++i)
		{
			ps = (img.ptr<uchar>(i));
			for (int j = 0; j < width; ++j)
			{
				if (channels == 1) //gray
				{
					*(pimg + i * step + j) = ps[j];
				}
				else if (channels == 3) //color
				{
					for (int k = 0; k < 3; ++k)
					{
						*(pimg + i * step + j * 3 + k) = ps[j * 3 + k];
					}
				}
			}
		}
		float cx, cy, dx, dy, k, t;//跟控件的宽和高以及图片宽和高有关的参数
		CRect   rect;//用于获取图片控件的宽和高
		cx = cImage.GetWidth();
		cy = cImage.GetHeight();//获取图片的宽 高
		k = cy / cx;//获得图片的宽高比
		CWnd* pWnd = NULL;

		switch (select)
		{
		case 1:pWnd = GetDlgItem(IDC_IMG1);
			break;
		case 2:pWnd = GetDlgItem(IDC_IMG2);
			break;
		case 3:pWnd = GetDlgItem(IDC_IMG3);
			break;
		}
		pWnd->GetClientRect(&rect);//获取Picture Control控件的客户区
		dx = rect.Width();
		dy = rect.Height();//获得控件的宽高比
		t = dy / dx;//获得控件的宽高比

		if (k >= t)
		{
			rect.right = floor(rect.bottom / k);
			rect.left = (dx - rect.right) / 2;
			rect.right = floor(rect.bottom / k) + (dx - rect.right) / 2;
		}
		else
		{
			rect.bottom = floor(k * rect.right);
			rect.top = (dy - rect.bottom) / 2;
			rect.bottom = floor(k * rect.right) + (dy - rect.bottom) / 2;
		}
		CDC* pDc = NULL;
		pDc = pWnd->GetDC();//获取picture control的DC
		int ModeOld = SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);//设置指定设备环境中的位图拉伸模式

		cImage.StretchBlt(pDc->m_hDC, rect, SRCCOPY);//显示函数
		SetStretchBltMode(pDc->m_hDC, ModeOld);

		ReleaseDC(pDc);//释放指针空间
		return cImage;
	}

public:
	void statusini()
	{
		ampTimes = 2;
		backPicS = 2;
		codedPicS = 1;
		uncodePicS = 3;
		//
		uncodePic.create(1, 1, CV_8UC1);
		decodedPic.create(1, 1, CV_8UC1);
		toDecodePic.create(1, 1, CV_8UC1);
		backPic.create(1, 1, CV_8UC1);//将嵌入小文件的背景
		codedPic.create(1, 1, CV_8UC1);//加密完成的文件
		block.create(1, 1, CV_8UC1);
		//
		block.at<cv::Vec3b>(0, 0)[0] = NULL;
		uncodePic = block.clone();
		backPic = block.clone();
		decodedPic = block.clone();
		toDecodePic = block.clone();
		codedPic = block.clone();
		//
		filePathC = char(NULL);//已加密的图片的地址
		filePathD = char(NULL);//未加密的图片的地址
		filePathB = char(NULL);//底片的地址
	}

	cv::Mat code(cv::Mat big_img, cv::Mat small_img, int step)
	{
		int big_h = big_img.rows;            //获取行数目；
		int big_w = big_img.cols;            //获取列数目；
		int small_h = small_img.rows;            //获取行数目；
		int small_w = small_img.cols;
		cv::Mat dst_im = big_img.clone();
		int map_h = 0;
		int map_w = 0;

		for (int tmpth = 0; tmpth < small_h; tmpth++)
		{
			for (int tmptw = 0; tmptw < small_w; tmptw++)
			{
				map_h = int(tmpth * step + step * 0.5);
				map_w = int(tmptw * step + step * 0.5);
				dst_im.at<cv::Vec3b>(map_h, map_w) = small_img.at<cv::Vec3b>(tmpth, tmptw);
			}
		}

		return dst_im.clone();
	}
	cv::Mat decode(cv::Mat big_img, int step)
	{
		cv::Mat dst_im;
		int big_h = big_img.rows;            //获取行数目；
		int big_w = big_img.cols;            //获取列数目；
		dst_im = big_img.clone();
		cv::resize(dst_im, dst_im, cv::Size((big_w / step), big_h / step));
		if ((big_w % step != 0))
		{
			dst_im = block.clone();//如果长宽不对，令小图片变为NULL
			AfxMessageBox(_T("图片长宽比例不正确"));
			return block.clone();
		}
		//cv::Mat dst_im = small_img.clone();

		int initial = int(step / 2);
		int map_h = 0;
		int map_w = 0;

		for (int tmpth = initial; tmpth < big_h; tmpth += step)
		{
			for (int tmptw = initial; tmptw < big_w; tmptw += step)
			{
				map_h = int(tmpth / step - 0.5);
				map_w = int(tmptw / step - 0.5);
				dst_im.at<cv::Vec3b>(map_h, map_w)[0] = big_img.at<cv::Vec3b>(tmpth, tmptw)[0];
				dst_im.at<cv::Vec3b>(map_h, map_w)[1] = big_img.at<cv::Vec3b>(tmpth, tmptw)[1];
				dst_im.at<cv::Vec3b>(map_h, map_w)[2] = big_img.at<cv::Vec3b>(tmpth, tmptw)[2];
			}
		}
		//imshow("IMG", dst_im);
		//cv::waitKey();
		return dst_im.clone();
	}
	cv::Mat resizePic(cv::Mat backPic, cv::Mat uncodePic, int ampTimes)
	{
		cv::Mat backPic1 = backPic.clone();
		int big_h = backPic1.rows;            //获取行数目；
		int big_w = backPic1.cols;            //获取列数目；
		int small_h = uncodePic.rows;            //获取行数目；
		int small_w = uncodePic.cols;		//获取列数目
		if ((big_w >= small_w) && (big_h >= small_h))
		{
			backPic1 = backPic1(cv::Rect(0, 0, small_w, small_h)).clone();
		}
		else
		{
			if (big_h / small_h <= big_w / small_w)
			{
				//backPic1.resize(small_h+2, int(big_w * small_h / big_h) + 2);
				cv::resize(backPic1, backPic1, cv::Size(big_w * (small_h / big_h) + 2, small_h + 2));
			}
			else
			{
				cv::resize(backPic1, backPic1, cv::Size(small_w + 2, big_h * (small_w / big_w) + 2));
			}
		}

		backPic1 = backPic1(cv::Rect(0, 0, small_w, small_h)).clone();
		big_h = small_h * ampTimes;
		big_w = small_w * ampTimes;

		cv::resize(backPic1, backPic1, cv::Size(big_w, big_h));
		//imshow("!", backPic);
		//cv::imwrite("2.png", backPic);
		//cv::waitKey();
		return backPic1.clone();
	}
	cv::Mat randomColorBackPic(cv::Mat backPic)
	{
		int big_h = backPic.rows;            //获取行数目；
		int big_w = backPic.cols;		//获取列数目；
		cv::Mat temptPic;
		temptPic = backPic.clone();
		int a = rand() % (255 + 1);
		int b = rand() % (255 + 1);
		int c = rand() % (255 + 1);
		for (int tmpth = 0; tmpth < big_h; tmpth++)
		{
			for (int tmptw = 0; tmptw < big_w; tmptw++)
			{
				temptPic.at<cv::Vec3b>(tmpth, tmptw)[0] = a;
				temptPic.at<cv::Vec3b>(tmpth, tmptw)[1] = b;
				temptPic.at<cv::Vec3b>(tmpth, tmptw)[2] = c;
			}
		}

		return temptPic;
	}

public:
	// 显示图片

	afx_msg void OnBnClickedToCode();

	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeMfceditbrowse4();
	afx_msg void OnEnChangeMfceditbrowse2();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnEnChangeMfceditbrowse3();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnEnUpdateMfceditbrowse2();
	afx_msg void OnEnUpdateMfceditbrowse4();
	afx_msg void OnEnUpdateMfceditbrowse3();
	afx_msg void OnBnClickedButton1();
};
