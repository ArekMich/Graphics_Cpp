#ifndef LAB03MAIN_H
#define LAB03MAIN_H

//(*Headers(lab03Frame)
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/colordlg.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/filedlg.h>
#include <wx/choice.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class lab03Frame: public wxFrame
{
    public:

        lab03Frame(wxWindow* parent,wxWindowID id = -1);
        virtual ~lab03Frame();

    private:

        //(*Handlers(lab03Frame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnPanel2Paint(wxPaintEvent& event);
        void OnPanel1Paint(wxPaintEvent& event);
        void OnPanel1LeftDown(wxMouseEvent& event);
        void OnSlider1CmdScroll(wxScrollEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnBitmapButton1Click(wxCommandEvent& event);
        void OnCheckBox1Click(wxCommandEvent& event);
        void OnTextCtrl2TextEnter(wxCommandEvent& event);
        void OnChoice1Select(wxCommandEvent& event);
        //*)

        //(*Identifiers(lab03Frame)
        static const long ID_SLIDER1;
        static const long ID_CHECKBOX1;
        static const long ID_BUTTON1;
        static const long ID_TEXTCTRL2;
        static const long ID_CHOICE1;
        static const long ID_BITMAPBUTTON1;
        static const long ID_TEXTCTRL1;
        static const long ID_PANEL1;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(lab03Frame)
        wxSlider* Slider1;
        wxButton* Button1;
        wxPanel* Panel1;
        wxColourDialog* ColourDialog1;
        wxFileDialog* FileDialog1;
        wxBitmapButton* BitmapButton1;
        wxCheckBox* CheckBox1;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TextCtrl2;
        wxTextCtrl* TextCtrl1;
        wxChoice* Choice1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // LAB03MAIN_H
