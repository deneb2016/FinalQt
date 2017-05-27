#pragma once
#include "afxwin.h"


// CClassEditDlg 대화 상자입니다.

class CClassEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CClassEditDlg)

public:
	CClassEditDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CClassEditDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLASSEDITDIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_ClassName;
	CString m_Attribute;
	CString m_Operation;
	afx_msg void OnCbnSelchangeStereocombo();
	CComboBox m_comboInput;
	virtual BOOL OnInitDialog();
	int cIndex;
};
