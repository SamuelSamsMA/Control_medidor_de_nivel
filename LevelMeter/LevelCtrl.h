#pragma once


class CLevelMeterOptDlg;


// CLevelCtrl

class CLevelCtrl : public CStatic
{
	DECLARE_DYNAMIC(CLevelCtrl)

public:
	CLevelCtrl();
	virtual ~CLevelCtrl();

// Attributes
protected:
	double m_vMax, m_vMin, m_value;
	int m_nDivisions;
	int m_nDecimals;
	CString m_strTitle, m_strUnit;
	CFont m_font;

	CRect m_rcCtrl;
	CRect m_rcTank;
	CRect m_rcValue;
	CRect m_rcTitle;
	CRect m_rcOptions;

	COLORREF m_colorTxtValue;
	COLORREF m_colorIndicator;

	CDC m_dcBackground;
	CBitmap m_bitmapBackground, * m_pBitmapOldBackground;

// Operations
public:
	BOOL setRange(double vMin, double vMax);
	void setValue(double val);
	BOOL setDivisions(int nDiv);
	BOOL setDecimals(int nDec);
	void setTitle(CString title);
	void setUnit(CString unit);

	double getValue() { return m_value; }
	CString getTitle() { return m_strTitle; }

// Implementation
protected:
	void DrawCtrlBackground(CDC* pDC, CRect& rect);
	void reconstructControl();
	void updateValue(CDC* pDC);
	void updateMeter(CDC* pDC);

public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

protected:
	DECLARE_MESSAGE_MAP()
};




// CLevelMeterOptDlg

class CLevelMeterOptDlg : public CDialog
{
	DECLARE_DYNAMIC(CLevelMeterOptDlg)

public:
	CLevelMeterOptDlg(CWnd* pParent = nullptr);   // Constructor estándar
	virtual ~CLevelMeterOptDlg();

public:
	CString m_strTitle;
	CString m_strUnit;
	double m_nMin;
	double m_nMax;
	int m_nDivisions;
	COLORREF m_colorIndicator;
protected:
	CMFCColorButton c_colorBtn;
	CEdit c_editMin;

	// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LEVEL_OPT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV
	virtual BOOL OnInitDialog();

	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};

