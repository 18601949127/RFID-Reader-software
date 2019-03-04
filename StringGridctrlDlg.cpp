// StringGridctrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StringGridctrl.h"
#include "StringGridctrlDlg.h"
#include "GridCtrl/GridCtrl.h"
#include <stdlib.h>
#include "askcsc.h"
#include <string.h>
#include <string>
#include <io.h>

#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

CThread  thread;
extern CStringArray  array;



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
// CStringGridctrlDlg dialog

CStringGridctrlDlg::CStringGridctrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStringGridctrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStringGridctrlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	lineCount=0;
	index=0;
    isdataSave=false;
	//m_dc=NULL;

	
}
CStringGridctrlDlg::~CStringGridctrlDlg()
{
   if(m_dc!=NULL)
   {
	   delete m_dc;
   }
}

void CStringGridctrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

    DDX_GridControl(pDX,IDC_GRID,m_AttrGrid);

	//{{AFX_DATA_MAP(CStringGridctrlDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_progressctrl);
	DDX_Control(pDX, IDC_EDIT2, m_searchData);
	DDX_Control(pDX, IDC_STATIC1, m_currentNum);
	DDX_Control(pDX, IDC_EDIT1, m_taskCount);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStringGridctrlDlg, CDialog)
	//{{AFX_MSG_MAP(CStringGridctrlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Btn1, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_Read, OnBTNRead)
	ON_BN_CLICKED(IDC_BtnStart, OnBtnStart)
	ON_BN_CLICKED(IDC_BtnPause, OnBtnPause)
	ON_BN_CLICKED(IDC_BtnAddTask, OnBtnAddTask)
	ON_BN_CLICKED(IDC_BtnResume, OnBtnResume)
    ON_MESSAGE(WM_USERMESSAGE,OnMyMessage)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BtnCancel, OnBtnCancel)
	ON_MESSAGE(WM_SHOWDATA,OnMySHOWDATAMessage)
	ON_MESSAGE(WM_SHOWNOTE,OnMyMessageRE)
	ON_BN_CLICKED(IDC_BtnDelete, OnBtnDelete)
	ON_BN_CLICKED(IDC_BtnSearch, OnBtnSearch)
	ON_BN_CLICKED(IDC_Btnfocus, OnBtnfocus)
	ON_BN_CLICKED(IDC_BtnSave, OnBtnSave)
	ON_BN_CLICKED(IDC_BtnClear, OnBtnClear)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStringGridctrlDlg message handlers

BOOL CStringGridctrlDlg::OnInitDialog()
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
    CString str;
    ::GetPrivateProfileString("General","Name","港铁写信息软件1.0-1号机",str.GetBuffer(50),50,".\\Port.ini");
	SetWindowText(str);

    CThread::m_windowname=str;
	SetTimer(1,100,NULL);
    SetTimer(2,100,NULL);
	SetTimer(3,200,NULL);
	// TODO: Add extra initialization here
	//GetDlgItem(IDC_Btn1)->EnableWindow(false);
    GetDlgItem(IDC_BtnResume)->EnableWindow(false);


	m_AttrGrid.SetColumnCount(3);
    m_AttrGrid.SetColumnWidth(1,180);
    m_AttrGrid.SetColumnWidth(2,160);
	m_AttrGrid.SetRowCount(1);

	m_AttrGrid.SetFixedRowCount(1);
    m_AttrGrid.SetFixedRowSelection(true);
	m_AttrGrid.SetRowHeight(0,30);
    //m_AttrGrid.SetRowHeight(1,30);
	m_AttrGrid.SetFixedColumnCount(1);
    m_AttrGrid.SetFixedColumnSelection(true);

	m_AttrGrid.SetItemText(0,0,"Number");
    m_AttrGrid.SetItemText(0,1,"UID");
    m_AttrGrid.SetItemText(0,2,"OTP");
	m_AttrGrid.SetRowResize(false);
	m_AttrGrid.SetColumnResize(false);
	m_AttrGrid.SetEditable(false);


      
   //  CString strTCD;
	 CString strReader;

     //::GetPrivateProfileString("General","TCDPortName","COM1",str.GetBuffer(20),20,".\\Port.ini");
	// CThread::TCDPortName=str;
	 //strTCD.Format("TCD:%s",str);

     ::GetPrivateProfileString("General","ReaderPortName","COM2",str.GetBuffer(20),20,".\\Port.ini");
     CThread::readerPortName=str;
	 strReader.Format("Reader:%s",str);


     UINT array[3];
	 for(int i=0;i<3;i++)
	 {
		 array[i]=100+i;
	 }
     m_statusbar.Create(this);
	 m_statusbar.SetIndicators(array,sizeof(array)/sizeof(UINT));
	 for(int n=0;n<2;n++)
	 {
		 m_statusbar.SetPaneInfo(n,array[n],0,80);
	 }
     m_statusbar.SetPaneInfo(1,array[1],0,800);
//	 m_statusbar.SetPaneText(0,strTCD);
     m_statusbar.SetPaneText(0,strReader);
	 RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);

	 RECT m_rect;
	 m_statusbar.GetItemRect(1,&m_rect);

     //m_progressctrl.Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH,m_rect, this, 1);
     m_progressctrl.SetParent(&m_statusbar);
	 m_progressctrl.MoveWindow(&m_rect);
	 m_progressctrl.SetStep(1);

	 m_progressctrl.SetRange(0,25);//设置进度条范围

     //m_progressctrl.SetPos(60);
    
	m_dc=new CClientDC(this);
	rect=CRect(100,420,200,460);

      


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStringGridctrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CStringGridctrlDlg::OnPaint() 
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
HCURSOR CStringGridctrlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
COLORREF  col=RGB(255,0,0);
void CStringGridctrlDlg::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
   
    //if(thread.Stop())
	//{
      //GetDlgItem(IDC_Btn1)->EnableWindow(false);
     //GetDlgItem(IDC_BtnStart)->EnableWindow(true);
	//}

            // COLORREF  col=RGB(255,0,0);
	        //m_dc->Rectangle(m_rect);
	        //m_dc->FillSolidRect(m_rect,col);
	 
	 
     COLORREF  col=RGB(255,0,0);
	 m_dc->Ellipse(rect);
	 m_dc->FillSolidRect(rect,col);
	 
     
	
	
    
     PlaySound("guyong.wav", NULL, SND_FILENAME | SND_ASYNC);

}

void CStringGridctrlDlg::OnBTNRead() 
{

    CCellID cell(lineCount,1);
	m_AttrGrid.EnsureVisible(cell);
}

void CStringGridctrlDlg::OnBtnStart() 
{
	// TODO: Add your control notification handler code here

    //CString str="11";
	
   // const char hexCode[]={'0','1','2','3','4','5','6','7','8','9','2','B','C','D','E','F'};
    //str=str+hexCode[11];
	//AfxMessageBox(str);

     
	 
	 //if(thread.Start())
	// {
	 //GetDlgItem(IDC_Btn1)->EnableWindow(true);
      //IDC_BtnStart
    // GetDlgItem(IDC_BtnStart)->EnableWindow(false);
	   //GetDlgItem(IDC_BtnStart)->SetWindowText("停止");

	// }
     char ch1[10];
	 GetDlgItem(IDC_BtnStart)->GetWindowText(ch1,10);
	 if(!strcmp(ch1,"开始"))
	 {
          thread.Start();
		  Sleep(200);
          GetDlgItem(IDC_BtnStart)->SetWindowText("停止");
	 }
	 else
	 { 
          thread.Stop();
		  CThread::CancelTask();
		  Sleep(200);
          GetDlgItem(IDC_BtnStart)->SetWindowText("开始");
	 }


   //SendMessage(WM_USERMESSAGE);
	     
}

CString CStringGridctrlDlg::ByteToCString(void *lpData, int Length)
{
    BYTE *lpByte=(BYTE *)lpData;
	CString str="";
	const char hexCode[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	for(int i=0;i<Length;i++)
	{
        str=str+hexCode[(*lpByte)>>4];
		str=str+hexCode[(*lpByte)&0x0F];
		lpByte++;
	}
	return str;

}

void CStringGridctrlDlg::OnBtnPause() 
{
	// TODO: Add your control notification handler code here
	CThread::PauseTask();
    GetDlgItem(IDC_BtnPause)->EnableWindow(false);
    GetDlgItem(IDC_BtnResume)->EnableWindow(true);

}

void CStringGridctrlDlg::OnBtnAddTask() 
{
	// TODO: Add your control notification handler code here
    int num1;
	char ch1[10];
	m_taskCount.GetWindowText(ch1,10);
    num1=atoi(ch1);
    CThread::AddTask(num1);
	m_progressctrl.SetPos(0);
}

void CStringGridctrlDlg::OnBtnResume() 
{
	// TODO: Add your control notification handler code here
	CThread::ResumeTask();
	GetDlgItem(IDC_BtnPause)->EnableWindow(true);
    GetDlgItem(IDC_BtnResume)->EnableWindow(false);
}

BOOL CStringGridctrlDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	thread.Stop();
	return CDialog::DestroyWindow();
}
void CStringGridctrlDlg::OnMyMessage(WPARAM wParam,LPARAM lParam)
{

     if(thread.Stop())
	{
	 CThread::TaskCount=0;
	 Sleep(200);
     GetDlgItem(IDC_BtnStart)->SetWindowText("开始");
	}
}

void CStringGridctrlDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case 1:
		{
			int num=CThread::TaskCount;
            char ch1[10];
	        itoa(num,ch1,10);
            m_currentNum.SetWindowText(ch1);
		//	m_colour=BLUE;

		   // CRect rect(50,50,100,100);
           // InvalidateRect(rect);
			 
			//Invalidate();
		;
			break;
	      
		}

	
	case 2:
		{
			if((lastCount>0)&&(CThread::TaskCount<1))
			{
                 PlaySound("guyong.wav", NULL, SND_FILENAME | SND_ASYNC);
			}
            lastCount=CThread::TaskCount;
		//	m_colour=GREEN;
			//Invalidate();
			break;
				
		}
	case 3:
		{
			CTime t1 = CTime::GetCurrentTime();
            CString s = t1.Format("%H:%M:%S");
           // GetDlgItem(IDC_Btn1)->SetWindowText(s);
		   COLORREF  col=RGB(255,0,0);
	       m_dc->Ellipse(rect);
	       m_dc->FillSolidRect(rect,col);
		}
	}
	 CDialog::OnTimer(nIDEvent);

}

//DEL void CStringGridctrlDlg::OnCancelMode() 
//DEL {
//DEL 	CDialog::OnCancelMode();
//DEL 	
//DEL 	// TODO: Add your message handler code here
//DEL 	
//DEL }

void CStringGridctrlDlg::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here

	//CThread::TaskCount=0;
	CThread::CancelTask();
}
void CStringGridctrlDlg::OnMySHOWDATAMessage(WPARAM wParam,LPARAM lParam)
{
    KillTimer(3);
    BYTE Data[20];

	memcpy(Data,(BYTE*)wParam,20);

	CString str=this->ByteToCString(Data,11);

    //char *p=new char[30]; 
    // p=str.GetBuffer(str.GetLength()); 

    char p[30];
	strcpy(p,str.GetBuffer(str.GetLength()));
    str.ReleaseBuffer();

    p[22]='\0';
    char UID[16];
	char OTP[10];
	for(int i=0;i<14;i++)
	{
       UID[i]=p[i];
	}
    UID[14]='\0';
	memcpy(OTP,&p[14],8);
	OTP[8]='\0';
	lineCount++;
    char ch1[10];
	itoa(lineCount,ch1,10);
    m_AttrGrid.InsertRow(ch1,-1);
    m_AttrGrid.Invalidate(true);

    m_AttrGrid.SetRowHeight(lineCount,30);
    m_AttrGrid.SetItemText(lineCount,1,UID);
    m_AttrGrid.SetItemText(lineCount,2,OTP);
	CCellID cell(lineCount,1);
	//m_AttrGrid.EnsureVisible(cell);
    m_AttrGrid.GuYong(lineCount,1);
	m_AttrGrid.SetFocusCell(cell);
	m_progressctrl.StepIt();
	COLORREF  col=RGB(0,255,0);
	m_dc->Rectangle(rect);
	m_dc->FillSolidRect(rect,col);
	 SetTimer(3,500,NULL);
}

void CStringGridctrlDlg::OnBtnDelete() 
{
	// TODO: Add your control notification handler code here
if(index==0||index>lineCount)
	  { 
          AfxMessageBox("待删除标签不存在");
		  return;
	  }
	  if(lineCount==1)
	  {
          this->clearData();
		  return;
	  }
   
      m_AttrGrid.DeleteRow(index);
	  m_AttrGrid.Invalidate(true);
	  for(int i=index;i<lineCount+1;i++)
	  {
		 char ch1[10];
		 itoa(i,ch1,10);
         m_AttrGrid.SetItemText(i,0,ch1);
		 
	  }
	  lineCount--;
	 // m_AttrGrid.Invalidate(tru
	 // m_AttrGrid.Invalidate(true);
}

void CStringGridctrlDlg::OnBtnSearch() 
{
	// TODO: Add your control notification handler code here
    int	nSelRow	= m_AttrGrid.GetFocusCell().row;

     m_searchData.SetWindowText(m_AttrGrid.GetItemText(nSelRow,1));
    char ch1[20];

	m_searchData.GetWindowText(ch1,20);
    CString str;
	
	str.Format("%s",ch1);
	for(int i=0;i<lineCount;i++)
	{
        if(str==m_AttrGrid.GetItemText(i+1,1))
		{
			//AfxMessageBox("");
             CCellID cell(i+1,1);
		     m_AttrGrid.EnsureVisible(cell);
             m_AttrGrid.SetFocusCell(cell);
			 index=i+1;
			 return;
		}
	}
    AfxMessageBox("没有找到指定标签");
}

void CStringGridctrlDlg::OnBtnfocus() 
{
	// TODO: Add your control notification handler code here
	    if(lineCount>1)
		{
		//CCellID cell(lineCount,1);
		//m_AttrGrid.EnsureVisible(cell);
       // m_AttrGrid.SetFocusCell(cell);
			m_AttrGrid.GuYong(lineCount,1);

		}
	
}

void CStringGridctrlDlg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
    if(_access("logfile",0)==-1) 
	{
         AfxMessageBox("logfile文件夹不存在");
		 return;
	}
     CString str;
	 char ch1[20];
	 char ch2[20];
	 GetDlgItem(IDC_EDIT3)->GetWindowText(ch1,20);
     GetDlgItem(IDC_EDIT4)->GetWindowText(ch2,20);
	 str.Format("logfile\\HKT-%s.hk.csv",ch1);
	 if(_access(str,0)==0)
	 {
           AfxMessageBox("文件已经存在无法保存");
		   return;
	 }
	 FILE* file;
	 file=fopen(str,"w");

	 for(int i=0;i<lineCount;i++)
	 {
       //int fprintf(FILE *stream,char *format,[argument])
        str=m_AttrGrid.GetItemText(i+1,1);
		fprintf(file,"00000000,%s,%s,,,,\n",str,ch2);
	 }

	 fclose(file);
	 isdataSave=true;
     AfxMessageBox("文件保存成功,谢谢!");


}

void CStringGridctrlDlg::OnBtnClear() 
{
	// TODO: Add your control notification handler code here
	if((isdataSave==false)&&(lineCount>0))
	{
         if(IDOK!=AfxMessageBox("数据没有保存,你确定删除数据吗?",MB_OKCANCEL|MB_APPLMODAL|MB_ICONWARNING))
		 {
			 return;
		 }
	}

	this->clearData();
	clearArray();

}

void CStringGridctrlDlg::clearData()
{
    m_AttrGrid.SetColumnCount(3);
    m_AttrGrid.SetColumnWidth(1,180);
    m_AttrGrid.SetColumnWidth(2,160);
	m_AttrGrid.SetRowCount(1);

	m_AttrGrid.SetFixedRowCount(1);
    m_AttrGrid.SetFixedRowSelection(true);
	m_AttrGrid.SetRowHeight(0,30);
    //m_AttrGrid.SetRowHeight(1,30);
	m_AttrGrid.SetFixedColumnCount(1);
    m_AttrGrid.SetFixedColumnSelection(true);

	m_AttrGrid.SetItemText(0,0,"Number");
    m_AttrGrid.SetItemText(0,1,"UID");
    m_AttrGrid.SetItemText(0,2,"OTP");
	m_AttrGrid.SetRowResize(false);
	m_AttrGrid.SetColumnResize(false);
	m_AttrGrid.SetEditable(false);
    lineCount=0;
    isdataSave=false;
}

HBRUSH CStringGridctrlDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
     CFont font;
	 font.CreatePointFont(200,"黑体");
     COLORREF m_myColor;
     m_myColor=RGB(255,0,0);
 
    if(pWnd->GetDlgCtrlID()==IDC_STATIC1)  
    {  
        pDC->SelectObject(&font);    // 设置字体  
        pDC->SetTextColor(m_myColor);    // 设置颜色     
    }
	//if(pWnd->GetDlgCtrlID()==IDC_STATIC2)
	//{
		//HBRUSH m_br=::CreateSolidBrush(m_myColor);
		//return m_br;
//	}
	
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
void CStringGridctrlDlg::clearArray()
{
    if(array.GetSize()>0);
	{     
		array.RemoveAll();
	}// Pointers removed but objects not deleted.

}
void CStringGridctrlDlg::OnMyMessageRE(WPARAM wParam,LPARAM lParam)
{
	 KillTimer(3);
     COLORREF  col=RGB(0,0,255);
	 m_dc->Rectangle(rect);
	 m_dc->FillSolidRect(rect,col);
	  SetTimer(3,500,NULL);
}
void CStringGridctrlDlg::OnOK()
{

}
