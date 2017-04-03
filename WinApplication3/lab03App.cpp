#include "wx_pch.h"
#include "lab03App.h"

#include "lab03Main.h"
#include <wx/image.h>


IMPLEMENT_APP(lab03App);

bool lab03App::OnInit()
{
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	lab03Frame* Frame = new lab03Frame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }

    return wxsOK;
}
