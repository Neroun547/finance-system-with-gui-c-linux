#include "../include/finance_system_gui_category.h"
#include <string>
#include <json.hpp>
#include <cmath>
#include <wx/msgdlg.h>
#include <iostream>
#include <fstream>
#include "../finance_system_guiMain.h"

using namespace std;

#include <wx/string.h>
#include <wx/intl.h>


const long finance_system_gui_category::ID_TEXTCTRL = wxNewId();
const long finance_system_gui_category::ID_BUTTON_ADD = wxNewId();
const long finance_system_gui_category::ID_STATICTEXT = wxNewId();
const long finance_system_gui_category::ID_BUTTON_DEL = wxNewId();
const long finance_system_gui_category::ID_BUTTON_DEL_CATEGORY = wxNewId();
const long finance_system_gui_category::ID_BUTTON_PREV_FRAME = wxNewId();

const string userInSystem = getlogin();
const string pathToCategoryDataFile = "/home/" + userInSystem + "/category.json";

finance_system_gui_category::finance_system_gui_category(wxWindow* parent, wxWindowID id, string category, double sum, nlohmann::json categoryDataJson)
{
    this -> category = category;
    this -> sum = sum;
    this -> categoryDataJson = categoryDataJson;

    double roundSum = round(sum*100)/100;
    Create(parent, id, category, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(1920,1080));

    this -> TextCtrl = new wxTextCtrl(this, ID_TEXTCTRL, wxEmptyString, wxPoint(660,60), wxSize(600,60), 0, wxDefaultValidator, _T("ID_TEXTCTRL"));
    new wxButton(this, ID_BUTTON_ADD, "Add sum", wxPoint(660, 120), wxSize(290, 60), 0, wxDefaultValidator, _T("ID_BUTTON_ADD"));
    new wxButton(this, ID_BUTTON_DEL, "Del sum", wxPoint(960, 120), wxSize(290, 60), 0, wxDefaultValidator, _T("ID_BUTTON_DEL"));
    new wxButton(this, ID_BUTTON_DEL_CATEGORY, "Del category", wxPoint(70, 70), wxSize(150, 50), 0, wxDefaultValidator, _T("ID_BUTTON_DEL_CATEGORY"));
    new wxButton(this, ID_BUTTON_PREV_FRAME, "Prev", wxPoint(0, 0), wxSize(70, 50), 0, wxDefaultValidator, _T("ID_BUTTON_PREV_FRAME"));
    this -> StaticText = new wxStaticText(this, ID_STATICTEXT, "Spending: "+to_string(roundSum), wxPoint(660, 230), wxDefaultSize, 0, _T("ID_STATICTEXT"));

    Connect(ID_BUTTON_DEL_CATEGORY, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&finance_system_gui_category::OnButtonClickDelCategory);
    Connect(ID_BUTTON_ADD, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&finance_system_gui_category::OnButtonClickAdd);
    Connect(ID_BUTTON_DEL, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&finance_system_gui_category::OnButtonClickDel);
    Connect(ID_BUTTON_PREV_FRAME, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&finance_system_gui_category::OnButtonClickPrevFrame);
}

void finance_system_gui_category::OnButtonClickAdd(wxCommandEvent& event)
{
    try {
        wxString textCtrlValue = TextCtrl -> GetValue();
        double sum = stod(textCtrlValue.ToStdString());
        this -> sum += sum;

        this -> categoryDataJson[this -> category] = this -> sum;

        ofstream write;
        write.open(pathToCategoryDataFile);
        write << this -> categoryDataJson.dump();
        write.close();

        this -> StaticText -> SetLabel(wxT("Spending: " + to_string(this -> sum)));
    } catch (...) {
        wxMessageBox("Write number in input !", "Error");
    }
}

void finance_system_gui_category::OnButtonClickDel(wxCommandEvent& event)
{
    try {
        wxString textCtrlValue = TextCtrl -> GetValue();
        double sum = stod(textCtrlValue.ToStdString());
        this -> sum -= sum;

        this -> categoryDataJson[this -> category] = this -> sum;

        ofstream write;
        write.open(pathToCategoryDataFile);
        write << this -> categoryDataJson.dump();
        write.close();

        this -> StaticText -> SetLabel(wxT("Spending: " + to_string(this -> sum)));
    } catch (...) {
        wxMessageBox("Write number in input !", "Error");
    }
}

void finance_system_gui_category::OnButtonClickDelCategory(wxCommandEvent& event)
{
    this -> categoryDataJson.erase(this -> category);
    ofstream write;
    write.open(pathToCategoryDataFile);
    write << this -> categoryDataJson.dump();
    write.close();

    wxFrame* frame = new finance_system_guiFrame(NULL, 1);
    (*frame).Show(true);

    this -> Close(true);
    delete this;
}

void finance_system_gui_category::OnButtonClickPrevFrame(wxCommandEvent& event)
{
    wxFrame* frame = new finance_system_guiFrame(NULL, 1);
    (*frame).Show(true);

    this -> Close(true);
    delete this;
}

finance_system_gui_category::~finance_system_gui_category()
{
    //dtor
}
