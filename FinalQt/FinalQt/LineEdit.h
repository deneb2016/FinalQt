#pragma once
#include "afxwin.h"


// CLineEdit 대화 상자입니다.

class CLineEdit : public CDialog
{
	DECLARE_DYNAMIC(CLineEdit)

public:
	CLineEdit(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLineEdit();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ComboIndex;
	int cIndex;
	virtual BOOL OnInitDialog();
};
