#pragma once
#include "afxwin.h"


// CClassEditDlg ��ȭ �����Դϴ�.

class CClassEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CClassEditDlg)

public:
	CClassEditDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CClassEditDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLASSEDITDIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
