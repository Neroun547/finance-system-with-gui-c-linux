/***************************************************************
 * Name:      finance_system_guiApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Gosha ()
 * Created:   2022-06-11
 * Copyright: Gosha ()
 * License:
 **************************************************************/

#include "finance_system_guiApp.h"

//(*AppHeaders
#include "finance_system_guiMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(finance_system_guiApp);

bool finance_system_guiApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	finance_system_guiFrame* Frame = new finance_system_guiFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
        