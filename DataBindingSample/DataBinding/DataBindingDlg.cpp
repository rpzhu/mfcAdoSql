// DataBindingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataBinding.h"
#include "DataBindingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataBindingDlg dialog

CDataBindingDlg::CDataBindingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataBindingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataBindingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDataBindingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataBindingDlg)
	DDX_Control(pDX, IDC_DATAGRID, m_datagridctrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDataBindingDlg, CDialog)
	//{{AFX_MSG_MAP(CDataBindingDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataBindingDlg message handlers

BOOL CDataBindingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CString strConnection = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=AOI_SPC_USER-PC_20210602.mdb");
	//strConnection = _T("Driver={SQL Server};Server=sysdevpdc;Trusted_Connection=Yes;Database=sysDev;uid=sa;pdw=");
	if(m_pDb.Open(strConnection))
	{	
		m_pRs = CADORecordset(&m_pDb);

		if(m_pRs.Open("msglog", CADORecordset::openTable))
		//if(m_pRs.Open("sysTable01", CADORecordset::openTable))
		{
			m_datagridctrl.SetCaption("Clients");
			m_datagridctrl.SetRefDataSource(NULL);
			m_datagridctrl.SetRefDataSource((LPUNKNOWN)m_pRs.GetRecordset());
			m_datagridctrl.Refresh();
		}
		m_pRs.AddNew();
		m_pRs.SetFieldValue("ID", 219);
		m_pRs.SetFieldValue("TestComputerName", CString("Client 05"));
		m_pRs.SetFieldValue("ProductName", CString("Client 05"));
		m_pRs.SetFieldValue("RefName", CString("Client 05"));
		m_pRs.SetFieldValue("PartNo", CString("Client 05"));
		m_pRs.SetFieldValue("PCBNAME", CString("Client 05"));
		m_pRs.SetFieldValue("BARCODE", CString("Client 05"));
		m_pRs.SetFieldValue("FOV", 0);
		m_pRs.SetFieldValue("CheckFormatTime", CString("100"));
		//m_pRs.SetFieldValue("PicPath", CString("E:\\abc.jpg"));
		_StreamPtr pStm;
		pStm.CreateInstance("ADODB.Stream");
		variant_t varBLOB, varOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
		pStm->PutType(adTypeBinary);
		pStm->Open(varOptional, adModeUnknown, adOpenStreamUnspecified, _bstr_t(), _bstr_t());
		pStm->LoadFromFile(_bstr_t("E:\\vc6Mfc\\ado\\DataBindingSample\\DataBinding\\2.jpg"));				//¶ÁÈëÎÄ¼þ 
		varBLOB = pStm->Read(adReadAll);
		_bstr_t a = varBLOB;
		m_pRs.GetRecordset()->GetFields()->GetItem("PicPath")->AppendChunk(varBLOB);

		//m_pRs.AppendChunk("PicPath",,1024);
		m_pRs.Update();
		m_datagridctrl.Refresh();
		//Sample of GetChunck
		//char data[1024];
		//m_pRs.GetChunk("Document", (LPVOID)&data);
	}
	else
	{
		AfxMessageBox(m_pDb.GetLastErrorString());
		DWORD dwError = m_pDb.GetLastError();
		return FALSE;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDataBindingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDataBindingDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDataBindingDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CDataBindingDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	//m_pRs.Close();
	//m_pDb.Close();
	return CDialog::DestroyWindow();
}
