// DataBindingDlg.h : header file
//
//{{AFX_INCLUDES()
#include "datagrid.h"
//}}AFX_INCLUDES

#include "ado2.h"

#if !defined(AFX_DATABINDINGDLG_H__475D4354_C673_4F80_B817_904404356FFD__INCLUDED_)
#define AFX_DATABINDINGDLG_H__475D4354_C673_4F80_B817_904404356FFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDataBindingDlg dialog

class CDataBindingDlg : public CDialog
{
// Construction
public:
	CDataBindingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDataBindingDlg)
	enum { IDD = IDD_DATABINDING_DIALOG };
	CDataGrid	m_datagridctrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataBindingDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CADORecordset m_pRs;
	CADODatabase m_pDb;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDataBindingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATABINDINGDLG_H__475D4354_C673_4F80_B817_904404356FFD__INCLUDED_)
