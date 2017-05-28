// LineEdit.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "FinalQt.h"
#include "LineEdit.h"
#include "afxdialogex.h"


// CLineEdit 대화 상자입니다.

IMPLEMENT_DYNAMIC(CLineEdit, CDialog)

CLineEdit::CLineEdit(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

CLineEdit::~CLineEdit()
{
}

void CLineEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ComboIndex);
}


BEGIN_MESSAGE_MAP(CLineEdit, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CLineEdit::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CLineEdit 메시지 처리기입니다.


BOOL CLineEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_ComboIndex.AddString(_T("Generalization"));
	m_ComboIndex.AddString(_T("Realization"));
	m_ComboIndex.AddString(_T("Dependency"));
	m_ComboIndex.AddString(_T("Association"));

	UpdateData(FALSE);
	m_ComboIndex.SetCurSel(cIndex);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CLineEdit::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cIndex = m_ComboIndex.GetCurSel();
}
