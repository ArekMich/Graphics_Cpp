#include "wx_pch.h"
#include "lab03Main.h"
#include <wx/msgdlg.h>

#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
#include <wx/dcbuffer.h>

enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(lab03Frame)
const long lab03Frame::ID_SLIDER1 = wxNewId();
const long lab03Frame::ID_CHECKBOX1 = wxNewId();
const long lab03Frame::ID_BUTTON1 = wxNewId();
const long lab03Frame::ID_TEXTCTRL2 = wxNewId();
const long lab03Frame::ID_CHOICE1 = wxNewId();
const long lab03Frame::ID_BITMAPBUTTON1 = wxNewId();
const long lab03Frame::ID_TEXTCTRL1 = wxNewId();
const long lab03Frame::ID_PANEL1 = wxNewId();
const long lab03Frame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(lab03Frame,wxFrame)
    //(*EventTable(lab03Frame)
    //*)
END_EVENT_TABLE()

lab03Frame::lab03Frame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(lab03Frame)
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer1;
    
    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer1->AddGrowableCol(1);
    FlexGridSizer1->AddGrowableRow(0);
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    Slider1 = new wxSlider(this, ID_SLIDER1, 0, 45, 129, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER1"));
    BoxSizer1->Add(Slider1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox1 = new wxCheckBox(this, ID_CHECKBOX1, _("Wlacz Latarnie"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox1->SetValue(false);
    BoxSizer1->Add(CheckBox1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button1 = new wxButton(this, ID_BUTTON1, _("Kolor Swiatla"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer1->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, _("U Arkadiusza"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    BoxSizer1->Add(TextCtrl2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Choice1 = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Choice1->SetSelection( Choice1->Append(_("BMW")) );
    Choice1->Append(_("AUDI"));
    BoxSizer1->Add(Choice1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BitmapButton1 = new wxBitmapButton(this, ID_BITMAPBUTTON1, wxBitmap(wxImage(_T("C:\\Users\\Asus\\Desktop\\lab3\\icon.png"))), wxDefaultPosition, wxSize(36,24), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
    BoxSizer1->Add(BitmapButton1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxFULL_REPAINT_ON_RESIZE, _T("ID_PANEL1"));
    Panel1->SetMinSize(wxSize(460,400));
    Panel1->SetBackgroundColour(wxColour(255,255,255));
    TextCtrl1 = new wxTextCtrl(Panel1, ID_TEXTCTRL1, _("Text"), wxPoint(24,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    TextCtrl1->Hide();
    BoxSizer2->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxFIXED_MINSIZE|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(FlexGridSizer1);
    MenuBar1 = new wxMenuBar();
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    ColourDialog1 = new wxColourDialog(this);
    FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);
    
    Connect(ID_SLIDER1,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&lab03Frame::OnSlider1CmdScroll);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&lab03Frame::OnCheckBox1Click);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&lab03Frame::OnButton1Click);
    Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&lab03Frame::OnTextCtrl2TextEnter);
    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&lab03Frame::OnChoice1Select);
    Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&lab03Frame::OnBitmapButton1Click);
    Panel1->Connect(wxEVT_PAINT,(wxObjectEventFunction)&lab03Frame::OnPanel1Paint,0,this);
    Panel1->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&lab03Frame::OnPanel1LeftDown,0,this);
    //*)
}

lab03Frame::~lab03Frame()
{

}

void lab03Frame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void lab03Frame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

wxColour myColor;
enum ModelSamochodu {BMW, AUDI} modelSamochodu;
wxBitmap myBitmap;

void lab03Frame::OnPanel1Paint(wxPaintEvent& event)
{
    wxPaintDC dc( Panel1 );
    wxSize sz = GetClientSize();
    dc.SetDeviceOrigin(sz.x/2-60,sz.y/2);

    wxString nazwaModelu = "";
    switch (modelSamochodu)
    {
    case BMW:
        nazwaModelu = "BMW.png";
        break;
    case AUDI:
        nazwaModelu = "Audi.png";
        break;
    }
    wxBitmap a = wxBitmap(nazwaModelu,wxBITMAP_TYPE_PNG);
    float yAuta = (Slider1->GetValue() + 45)/129.0;
    dc.DrawBitmap(a,wxPoint(-Slider1->GetValue(),45+yAuta*45));
    wxPoint tab[] = {wxPoint(-180,150),wxPoint(-170,-150),wxPoint(-130,-130) };//wxPoint(10,-10),wxPoint(10,10),wxPoint(-10,10),wxPoint(-10,-10)};
    wxPoint tab2[] = {wxPoint(-138,-122),wxPoint(-120,-138)};
    wxPoint tab3[] = {wxPoint(-15,-17),wxPoint(-15,96),wxPoint(24,116),wxPoint(24,64),wxPoint(-15,-17)};
    wxPoint tab4[] = {wxPoint(86,137),wxPoint(125,150),wxPoint(125,29),wxPoint(86,83),wxPoint(86,137)};
    wxPoint tab5[] = {wxPoint(3,-11),wxPoint(15,-41),wxPoint(122,-7),wxPoint(110,23)};
    wxPoint tab6[] = {wxPoint(-16,-14),wxPoint(74,-111),wxPoint(185,-60),wxPoint(124,31)};
    wxPoint tab7[] = {wxPoint(184,57),wxPoint(126,149)};

    dc.DrawLines(3,tab);
    dc.DrawLines(2,tab2);
    dc.DrawLines(5,tab3);
    dc.DrawPolygon(5,tab4);
    dc.DrawLines(4,tab5);
    dc.DrawLines(4,tab6);

    dc.DrawLine(tab3[3],tab4[3]);
    dc.DrawLine(tab3[0],tab4[2]);
    dc.DrawLines(2,tab7);

    wxPoint swiatloLatarni[] = {wxPoint(-138,-122),wxPoint(-153,44),wxPoint(-111,71),wxPoint(-61,31),wxPoint(-120,-135)};

    if (CheckBox1->IsChecked())
    {
        dc.SetPen(wxPen(myColor));
        dc.SetBrush(myColor);
        dc.DrawPolygon(5,swiatloLatarni);
    }

    dc.DrawRotatedText(TextCtrl2->GetValue(),20,-37,-20);
    myBitmap = dc.GetAsBitmap();
}

void lab03Frame::OnPanel1LeftDown(wxMouseEvent& event)
{
    wxPoint a = event.GetPosition();
    TextCtrl1->SetValue("");
    wxSize sz = GetClientSize();
    a.x = a.x - sz.x/2+60;
    a.y = a.y - sz.y/2;
    *TextCtrl1 << a.x  << " " << a.y;
}

void lab03Frame::OnSlider1CmdScroll(wxScrollEvent& event)
{
    TextCtrl1->SetValue("");
    *TextCtrl1 << Slider1->GetValue();
    Panel1->Refresh();

}

void lab03Frame::OnButton1Click(wxCommandEvent& event)
{
    ColourDialog1->ShowModal();
    myColor = ColourDialog1->GetColourData().GetColour();
    Panel1->Refresh();
}

void lab03Frame::OnBitmapButton1Click(wxCommandEvent& event)
{


wxFileDialog
        saveFileDialog(this, _("Save file"), "", "",
                       "BMP (*.bmp)|*.bmp", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;
    wxWindowDC cdc(Panel1);

    int w = cdc.GetSize().x;
    int h = cdc.GetSize().y;

    wxBitmap bitmap(w, h, 24);
    wxMemoryDC mdc(bitmap);
    mdc.Blit(0,0, w,h, &cdc, 0,0);
    mdc.SelectObject(wxNullBitmap);
    bitmap.SaveFile(saveFileDialog.GetPath(), wxBITMAP_TYPE_BMP);

}

void lab03Frame::OnCheckBox1Click(wxCommandEvent& event)
{
    Panel1->Refresh();
}

void lab03Frame::OnTextCtrl2TextEnter(wxCommandEvent& event)
{
    Panel1->Refresh();
}

void lab03Frame::OnChoice1Select(wxCommandEvent& event)
{
    if (Choice1->GetSelection()==0)
        modelSamochodu = BMW;
    else
        modelSamochodu = AUDI;
    Panel1->Refresh();

}
