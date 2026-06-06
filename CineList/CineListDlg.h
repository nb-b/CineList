
// CineListDlg.h : header file
//

#pragma once
#include "Film.h"

// CCineListDlg dialog
class CCineListDlg : public CDialogEx
{
// Construction
public:
	CCineListDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CINELIST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CFont m_fontHeading;

	afx_msg void OnBnClickedBtnTambah();
	void UpdateListCtrl();
	MovieLinkedList m_movieList;
	CButton BTN_TAMBAH;
	afx_msg void OnBnClickedBtnCari();
	afx_msg void OnBnClickedBtnSort();
	afx_msg void OnBnClickedBtnHapus();
	afx_msg void OnBnClickedBtnEdit();
	afx_msg void OnNMDblclkListFilm(NMHDR* pNMHDR, LRESULT* pResult);

	bool IsDuplicate(CString targetKode, CString targetJudul, bool isEditMode);
	bool ValidateInputData(CString& kode, CString& judul, CString& genre, CString& strTahun, CString& strRating, CString& sutradara);
	afx_msg void OnBnClickedBtnPrint();
};
