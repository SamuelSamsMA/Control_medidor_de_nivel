
// LevelMeter.h: archivo de encabezado principal para la aplicación LevelMeter
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'pch.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"       // Símbolos principales


// CLevelMeterApp:
// Consulte LevelMeter.cpp para obtener información sobre la implementación de esta clase
//

class CLevelMeterApp : public CWinApp
{
public:
	CLevelMeterApp() noexcept;


// Reemplazos
public:
	virtual BOOL InitInstance();

// Implementación
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLevelMeterApp theApp;
