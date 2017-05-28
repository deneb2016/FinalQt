// LineEdit.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FinalQt.h"
#include "LineEdit.h"
#include "afxdialogex.h"


// CLineEdit ��ȭ �����Դϴ�.

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


// CLineEdit �޽��� ó�����Դϴ�.


BOOL CLineEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_ComboIndex.AddString(_T("Generalization"));
	m_ComboIndex.AddString(_T("Realization"));
	m_ComboIndex.AddString(_T("Dependency"));
	m_ComboIndex.AddString(_T("Association"));

	UpdateData(FALSE);
	m_ComboIndex.SetCurSel(cIndex);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CLineEdit::OnCbnSelchangeCombo1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	cIndex = m_ComboIndex.GetCurSel();
}
