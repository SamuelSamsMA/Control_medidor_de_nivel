
// LevelMeter.cpp: define los comportamientos de las clases para la aplicación.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "LevelMeter.h"
#include "MainFrm.h"

#include "LevelCtrl.h"

#include "LevelMeterDoc.h"
#include "LevelMeterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLevelMeterApp

BEGIN_MESSAGE_MAP(CLevelMeterApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CLevelMeterApp::OnAppAbout)
	// Comandos de documento estándar basados en archivo
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// Comando de configuración de impresión estándar
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// Construcción de CLevelMeterApp

CLevelMeterApp::CLevelMeterApp() noexcept
{
	// TODO: reemplace la cadena de identificador de aplicación siguiente por una cadena de identificador único; el formato
	// recomendado para la cadena es NombreCompañía.NombreProducto.Subproducto.InformaciónDeVersión
	SetAppID(_T("LevelMeter.AppID.NoVersion"));

	// TODO: agregar aquí el código de construcción,
	// Colocar toda la inicialización importante en InitInstance
}

// Único objeto CLevelMeterApp

CLevelMeterApp theApp;


// Inicialización de CLevelMeterApp

BOOL CLevelMeterApp::InitInstance()
{
	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// Se necesita AfxInitRichEdit2() para usar el control RichEdit
	// AfxInitRichEdit2();

	// Inicialización estándar
	// Si no utiliza estas funcionalidades y desea reducir el tamaño
	// del archivo ejecutable final, debe quitar
	// las rutinas de inicialización específicas que no necesite
	// Cambie la clave del Registro en la que se almacena la configuración
	// TODO: debe modificar esta cadena para que contenga información correcta
	// como el nombre de su compañía u organización
	SetRegistryKey(_T("Aplicaciones generadas con el Asistente para aplicaciones local"));
	LoadStdProfileSettings(4);  // Cargar opciones de archivo INI estándar (incluidas las de la lista MRU)


	// Registrar las plantillas de documento de la aplicación.  Las plantillas de documento
	//  sirven como conexión entre documentos, ventanas de marco y vistas
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CLevelMeterDoc),
		RUNTIME_CLASS(CMainFrame),       // Ventana de marco SDI principal
		RUNTIME_CLASS(CLevelMeterView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Analizar línea de comandos para comandos Shell estándar, DDE, Archivo Abrir
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Enviar comandos especificados en la línea de comandos.  Devolverá FALSE si
	// la aplicación se inició con los modificadores /RegServer, /Register, /Unregserver o /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Se ha inicializado la única ventana; mostrarla y actualizarla
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

// Controladores de mensajes de CLevelMeterApp


// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Comando de la aplicación para ejecutar el cuadro de diálogo
void CLevelMeterApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Controladores de mensajes de CLevelMeterApp



