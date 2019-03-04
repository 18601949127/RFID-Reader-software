// StringGridctrlDlg.h : header file
//

#if !defined(AFX_STRINGGRIDCTRLDLG_H__E7C20BED_40B9_4B8D_BB63_B563A8D9C01C__INCLUDED_)
#define AFX_STRINGGRIDCTRLDLG_H__E7C20BED_40B9_4B8D_BB63_B563A8D9C01C__INCLUDED_

#include "GRIDCTRL\GridCtrl.h"	// Added by ClassView
#include "Thread.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CStringGridctrlDlg dialog

#define WM_USERMESSAGE WM_USER+30
#define WM_SHOWDATA WM_USER+31
#define WM_SHOWNOTE WM_USER+32
#define RED 0
#define BLUE 1
#define GREEN 2
#define ORANGE 3
//unsigned int m_colour;

class CStringGridctrlDlg : public CDialog
{
// Construction
public:
	CRect rect;
	CClientDC * m_dc;
	CStatusBar m_statusbar;
	int index;
	int lineCount;
	CString ByteToCString(void *lpData ,int Length);
	CStringGridctrlDlg(CWnd* pParent = NULL);	// standard constructor
    void clearArray();
	~CStringGridctrlDlg();
// Dialog Data
	//{{AFX_DATA(CStringGridctrlDlg)
	enum { IDD = IDD_STRINGGRIDCTRL_DIALOG };
	CProgressCtrl	m_progressctrl;
	CEdit	m_searchData;
	CStatic	m_currentNum;
	CEdit	m_taskCount;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStringGridctrlDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int lastCount;
	bool btnStopStatus;
	bool isdataSave;
	HICON m_hIcon;
	virtual void OnOK();

	// Generated message map functions
	//{{AFX_MSG(CStringGridctrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnAdd();
	afx_msg void OnBTNRead();
	afx_msg void OnBtnStart();
	afx_msg void OnBtnPause();
	afx_msg void OnBtnAddTask();
	afx_msg void OnBtnResume();
    afx_msg void OnMyMessage(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnCancel();
    afx_msg void OnMySHOWDATAMessage(WPARAM wParam,LPARAM lParam);
	afx_msg void OnMyMessageRE(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnSearch();
	afx_msg void OnBtnfocus();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnClear();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void clearData();
	CGridCtrl m_AttrGrid;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRINGGRIDCTRLDLG_H__E7C20BED_40B9_4B8D_BB63_B563A8D9C01C__INCLUDED_)
