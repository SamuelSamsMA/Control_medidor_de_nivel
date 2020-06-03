
// LevelMeterView.cpp: implementación de la clase CLevelMeterView
//

#include "pch.h"
#include "framework.h"
// Se pueden definir SHARED_HANDLERS en un proyecto ATL implementando controladores de vista previa, miniatura
// y filtro de búsqueda, y permiten compartir código de documentos con ese proyecto.
#ifndef SHARED_HANDLERS
#include "LevelMeter.h"
#endif

#include "LevelMeterDoc.h"
#include "LevelMeterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLevelMeterView

IMPLEMENT_DYNCREATE(CLevelMeterView, CFormView)

BEGIN_MESSAGE_MAP(CLevelMeterView, CFormView)
	// Comandos de impresión estándar
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

// Construcción o destrucción de CLevelMeterView

CLevelMeterView::CLevelMeterView() noexcept
	: CFormView(IDD_LEVELMETER_FORM)
{
	// TODO: agregar aquí el código de construcción

}

CLevelMeterView::~CLevelMeterView()
{
}

void CLevelMeterView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CLevelMeterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: modificar aquí la clase Window o los estilos cambiando
	//  CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CLevelMeterView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// Impresión de CLevelMeterView

BOOL CLevelMeterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Preparación predeterminada
	return DoPreparePrinting(pInfo);
}

void CLevelMeterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: agregar inicialización adicional antes de imprimir
}

void CLevelMeterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: agregar limpieza después de imprimir
}

void CLevelMeterView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: agregar aquí el código de impresión personalizado
}


// Diagnósticos de CLevelMeterView

#ifdef _DEBUG
void CLevelMeterView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLevelMeterView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CLevelMeterDoc* CLevelMeterView::GetDocument() const // La versión de no depuración está alineada
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLevelMeterDoc)));
	return (CLevelMeterDoc*)m_pDocument;
}
#endif //_DEBUG


// Controladores de mensajes de CLevelMeterView
