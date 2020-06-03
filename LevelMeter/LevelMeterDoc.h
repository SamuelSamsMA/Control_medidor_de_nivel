
// LevelMeterDoc.h: interfaz de la clase CLevelMeterDoc
//


#pragma once


class CLevelMeterDoc : public CDocument
{
protected: // Crear sólo a partir de serialización
	CLevelMeterDoc() noexcept;
	DECLARE_DYNCREATE(CLevelMeterDoc)

// Atributos
public:

// Operaciones
public:

// Reemplazos
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementación
public:
	virtual ~CLevelMeterDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Funciones de asignación de mensajes generadas
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Función del asistente que establece contenido de búsqueda para un controlador de búsqueda
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
