
// LevelMeterView.h: interfaz de la clase CLevelMeterView
//

#pragma once


class CLevelMeterView : public CFormView
{
protected: // Crear sólo a partir de serialización
	CLevelMeterView() noexcept;
	DECLARE_DYNCREATE(CLevelMeterView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_LEVELMETER_FORM };
#endif

// Atributos
public:
	CLevelMeterDoc* GetDocument() const;

// Operaciones
public:

// Reemplazos
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV
	virtual void OnInitialUpdate(); // Se llama la primera vez después de la construcción
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// Implementación
public:
	virtual ~CLevelMeterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Funciones de asignación de mensajes generadas
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Versión de depuración en LevelMeterView.cpp
inline CLevelMeterDoc* CLevelMeterView::GetDocument() const
   { return reinterpret_cast<CLevelMeterDoc*>(m_pDocument); }
#endif

