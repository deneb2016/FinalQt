// ClassEditDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FinalQt.h"
#include "ClassEditDlg.h"
#include "afxdialogex.h"



// CClassEditDlg ��ȭ �����Դϴ�.

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


// CClassEditDlg �޽��� ó�����Դϴ�.


void CClassEditDlg::OnCbnSelchangeStereocombo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	cIndex = m_comboInput.GetCurSel();
	CString strItem;

}


BOOL CClassEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.	

	m_comboInput.AddString(_T("Utility"));
	m_comboInput.AddString(_T("Abstract"));
	m_comboInput.AddString(_T("Interface"));


	
	

	UpdateData(FALSE);
	m_comboInput.SetCurSel(cIndex);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
