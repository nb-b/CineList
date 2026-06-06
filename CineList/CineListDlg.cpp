
// CineListDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "CineList.h"
#include "CineListDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCineListDlg dialog



CCineListDlg::CCineListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CINELIST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCineListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_TAMBAH, BTN_TAMBAH);
}

BEGIN_MESSAGE_MAP(CCineListDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_TAMBAH, &CCineListDlg::OnBnClickedBtnTambah)
	ON_BN_CLICKED(IDC_BTN_CARI, &CCineListDlg::OnBnClickedBtnCari)
	ON_BN_CLICKED(IDC_BTN_SORT, &CCineListDlg::OnBnClickedBtnSort)
	ON_BN_CLICKED(IDC_BTN_HAPUS, &CCineListDlg::OnBnClickedBtnHapus)
	ON_BN_CLICKED(IDC_BTN_EDIT, &CCineListDlg::OnBnClickedBtnEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FILM, &CCineListDlg::OnNMDblclkListFilm)
	ON_BN_CLICKED(IDC_BTN_PRINT, &CCineListDlg::OnBnClickedBtnPrint)
END_MESSAGE_MAP()


// CCineListDlg message handlers

BOOL CCineListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	// ==ICON
	int targetLebar = 16;
	int targetTinggi = 16;
	HICON hIconSort = (HICON)::LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_ICON_SORT),
		IMAGE_ICON,
		targetLebar, targetTinggi,
		LR_DEFAULTCOLOR);

	HICON hIconPrint = (HICON)::LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_ICON_PRINT),
		IMAGE_ICON,
		targetLebar, targetTinggi,
		LR_DEFAULTCOLOR);
	CButton* pBtnSort = (CButton*)GetDlgItem(IDC_BTN_SORT);
	CButton* pBtnLaporan = (CButton*)GetDlgItem(IDC_BTN_PRINT);
	if (pBtnSort != nullptr) pBtnSort->SetIcon(hIconSort);
	if (pBtnLaporan != nullptr) pBtnLaporan->SetIcon(hIconPrint);

	//==HEADING
	m_fontHeading.CreatePointFont(120, _T("Segoe UI"));
	GetDlgItem(IDC_STATIC_HEADING1)->SetFont(&m_fontHeading);
	GetDlgItem(IDC_STATIC_HEADING2)->SetFont(&m_fontHeading);

	// ==SEED
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST_FILM);
	pList->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	pList->InsertColumn(0, _T("Kode"), LVCFMT_LEFT, 50);
	pList->InsertColumn(1, _T("Judul"), LVCFMT_LEFT, 150);
	pList->InsertColumn(2, _T("Genre"), LVCFMT_LEFT, 100);
	pList->InsertColumn(3, _T("Tahun"), LVCFMT_LEFT, 60);
	pList->InsertColumn(4, _T("Rating"), LVCFMT_LEFT, 50);
	pList->InsertColumn(5, _T("Sutradara"), LVCFMT_LEFT, 120);

	m_movieList.AddMovie({ _T("M001"), _T("The Matrix"), _T("Sci-Fi"), 1999, 8.7, _T("Lana Wachowski") });
	m_movieList.AddMovie({ _T("M002"), _T("Inception"), _T("Action"), 2010, 8.8, _T("Christopher Nolan") });
	m_movieList.AddMovie({ _T("M003"), _T("Parasite"), _T("Thriller"), 2019, 8.5, _T("Bong Joon Ho") });
	m_movieList.AddMovie({ _T("M004"), _T("Spirited Away"), _T("Animation"), 2001, 8.6, _T("Hayao Miyazaki") });
	m_movieList.AddMovie({ _T("M005"), _T("Interstellar"), _T("Sci-Fi"), 2014, 8.6, _T("Christopher Nolan") });
	UpdateListCtrl();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCineListDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCineListDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCineListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CCineListDlg::IsDuplicate(CString targetKode, CString targetJudul, bool isEditMode)
{
	MovieNode* temp = m_movieList.head;
	while (temp != nullptr) {
		if (!isEditMode && temp->data.kode.CompareNoCase(targetKode) == 0) {
			AfxMessageBox(_T("Kode film ini sudah terdaftar pada record lain."));
			return true;
		}

		if (temp->data.judul.CompareNoCase(targetJudul) == 0) {
			if (!isEditMode || temp->data.kode.CompareNoCase(targetKode) != 0) {
				AfxMessageBox(_T("Judul film ini sudah terdaftar pada record lain."));
				return true;
			}
		}

		temp = temp->next;
	}
	return false;
}

bool CCineListDlg::ValidateInputData(CString& kode, CString& judul, CString& genre, CString& strTahun, CString& strRating, CString& sutradara)
{
	kode.Trim(); judul.Trim(); genre.Trim();
	strTahun.Trim(); strRating.Trim(); sutradara.Trim();

	if (kode.IsEmpty() || judul.IsEmpty() || genre.IsEmpty() ||
		strTahun.IsEmpty() || strRating.IsEmpty() || sutradara.IsEmpty()) {
		AfxMessageBox(_T("Seluruh kolom data wajib diisi penuh. Tidak boleh ada yang kosong."));
		return false;
	}

	for (int i = 0; i < strTahun.GetLength(); i++) {
		if (!_istdigit(strTahun[i])) {
			AfxMessageBox(_T("Tahun rilis harus berupa angka solid tanpa karakter huruf/simbol."));
			return false;
		}
	}

	int tahun = _ttoi(strTahun);
	if (tahun < 1800 || tahun > 2100) {
		AfxMessageBox(_T("Parameter tahun rilis di luar batas rentang logis."));
		return false;
	}

	int dotCount = 0;
	for (int i = 0; i < strRating.GetLength(); i++) {
		if (strRating[i] == _T('.')) {
			dotCount++;
		}
		else if (!_istdigit(strRating[i])) {
			AfxMessageBox(_T("Rating harus berupa angka desimal. Gunakan titik (.) untuk pemisah."));
			return false;
		}
	}

	if (dotCount > 1) {
		AfxMessageBox(_T("Format angka desimal rating korup (terlalu banyak titik)."));
		return false;
	}

	double rating = _ttof(strRating);
	if (rating < 0.0 || rating > 10.0) {
		AfxMessageBox(_T("Batas rentang rating hanya diizinkan antara 0.0 hingga 10.0."));
		return false;
	}

	return true;
}


void CCineListDlg::UpdateListCtrl() {
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST_FILM);
	pList->DeleteAllItems();

	MovieNode* temp = m_movieList.head;
	int index = 0;
	while (temp != nullptr) {
		pList->InsertItem(index, temp->data.kode);
		pList->SetItemText(index, 1, temp->data.judul);
		pList->SetItemText(index, 2, temp->data.genre);

		CString strTahun, strRating;
		strTahun.Format(_T("%d"), temp->data.tahun);
		strRating.Format(_T("%.1f"), temp->data.rating);

		pList->SetItemText(index, 3, strTahun);
		pList->SetItemText(index, 4, strRating);
		pList->SetItemText(index, 5, temp->data.sutradara);

		temp = temp->next;
		index++;
	}
}

void CCineListDlg::OnBnClickedBtnTambah()
{
	CString kode, judul, genre, strTahun, strRating, sutradara;

	GetDlgItemText(IDC_EDIT_KODE, kode);
	GetDlgItemText(IDC_EDIT_JUDUL, judul);
	GetDlgItemText(IDC_EDIT_GENRE, genre);
	GetDlgItemText(IDC_EDIT_TAHUN, strTahun);
	GetDlgItemText(IDC_EDIT_RATING, strRating);
	GetDlgItemText(IDC_EDIT_SUTRADARA, sutradara);

	if (kode.IsEmpty() || judul.IsEmpty()) {
		AfxMessageBox(_T("Error: Kode dan Judul wajib diisi."));
		return;
	}

	if (!ValidateInputData(kode, judul, genre, strTahun, strRating, sutradara)) {
		return;
	}

	if (IsDuplicate(kode, judul, false)) {
		return;
	}

	MovieNode* temp = m_movieList.head;
	while (temp != nullptr) {
		if (temp->data.kode.CompareNoCase(kode) == 0) {
			AfxMessageBox(_T("Kode film ini sudah ada."));
			return;
		}
		temp = temp->next;
	}

	Film newMovie;
	newMovie.kode = kode;
	newMovie.judul = judul;
	newMovie.genre = genre;
	newMovie.tahun = _ttoi(strTahun);
	newMovie.rating = _ttof(strRating);
	newMovie.sutradara = sutradara;

	m_movieList.AddMovie(newMovie);
	UpdateListCtrl();

	SetDlgItemText(IDC_EDIT_KODE, _T(""));
	SetDlgItemText(IDC_EDIT_JUDUL, _T(""));
	SetDlgItemText(IDC_EDIT_GENRE, _T(""));
	SetDlgItemText(IDC_EDIT_TAHUN, _T(""));
	SetDlgItemText(IDC_EDIT_RATING, _T(""));
	SetDlgItemText(IDC_EDIT_SUTRADARA, _T(""));
}


void CCineListDlg::OnBnClickedBtnCari()
{
	CString keyword;
	GetDlgItemText(IDC_EDIT_CARI, keyword);

	if (keyword.IsEmpty()) {
		UpdateListCtrl();
		return;
	}

	MovieNode* result = m_movieList.SearchMovie(keyword, true);

	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST_FILM);
	pList->DeleteAllItems();

	if (result != nullptr) {
		pList->InsertItem(0, result->data.kode);
		pList->SetItemText(0, 1, result->data.judul);
		pList->SetItemText(0, 2, result->data.genre);

		CString strTahun, strRating;
		strTahun.Format(_T("%d"), result->data.tahun);
		strRating.Format(_T("%.1f"), result->data.rating);

		pList->SetItemText(0, 3, strTahun);
		pList->SetItemText(0, 4, strRating);
		pList->SetItemText(0, 5, result->data.sutradara);
	}
	else {
		AfxMessageBox(_T("Informasi: Film tidak ditemukan."));
	}
}



void CCineListDlg::OnBnClickedBtnSort()
{
	if (m_movieList.head == nullptr || m_movieList.head->next == nullptr) {
		return;
	}

	m_movieList.SortByYear();
	UpdateListCtrl();
}


void CCineListDlg::OnBnClickedBtnHapus()
{
	CString kode;
	GetDlgItemText(IDC_EDIT_KODE, kode);

	if (kode.IsEmpty()) {
		AfxMessageBox(_T("Error: Masukkan Kode film yang ingin dihapus."));
		return;
	}

	bool status = m_movieList.DeleteMovie(kode);

	if (status) {
		UpdateListCtrl();
		AfxMessageBox(_T("Sukses: Data terhapus."));
		SetDlgItemText(IDC_EDIT_KODE, _T(""));
	}
	else {
		AfxMessageBox(_T("Error: Kode film tidak ditemukan."));
	}
}


void CCineListDlg::OnBnClickedBtnEdit()
{
	CString kode, judul, genre, strTahun, strRating, sutradara;

	GetDlgItemText(IDC_EDIT_KODE, kode);
	if (kode.IsEmpty()) {
		AfxMessageBox(_T("Error: Masukkan Kode film yang ingin diedit atau double click item pada Tabel List."));
		return;
	}

	GetDlgItemText(IDC_EDIT_JUDUL, judul);
	GetDlgItemText(IDC_EDIT_GENRE, genre);
	GetDlgItemText(IDC_EDIT_TAHUN, strTahun);
	GetDlgItemText(IDC_EDIT_RATING, strRating);
	GetDlgItemText(IDC_EDIT_SUTRADARA, sutradara);

	if (!ValidateInputData(kode, judul, genre, strTahun, strRating, sutradara)) {
		return;
	}

	if (IsDuplicate(kode, judul, true)) {
		return;
	}

	Film updatedMovie;
	updatedMovie.kode = kode;
	updatedMovie.judul = judul;
	updatedMovie.genre = genre;
	updatedMovie.tahun = _ttoi(strTahun);
	updatedMovie.rating = _ttof(strRating);
	updatedMovie.sutradara = sutradara;

	bool status = m_movieList.EditMovie(kode, updatedMovie);

	if (status) {
		UpdateListCtrl();
		AfxMessageBox(_T("Sukses: Data berhasil diubah."));
	}
	else {
		AfxMessageBox(_T("Error: Kode film tidak ditemukan di memori."));
	}
}

void CCineListDlg::OnNMDblclkListFilm(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int nIndex = pNMItemActivate->iItem;

	if (nIndex == -1) {
		*pResult = 0;
		return;
	}

	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST_FILM);

	SetDlgItemText(IDC_EDIT_KODE, pList->GetItemText(nIndex, 0));
	SetDlgItemText(IDC_EDIT_JUDUL, pList->GetItemText(nIndex, 1));
	SetDlgItemText(IDC_EDIT_GENRE, pList->GetItemText(nIndex, 2));
	SetDlgItemText(IDC_EDIT_TAHUN, pList->GetItemText(nIndex, 3));
	SetDlgItemText(IDC_EDIT_RATING, pList->GetItemText(nIndex, 4));
	SetDlgItemText(IDC_EDIT_SUTRADARA, pList->GetItemText(nIndex, 5));

	*pResult = 0;
}

void CCineListDlg::OnBnClickedBtnPrint()
{
	if (m_movieList.head == nullptr) {
		AfxMessageBox(_T("Gagal: Database memori kosong. Tidak ada data untuk diekspor."));
		return;
	}

	CStdioFile file;
	CFileException ex;

	CString filePath = _T("Laporan_Data_Film.csv");

	if (file.Open(filePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText, &ex)) {

		file.WriteString(_T("Kode,Judul,Genre,Tahun,Rating,Sutradara\n"));

		MovieNode* temp = m_movieList.head;
		while (temp != nullptr) {
			CString barisData;

			barisData.Format(_T("%s,%s,%s,%d,%.1f,%s\n"),
				temp->data.kode,
				temp->data.judul,
				temp->data.genre,
				temp->data.tahun,
				temp->data.rating,
				temp->data.sutradara);

			file.WriteString(barisData);
			temp = temp->next;
		}

		file.Close();

		AfxMessageBox(_T("Sukses: Laporan berhasil di-generate ke file Laporan_Data_Film.csv"));
	}
	else {
		TCHAR szError[1024];
		ex.GetErrorMessage(szError, 1024);
		CString errorMsg;
		errorMsg.Format(_T("Fatal Error I/O: Gagal membuat file laporan.\n%s"), szError);
		AfxMessageBox(errorMsg);
	}
}