#pragma once
#include "afxwin.h"


// CLineEdit ��ȭ �����Դϴ�.

class CLineEdit : public CDialog
{
	DECLARE_DYNAMIC(CLineEdit)

public:
	CLineEdit(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLineEdit();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ComboIndex;
	int cIndex;
	virtual BOOL OnInitDialog();
};
