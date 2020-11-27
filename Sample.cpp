#include <wx/wx.h>
#include <wx/version.h>
#include "wxVTKRenderWindowInteractor.h"
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include "mondrian.xpm"


class MyApp;
class MyFrame;


class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};


class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    ~MyFrame();
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

protected:
    void ConstructVTK();
    void ConfigureVTK();
    void DestroyVTK();

private:
    wxVTKRenderWindowInteractor *m_pVTKWindow;
    vtkSmartPointer<vtkRenderer> pRenderer;
    vtkSmartPointer<vtkRenderWindow> pRenderWindow;
    vtkSmartPointer<vtkPolyDataMapper> pConeMapper;
    vtkSmartPointer<vtkActor> pConeActor;
    vtkSmartPointer<vtkConeSource> pConeSource;
private:
    DECLARE_EVENT_TABLE()
};

enum
{
    Minimal_Quit = 1,
    Minimal_About
};

#define MY_FRAME      101
#define MY_VTK_WINDOW 102

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame(_T("wxWidgets-VTK App"), wxPoint(50, 50), wxSize(450, 450));
    frame->Show(TRUE);
    return TRUE;
}


MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{

    SetIcon(wxICON(mondrian));
    wxMenu *menuFile = new wxMenu(_T(""), wxMENU_TEAROFF);
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, _T("&About...\tCtrl-A"), _T("Show about dialog"));
    menuFile->Append(Minimal_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, _T("&File"));
    menuBar->Append(helpMenu, _T("&Help"));
    SetMenuBar(menuBar);
    CreateStatusBar(2);
    wxString mystring;
    mystring << "WxWidgets Version: ";
    mystring << wxMAJOR_VERSION;
    mystring << ".";
    mystring << wxMINOR_VERSION;
    mystring << ".";
    mystring << wxRELEASE_NUMBER;
    mystring << ".";
    mystring << wxSUBRELEASE_NUMBER;
    SetStatusText(mystring,1);
    m_pVTKWindow = new wxVTKRenderWindowInteractor(this, MY_VTK_WINDOW);
    m_pVTKWindow->UseCaptureMouseOn();
    ConstructVTK();
    ConfigureVTK();
}

MyFrame::~MyFrame()
{
    if(m_pVTKWindow) m_pVTKWindow->Delete();
    DestroyVTK();
}

void MyFrame::ConstructVTK()
{
    pRenderer     = vtkRenderer::New();
    pConeMapper   = vtkPolyDataMapper::New();
    pConeActor    = vtkActor::New();
    pConeSource   = vtkConeSource::New();

}

void MyFrame::ConfigureVTK()
{
    // connect the render window and wxVTK window
    pRenderWindow = m_pVTKWindow->GetRenderWindow();
    // connect renderer and render window and configure render window
    pRenderWindow->AddRenderer(pRenderer);
    // initialize cone
    pConeSource->SetResolution(200);
    // connect pipeline
    pConeMapper->SetInputConnection(pConeSource->GetOutputPort());
    pConeActor->SetMapper(pConeMapper);
    pRenderer->AddActor(pConeActor);
    // configure renderer
    pRenderer->SetBackground(0.5, 0.5, 0.5);
    pRenderer->GradientBackgroundOn();
    pRenderer->SetBackground(1, 1, 1);
    pRenderer->SetBackground2(0, 0, 1);
    pRenderer->GetActiveCamera()->Elevation(30.0);
    pRenderer->GetActiveCamera()->Azimuth(30.0);
    pRenderer->GetActiveCamera()->Zoom(1.0);
    pRenderer->GetActiveCamera()->SetClippingRange(1,1000);
}

void MyFrame::DestroyVTK()
{
    if (pRenderer != 0)
        pRenderer->Delete();
    if (pConeMapper != 0)
        pConeMapper->Delete();
    if (pConeActor != 0)
        pConeActor->Delete();
    if (pConeSource != 0)
        pConeSource->Delete();
}


void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( _T("This is the about dialog of wx-vtk sample.\n"));
    wxMessageBox(msg, _T("About wx-vtk"), wxOK | wxICON_INFORMATION, this);
}
