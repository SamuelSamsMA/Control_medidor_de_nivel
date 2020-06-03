// LevelCtrl.cpp: archivo de implementación
//

#include "pch.h"
#include "LevelCtrl.h"
#include "SaveDC.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLevelCtrl

IMPLEMENT_DYNAMIC(CLevelCtrl, CStatic)

CLevelCtrl::CLevelCtrl()
	: m_strTitle(L"Tanque de agua #1"), m_strUnit(L"%")
{
	m_vMax = 100.0;
	m_vMin = 0.0;
	m_value = 0.0;
	m_nDivisions = 5;
	m_nDecimals = 1;

	m_font.CreatePointFont(110, L"Arial");
	m_colorTxtValue = RGB(0, 0, 0);
	m_colorIndicator = RGB(0, 128, 255);

	m_pBitmapOldBackground = nullptr;
}

CLevelCtrl::~CLevelCtrl()
{
	if (m_bitmapBackground.GetSafeHandle() && m_dcBackground.GetSafeHdc())
		m_dcBackground.SelectObject(m_pBitmapOldBackground);
}


BEGIN_MESSAGE_MAP(CLevelCtrl, CStatic)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


BOOL CLevelCtrl::setRange(double vMin, double vMax)
{
	if (vMin >= vMax)
		return FALSE;
	else
	{
		m_vMax = vMax;
		m_vMin = vMin;
		reconstructControl();
		return TRUE;
	}
}

void CLevelCtrl::setValue(double val)
{
	m_value = val;

	if (m_value < m_vMin || m_value > m_vMax)
		m_colorTxtValue = RGB(255, 0, 0);
	else
		m_colorTxtValue = RGB(0, 0, 0);

	Invalidate();
}

BOOL CLevelCtrl::setDivisions(int nDiv)
{
	if (nDiv < 0)
		return FALSE;
	else
	{
		m_nDivisions = nDiv;
		reconstructControl();
		return TRUE;
	}
}

BOOL CLevelCtrl::setDecimals(int nDec)
{
	if (nDec < 0)
		return FALSE;
	else
	{
		m_nDecimals = nDec;
		reconstructControl();
		return TRUE;
	}
}

void CLevelCtrl::setTitle(CString title)
{
	m_strTitle = title;
	reconstructControl();
}

void CLevelCtrl::setUnit(CString units)
{
	m_strUnit = units;
	Invalidate();
}



void CLevelCtrl::DrawCtrlBackground(CDC* pDC, CRect& rect)
{
	CBrush brushFill;
	CPen penDraw;

	{ /* save context */
		CSaveDC sdc(pDC);

		// fill the background with the button color
		brushFill.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
		penDraw.CreateStockObject(NULL_PEN);
		pDC->SelectObject(&penDraw);
		pDC->SelectObject(&brushFill);
			// Inflate rectangle only to include the bottom and right coordinates
		rect.InflateRect(0, 0, 1, 1);
		pDC->Rectangle(rect);
		rect.DeflateRect(0, 0, 1, 1);

		// draw the title bar and its options buttom
		pDC->SelectObject(&m_font);
		TEXTMETRIC txtMetric;
		pDC->GetTextMetrics(&txtMetric);
		m_rcTitle.SetRect(0, 0, rect.right, txtMetric.tmHeight + 6);

		brushFill.DeleteObject();
		brushFill.CreateSolidBrush(RGB(153, 217, 234));
		pDC->SelectObject(&brushFill);
		pDC->Rectangle(&m_rcTitle);
		pDC->Draw3dRect(&m_rcTitle, RGB(255, 255, 255), RGB(128, 128, 192));

		penDraw.DeleteObject();
		penDraw.CreatePen(PS_SOLID, 1, RGB(128, 128, 192));
		pDC->SelectObject(penDraw);
		CPoint optionsTopLeft(m_rcTitle.Width() - m_rcTitle.Height(), 0);
		m_rcOptions.SetRect(optionsTopLeft, m_rcTitle.BottomRight());
		int spaceY = m_rcOptions.Height() / 4;
		for (int i = 1; i <= 3; i++) {
			pDC->MoveTo(m_rcOptions.left + 4, spaceY * i);
			pDC->LineTo(m_rcOptions.right - 4, spaceY * i);
		}

		// draw the title
		pDC->SetTextAlign(TA_CENTER | TA_BOTTOM);
		pDC->SetBkMode(TRANSPARENT);
		pDC->TextOutW((m_rcTitle.Width() - m_rcOptions.Width()) / 2,
			m_rcTitle.bottom - 3,
			m_strTitle);

		// get the coordinates of the tank rectangle based on the text width
		CString str;
		str.Format(L"%.*f", m_nDecimals, m_vMax);
		CSize sizeVmax = pDC->GetTextExtent(str);
		str.Format(L"%.*f", m_nDecimals, m_vMin);
		CSize sizeVmin = pDC->GetTextExtent(str);

		int bigger;
		(sizeVmax.cx >= sizeVmin.cx) ? bigger = sizeVmax.cx : bigger = sizeVmin.cx;

		constexpr int
			markWidth = 10,		// size of scale's marks
			space = 3;			// Space between text, marks and tank in pixels

		m_rcTank.left = 4 * space + bigger + markWidth;
		m_rcTank.top = m_rcTitle.bottom + 5 * space;
		m_rcTank.right = rect.right - 2 * space;
		m_rcTank.bottom = rect.bottom - 5 * space - m_rcTitle.Height();

		//  draw the tank
		pDC->SelectStockObject(BLACK_PEN);
		pDC->SelectStockObject(WHITE_BRUSH);
		pDC->Rectangle(&m_rcTank);

		// Draw the scale and labels
		pDC->SetTextAlign(TA_RIGHT | TA_TOP);

		int separationY = m_rcTank.Height() / m_nDivisions;	// Distance between each tick mark

		for (int i = 0; i <= m_nDivisions; i++)
		{
			CPoint p(m_rcTank.left - 2 * space, m_rcTank.bottom - separationY * i - 1);
			pDC->MoveTo(p);
			p.Offset(-markWidth, 0);
			pDC->LineTo(p);
			p.Offset(-space, -txtMetric.tmHeight / 2);

			double delta = (m_vMax - m_vMin) / (double)m_nDivisions;
			str.Format(L"%.*f", m_nDecimals, m_vMin + delta * (double)i);
			pDC->TextOutW(p.x, p.y, str);
		}

		// Draw the value box
		m_rcValue.SetRect(0,
			rect.bottom - m_rcTitle.Height(),
			rect.right,
			rect.bottom);

		pDC->Draw3dRect(&m_rcValue, RGB(128, 128, 128), RGB(255, 255, 255));

	} /* save context */
}

void CLevelCtrl::reconstructControl()
{
	// if we've got a stored background - remove it!
	if (m_bitmapBackground.GetSafeHandle() && m_dcBackground.GetSafeHdc())
	{
		m_dcBackground.SelectObject(m_pBitmapOldBackground);
		m_dcBackground.DeleteDC();
		m_bitmapBackground.DeleteObject();
	}

	Invalidate();
}

void CLevelCtrl::updateValue(CDC* pDC)
{
	// Draw the value and units
	CPoint cP(m_rcValue.CenterPoint());
	pDC->SetTextAlign(TA_CENTER | TA_TOP);
	CFont* pOldFont = pDC->SelectObject(&m_font);
	TEXTMETRIC txtMetric;
	pDC->GetTextMetrics(&txtMetric);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_colorTxtValue);

	CString str;
	str.Format(L"%.*f ", m_nDecimals, m_value);
	str.Append(m_strUnit);
	pDC->TextOutW(cP.x, cP.y - txtMetric.tmHeight / 2, str);

	pDC->SelectObject(pOldFont);
}

void CLevelCtrl::updateMeter(CDC* pDC)
{
	CBrush brushFill, * pOldBrush;
	brushFill.CreateSolidBrush(m_colorIndicator);
	pOldBrush = pDC->SelectObject(&brushFill);
	pDC->SelectStockObject(NULL_PEN);

	CRect rcMeter(&m_rcTank);
	rcMeter.DeflateRect(1, 1, 0, 0);

	double pend = ((double)rcMeter.top - (double)rcMeter.bottom) / (m_vMax - m_vMin);
	CPoint
		leftTop(rcMeter.left, (int)(pend * (m_value - m_vMin) + (double)rcMeter.bottom)),
		rightBottom(rcMeter.right, rcMeter.bottom);

	if (leftTop.y < rcMeter.top)
		leftTop.y = rcMeter.top;
	if (leftTop.y > rcMeter.bottom)
		leftTop.y = rcMeter.bottom;

	CRect rc(leftTop, rightBottom);

	pDC->Rectangle(&rc);

	pDC->SelectObject(pOldBrush);
}


// Controladores de mensajes de CLevelCtrl


void CLevelCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	GetClientRect(&m_rcCtrl);

	CMemDC memDC(dc, m_rcCtrl);

	// set up a memory dc for the background stuff 
	// if one isn't being used
	if ((m_dcBackground.GetSafeHdc() == NULL) || (m_bitmapBackground.m_hObject == NULL))
	{
		m_dcBackground.CreateCompatibleDC(&dc);
		m_bitmapBackground.CreateCompatibleBitmap(&dc, m_rcCtrl.Width(),
			m_rcCtrl.Height());
		m_pBitmapOldBackground = m_dcBackground.SelectObject(&m_bitmapBackground);

		// Fill this bitmap with the background.

		// Note: This requires some serious drawing and calculating, 
		// therefore it is drawn "once" to a bitmap and 
		// the bitmap is stored and blt'd when needed.
		DrawCtrlBackground(&m_dcBackground, m_rcCtrl);
	}

	// drop in the background
	memDC.GetDC().BitBlt(0, 0, m_rcCtrl.Width(), m_rcCtrl.Height(),
		&m_dcBackground, 0, 0, SRCCOPY);

	// add the meter to the background
	updateMeter(&memDC.GetDC());

	// add the value to the background
	updateValue(&memDC.GetDC());
}


void CLevelCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_rcOptions.PtInRect(point))
	{	// if the cursor is inside the options button then simulate a pressed button
		CClientDC dc(this);

		CPen pen, * oldPen;
		pen.CreatePen(PS_SOLID, 1, RGB(128, 128, 192));
		oldPen = dc.SelectObject(&pen);
		dc.SelectStockObject(NULL_BRUSH);

		CRect rect = m_rcOptions;
		rect.DeflateRect(1, 1);
		dc.Rectangle(rect);

		dc.SelectObject(oldPen);
	}

	CStatic::OnLButtonDown(nFlags, point);
}


void CLevelCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// Only redraw the picture to delete the options rectangle
	Invalidate();

	// Create and show the options dialog to customize the level control
	CLevelMeterOptDlg optDlg;

	optDlg.m_strTitle = m_strTitle;
	optDlg.m_strUnit = m_strUnit;
	optDlg.m_nMin = m_vMin;
	optDlg.m_nMax = m_vMax;
	optDlg.m_nDivisions = m_nDivisions;
	optDlg.m_colorIndicator = m_colorIndicator;

	if (optDlg.DoModal() == IDOK)
	{
		m_strTitle = optDlg.m_strTitle;
		m_strUnit = optDlg.m_strUnit;
		m_vMin = optDlg.m_nMin;
		m_vMax = optDlg.m_nMax;
		m_nDivisions = optDlg.m_nDivisions;
		m_colorIndicator = optDlg.m_colorIndicator;

		reconstructControl();
	}

	CStatic::OnLButtonUp(nFlags, point);
}




// CLevelMeterOptDlg


IMPLEMENT_DYNAMIC(CLevelMeterOptDlg, CDialog)

CLevelMeterOptDlg::CLevelMeterOptDlg(CWnd* pParent)
	: CDialog(IDD_LEVEL_OPT_DLG, pParent)
	, m_strTitle(_T(""))
	, m_strUnit(_T(""))
	, m_nMin(0)
	, m_nMax(0)
	, m_nDivisions(0)
	, m_colorIndicator(RGB(0, 0, 0))
{
}

CLevelMeterOptDlg::~CLevelMeterOptDlg()
{
}

void CLevelMeterOptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LMO_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_LMO_UNIT, m_strUnit);
	DDX_Text(pDX, IDC_EDIT_LMO_MIN, m_nMin);
	DDX_Text(pDX, IDC_EDIT_LMO_MAX, m_nMax);
	DDX_Text(pDX, IDC_EDIT_LMO_NUMDIV, m_nDivisions);
	DDV_MinMaxInt(pDX, m_nDivisions, 1, INT_MAX);
	DDX_Control(pDX, IDC_MFCCOLOR_LMO_COLOR, c_colorBtn);
	DDX_Control(pDX, IDC_EDIT_LMO_MIN, c_editMin);
}

BOOL CLevelMeterOptDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	c_colorBtn.SetColor(m_colorIndicator);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPCIÓN: las páginas de propiedades OCX deben devolver FALSE
}

BEGIN_MESSAGE_MAP(CLevelMeterOptDlg, CDialog)

END_MESSAGE_MAP()


// Controladores de mensajes de CLevelMeterOptDlg


void CLevelMeterOptDlg::OnOK()
{
	// Verify that m_nMin is less than m_nMax
	UpdateData();
	if (m_nMin >= m_nMax)
	{
		c_editMin.SetFocus();
		c_editMin.SetSel(0, -1);
		MessageBeep(MB_ICONWARNING);
		return;
	}

	m_colorIndicator = c_colorBtn.GetColor();

	CDialog::OnOK();
}
