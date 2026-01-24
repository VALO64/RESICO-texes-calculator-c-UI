/*
    Commands to build the project: 
    cmake .
    make
    open Test.app
    Improvement: put my current job in a function  (checked)
    Create the info files (checked)
*/
 
// For compilers that support precompilation, includes "wx/wx.h".
#include<iostream>
#include <wx/wxprec.h> //UI to work with the user interface
using namespace std;
 
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
 
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
 
class MyFrame : public wxFrame
{
public:
    MyFrame();
 
private:
    //----------Clicked events -------------------
    void OnExit(wxCommandEvent& event);
    void OnButtonClick(wxCommandEvent& event);
    void OnAboutClick(wxCommandEvent& event);

    void frame_1(); //Function to allocate the text boxes and button
    wxTextCtrl * ivaCausadoTextBox;
    wxTextCtrl * ivaRetenidoTextBox;
    wxTextCtrl * resultTextBox;
    wxButton * calculateButton;
    void top_menu_bar();
    wxMenuBar *top_bar;
    wxMenu* helpMenu;
};


// --------Custom IDs--------- 
enum
{
    ID_Hello = 1,
    ID_About
};
 
wxIMPLEMENT_APP(MyApp);

//Function to initialize the frame
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}
// ----------------------Principal frame --------------------
MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "RESICO Calculator", wxPoint(), wxSize(250,300)){ //Creates the main frame / window with the title
    top_menu_bar();
    frame_1();

}
//Function to close the window 
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
void MyFrame::top_menu_bar(){
    // Main menu bar 
    top_bar = new wxMenuBar; // This is the principal menu bar 
    // Items in the menu bar 
    //wxMenu *top_menu = new wxMenu; //This are the sub menu of the principal menu bar 
  
    helpMenu = new wxMenu; // This is the menu of the sub menu 
    top_bar ->Append(helpMenu, _T("&Help")); //I link the helpMenu that I just created with the principal menu bar
    helpMenu ->Append(ID_About, _T("&About\tF1"), ""); //The second argument is the title that will show in the menu third argument will show a text in the status bar 
    
    SetMenuBar(top_bar);

    Bind(wxEVT_MENU, &MyFrame::OnAboutClick,this);


    CreateStatusBar();
    SetStatusText("Created by Oscar Valles");
}
// ------------------- Frame with all of the text boxes and button ----------------------
void MyFrame::frame_1(){
        ////--------------------Sizer of the layout ---------------------------
    wxPanel* panel_inputs = new wxPanel (this, wxID_ANY); //That's the panel that will allocate the labels
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    //--------------------Labels ---------------------------
    wxStaticText* ivaCausadoLabel = new wxStaticText (panel_inputs, wxID_ANY, "Impuestos trasladados"); //This is the label that I'll create
    wxStaticText* ivaRetenidoLaber = new wxStaticText (panel_inputs, wxID_ANY, "Impuestos retenidos"); 

    //--------------------Text Boxes ---------------------------
    ivaCausadoTextBox = new wxTextCtrl (panel_inputs, wxID_ANY,"",wxPoint(10,10),wxSize(200,25));
    ivaRetenidoTextBox = new wxTextCtrl (panel_inputs, wxID_ANY,"",wxPoint(10,10),wxSize(200,25));
    resultTextBox = new wxTextCtrl(panel_inputs,wxID_PRINT,"El total a pagar: ",wxPoint(10,10),wxSize(200,25),wxTE_READONLY);

    //--------------------Buttons ---------------------------
    calculateButton = new wxButton(panel_inputs, wxID_ANY, "Calculate", wxPoint(10,10), wxSize(200, 25));
    sizer ->Add(ivaCausadoLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    sizer ->Add(ivaCausadoTextBox, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 2);
    sizer ->Add(ivaRetenidoLaber, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    sizer ->Add(ivaRetenidoTextBox, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 2);
    sizer ->Add(calculateButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    sizer ->Add(resultTextBox, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 2);

    // //--------------------Linkers ---------------------------
    calculateButton ->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick,this); //I linked the calculate button with the function of the button down below
    panel_inputs ->SetSizerAndFit(sizer);
    this -> Center();

}
//------------Calculate button clicked function -------------------
void MyFrame::OnButtonClick(wxCommandEvent& event){

    double total_a_pagar = 0.0;
    double ivaCausado = 0.0;
    double ivaRetenido = 0.0;

    //- I got the values form the text boxes to do mathematical operations
    ivaCausadoTextBox->GetValue().ToDouble(&ivaCausado);
    ivaRetenidoTextBox ->GetValue().ToDouble(&ivaRetenido);
    //- I substract the values
    total_a_pagar = ivaCausado - ivaRetenido;
    //- I changed the substract value to string to printed on the text box
    std::string total_a_pagar_sring = std::to_string(total_a_pagar);
    //- I print the value on the text box
    resultTextBox->SetValue(wxString::Format("El total a pagar: %.2f", total_a_pagar));
}

void MyFrame::OnAboutClick(wxCommandEvent& event){
    wxMessageBox(_T("https://github.com/VALO64/RESICO-texes-calculator-c-UI"),
                 _T("Information and newer versions on"), wxOK | wxICON_INFORMATION, this); //First argument will appear below the title, the second argument is the title
}


