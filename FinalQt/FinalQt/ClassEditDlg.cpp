// ClassEditDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "FinalQt.h"
#include "ClassEditDlg.h"
#include "afxdialogex.h"



// CClassEditDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CClassEditDlg, CDialog)

CClassEditDlg::CClassEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CLASSEDITDIALOG1, pParent)
	, m_ClassName(_T(""))
	, m_Attribute(_T(""))
	, m_Operation(_T(""))
	, cIndex(0)
{

}

CClassEditDlg::~CClassEditDlg()
{
}

void CClassEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CLASSNAMEEDIT, m_ClassName);
	DDX_Text(pDX, IDC_ATTRIBUTEEDIT, m_Attribute);
	DDX_Text(pDX, IDC_OPERATIONEDIT, m_Operation);
	DDX_Control(pDX, IDC_STEREOCOMBO, m_comboInput);
}


BEGIN_MESSAGE_MAP(CClassEditDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_STEREOCOMBO, &CClassEditDlg::OnCbnSelchangeStereocombo)
END_MESSAGE_MAP()


// CClassEditDlg 메시지 처리기입니다.


void CClassEditDlg::OnCbnSelchangeStereocombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cIndex = m_comboInput.GetCurSel();
	CString strItem;

}


BOOL CClassEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.	

	m_comboInput.AddString(_T("Utility"));
	m_comboInput.AddString(_T("Abstract"));
	m_comboInput.AddString(_T("Interface"));


	
	

	UpdateData(FALSE);
	m_comboInput.SetCurSel(cIndex);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
