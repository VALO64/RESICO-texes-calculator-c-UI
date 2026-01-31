/*
    Commands to build the project: 
    cmake .
    make
    open Test.app
    if I want to see the messages on the terminal use this command:
    ./Test.app/Contents/MacOS/Test 
    Improvement: put my current job in a function  (checked)
    Create the info files (checked)
    Ideas for the future:
    Create my own .h files to implement them in the code and clean it 
    Create the pdf reader that automatically adds the information (checked)
    Give a .txt file that saves the information that I proportionate in the UI
    ****I want to add a new button to calculate more than one factura 
    Add new button: Agregar nueva factura (Checked)
    Expand the window size and add the new layer (checked)

    Add to the markdown how I solve the path and pdf 
*/
 
// For compilers that support precompilation, includes "wx/wx.h".
#include<iostream>
#include <wx/wxprec.h> //UI to work with the user interface
#include <wx/splitter.h>
#include<fstream>
#include<cstdlib>
#include <nlohmann/json.hpp>
#include<string>
#define WIDTH 250
#define HEIGHT 300
using namespace std;
using json = nlohmann::json;
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
    void OnFileOpen(wxCommandEvent& event);
    void OnAddNewFacturaClick(wxCommandEvent& event);
    void OnSecondButtonClick(wxCommandEvent& event);
    void frame_1(); //Function to allocate the text boxes and button
    void frame_2(); //This will allocate new calculation displays when the button is clicked on the main frame
    wxTextCtrl * ivaCausadoTextBox;
    wxTextCtrl * ivaRetenidoTextBox;
    wxTextCtrl * resultTextBox;
    wxButton * calculateButton;
    wxButton * addNewFacturaButton;


    wxTextCtrl * ivaCausadoTextBox2;
    wxTextCtrl * ivaRetenidoTextBox2;
    wxTextCtrl * resultTextBox2;
    wxButton * calculateButton2;    
    void top_menu_bar();
    wxMenuBar *top_bar;
    wxMenu* helpMenu;
    wxMenu* fileMenu;

    wxSplitterWindow * sizer_split = new wxSplitterWindow(this, wxID_ANY,wxDefaultPosition, wxDefaultSize,wxSP_LIVE_UPDATE); //,wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE
    wxPanel* panel_inputs = new wxPanel (sizer_split); //That's the panel that will allocate the labels
    wxPanel *secondary_panel_inputs = new wxPanel (sizer_split); //That's the panel that will allocate the labels


    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer2 = new wxBoxSizer(wxVERTICAL);

    //int *ptr_w;

    //ptr_w = &WIDTH;
};


// --------Custom IDs--------- 
enum
{
    ID_Hello = 1,
    ID_About = 1,
    ID_File = 1
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
MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "RESICO Calculator", wxPoint(), wxSize(WIDTH,HEIGHT)){ //Creates the main frame / window with the title
    std::cout << "does the size incressed? " << WIDTH << std::endl;
    top_menu_bar();
    frame_1();

}
//Function to close the window 
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
// Top menu bar function 
void MyFrame::top_menu_bar(){
    // Main menu bar 
    top_bar = new wxMenuBar; // This is the principal menu bar 
    // Items in the menu bar 
    //wxMenu *top_menu = new wxMenu; //This are the sub menu of the principal menu bar 
  
    helpMenu = new wxMenu; // This is the menu of the sub menu 
    fileMenu = new wxMenu; // This is the file menu 
    top_bar ->Append(helpMenu, _T("&Help")); //I link the helpMenu that I just created with the principal menu bar
    helpMenu ->Append(ID_About, _T("&About\tF1"), ""); //The second argument is the title that will show in the menu third argument will show a text in the status bar 
    top_bar ->Append(fileMenu, _T("&File"));
    fileMenu ->Append(ID_File, _T("&Open file\tF2"), " ");



    SetMenuBar(top_bar);

    Bind(wxEVT_MENU, &MyFrame::OnAboutClick,this);
    Bind(wxEVT_MENU, &MyFrame::OnFileOpen, this);


    CreateStatusBar();
    SetStatusText("Created by Oscar Valles");
}
// ------------------- Frame with all of the text boxes and button ----------------------
void MyFrame::frame_1(){
        ////--------------------Sizer of the layout ---------------------------
    
    //wxPanel* panel_inputs = new wxPanel (sizer);
    
    
    
    //--------------------Labels ---------------------------
    wxStaticText* ivaCausadoLabel = new wxStaticText (panel_inputs, wxID_ANY, "Impuestos trasladados"); //This is the label that I'll create
    wxStaticText* ivaRetenidoLaber = new wxStaticText (panel_inputs, wxID_ANY, "Impuestos retenidos"); 

    //--------------------Text Boxes ---------------------------
    ivaCausadoTextBox = new wxTextCtrl (panel_inputs, wxID_ANY,"",wxPoint(10,10),wxSize(200,25));
    ivaRetenidoTextBox = new wxTextCtrl (panel_inputs, wxID_ANY,"",wxPoint(10,10),wxSize(200,25));
    resultTextBox = new wxTextCtrl(panel_inputs,wxID_PRINT,"El total a pagar: ",wxPoint(10,10),wxSize(200,25),wxTE_READONLY);

    //--------------------Buttons ---------------------------
    calculateButton = new wxButton(panel_inputs, wxID_ANY, "Calcular", wxPoint(10,10), wxSize(200, 25));
    addNewFacturaButton = new wxButton(panel_inputs, wxID_ANY, "Agregar cálculo de factura", wxPoint(10,10), wxSize(200, 50));


    sizer ->Add(ivaCausadoLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    sizer ->Add(ivaCausadoTextBox, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 2);
    sizer ->Add(ivaRetenidoLaber, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    sizer ->Add(ivaRetenidoTextBox, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 2);
    sizer ->Add(calculateButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    sizer ->Add(resultTextBox, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 2);
    sizer ->Add(addNewFacturaButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 1);

    // //--------------------Linkers ---------------------------
    calculateButton ->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick,this); //I linked the calculate button with the function of the button down below
    addNewFacturaButton ->Bind(wxEVT_BUTTON, &MyFrame::OnAddNewFacturaClick, this);
    panel_inputs ->SetSizerAndFit(sizer);
    //sizer_split -> SplitVertically(panel_inputs , frame_2(new wxPanel (this, wxID_ANY)));
    this -> Center();
    //this -> Fit();
    

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
    resultTextBox->SetValue(wxString::Format("IVA a pagar: %.2f", total_a_pagar));
}

void MyFrame::OnAboutClick(wxCommandEvent& event){
    wxMessageBox(_T("https://github.com/VALO64/RESICO-texes-calculator-c-UI"),
                 _T("Information and newer versions on"), wxOK | wxICON_INFORMATION, this); //First argument will appear below the title, the second argument is the title
}

void MyFrame::OnFileOpen(wxCommandEvent& event){

    wxFileDialog openFileDialog(this, _("Open File"), "", "",
                               "Text files (*.txt)|*.txt|All files (*.*)|*.*",
                               wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_OK)
    {
        wxString path = openFileDialog.GetPath();
        // Use the selected path in your application (e.g., load the file content)
        wxLogStatus(this, _("Selected file: %s"), path);
        cout << "The path is:  " << path << endl;
        // Create the json to sent it to the script
        json pathgot;
        pathgot["pathgotten"] = path;

        ofstream outputFileStream("pathgotten.json");
        if (outputFileStream.is_open()){
            outputFileStream << setw(4) << pathgot << endl;
            outputFileStream.close();
            cout << "The data was written correctly! " << endl;    
        } else {
            cout << "The data couldn't be written correctly!" << endl;
        }
        
        // Calling the python script

        cout << "Calling Python script" << endl;

        int result = system("python3 /Users/oscar/projects/C_mas/C_UIs/Taxes_calculator_c/wxWidgets_basic_template/script.py");
        if (result == 0) {
            cout << "Python script executed successfully." << endl;
        } else {
            cout << "Error executing Python script." << endl;
        } 
        ifstream i("data.json");
        if (!i.is_open()){
        cerr << "Error opening json file";
        }
        json data;
        try {
            i >> data;
        } catch (json::parse_error& e){
            std::cerr << "Json parse error " << e.what() << std::endl;
        }
        float Impuestos_trasladados = data["Impuestos_trasladados"].get<float>();
        float Impuestos_retenidos = data["Impuestos_retenidos"].get<float>();

        cout <<  Impuestos_trasladados << endl;
        cout <<  Impuestos_retenidos << endl;

        float total = Impuestos_trasladados - Impuestos_retenidos;
        std::cout << "Total to pay: " << total << std::endl;
        resultTextBox->SetValue(wxString::Format("IVA a pagar: %.2f", total));    

    }
}

void MyFrame::OnAddNewFacturaClick(wxCommandEvent&event){
    std::cout << "does the size incressed? " << WIDTH << std::endl;
    SetClientSize(wxSize(500, HEIGHT));
    frame_2();
}
void MyFrame::frame_2(){
    
    //wxBoxSizer* secondary_sizer = new wxBoxSizer(wxVERTICAL);

    
    //--------------------Labels ---------------------------
    wxStaticText* ivaCausadoLabel = new wxStaticText (secondary_panel_inputs, wxID_ANY, "Impuestos trasladados "); //This is the label that I'll create
    wxStaticText* ivaRetenidoLabel = new wxStaticText (secondary_panel_inputs, wxID_ANY, "Impuestos retenidos "); 

    //--------------------Text Boxes ---------------------------
    ivaCausadoTextBox2 = new wxTextCtrl (secondary_panel_inputs, wxID_ANY,"",wxPoint(10,10),wxSize(200,25));
    ivaRetenidoTextBox2 = new wxTextCtrl (secondary_panel_inputs, wxID_ANY,"",wxPoint(10,10),wxSize(200,25));
    resultTextBox2 = new wxTextCtrl(secondary_panel_inputs,wxID_PRINT,"El total a pagar: ",wxPoint(10,10),wxSize(200,25),wxTE_READONLY);

    //--------------------Buttons ---------------------------
    calculateButton2 = new wxButton(secondary_panel_inputs, wxID_ANY, "Calcular 2", wxPoint(10,10), wxSize(200, 25));

    sizer2 ->Add(ivaCausadoLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    sizer2 ->Add(ivaCausadoTextBox2, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 2);
    sizer2 ->Add(ivaRetenidoLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    sizer2 ->Add(ivaRetenidoTextBox2, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 2);
    sizer2 ->Add(calculateButton2, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    sizer2 ->Add(resultTextBox2, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 2);

    calculateButton2 ->Bind(wxEVT_BUTTON, &MyFrame::OnSecondButtonClick,this);

    panel_inputs ->SetSizerAndFit(sizer2);
    sizer_split -> SplitVertically(panel_inputs , secondary_panel_inputs);
    //this -> Center();
    
}
void MyFrame::OnSecondButtonClick(wxCommandEvent&event){
    double total_a_pagar2 = 0.0;
    double ivaCausado2 = 0.0;
    double ivaRetenido2 = 0.0;

    //- I got the values form the text boxes to do mathematical operations
    ivaCausadoTextBox2 ->GetValue().ToDouble(&ivaCausado2);
    ivaRetenidoTextBox2 ->GetValue().ToDouble(&ivaRetenido2);
    //- I substract the values
    total_a_pagar2 = ivaCausado2 - ivaRetenido2;
    //- I changed the substract value to string to printed on the text box
    std::string total_a_pagar_sring = std::to_string(total_a_pagar2);
    //- I print the value on the text box
    resultTextBox2->SetValue(wxString::Format("IVA a pagar: %.2f", total_a_pagar2));
}

