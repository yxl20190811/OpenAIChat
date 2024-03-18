
// OpenAIChatDlg.h: 头文件
//

#pragma once

#include "TOpenAiChatThread.h"

// COpenAIChatDlg 对话框
class COpenAIChatDlg : public CDialogEx, protected TOpenAiChatThread
{
// 构造
public:
	COpenAIChatDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENAICHAT_DIALOG };
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
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedSend();
private:
	virtual void OnRecvFromOpenAI(std::string& text);
public:
	CButton m_ButtonSend;
	CEdit m_EditMsg;
	CRichEditCtrl m_EditResult;
	CComboBox m_Combox;
	CString m_text;
};
