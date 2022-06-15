/***************************************************************
 * Name:      finance_system_guiMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Gosha ()
 * Created:   2022-06-11
 * Copyright: Gosha ()
 * License:
 **************************************************************/

#include "finance_system_guiMain.h"
#include <wx/msgdlg.h>
#include <string>
#include <wx/frame.h>
#include <json.hpp>
#include "include/finance_system_gui_category.h"
#include <iostream>
#include <fstream>

using namespace std;

#include <wx/string.h>
#include <wx/intl.h>

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

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

// Path to data
const string userInSystem = getlogin();
const string pathToCategoryDataFile = "/home/" + userInSystem + "/category.json";
nlohmann::json categoryDataJson{};

const long finance_system_guiFrame::ID_BUTTON1 = wxNewId();
const long finance_system_guiFrame::ID_TEXTCTRL1 = wxNewId();
const long finance_system_guiFrame::ID_LISTBOX1 = wxNewId();
const long finance_system_guiFrame::idMenuQuit = wxNewId();
const long finance_system_guiFrame::idMenuAbout = wxNewId();
const long finance_system_guiFrame::ID_STATUSBAR1 = wxNewId();
const long finance_system_guiFrame::ID_STATICTEXT_ALL_SUM = wxNewId();

BEGIN_EVENT_TABLE(finance_system_guiFrame,wxFrame)
END_EVENT_TABLE()

finance_system_guiFrame::finance_system_guiFrame(wxWindow* parent,wxWindowID id)
{
    string data;
    ifstream read;

    read.open(pathToCategoryDataFile);
    getline(read, data);
    read.close();

    if(!data.empty()) {
        categoryDataJson = nlohmann::json::parse(data);

        Create(parent, id, "Finance system", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
        SetClientSize(wxSize(1920,1080));

        new wxButton(this, ID_BUTTON1, _("Add category"), wxPoint(660,160), wxSize(600,60), 0, wxDefaultValidator, _T("ID_BUTTON1"));
        TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(660,60), wxSize(600,60), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
        ListBox1 = new wxListBox(this, ID_LISTBOX1, wxPoint(660,260), wxSize(600,300), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));

        double allSum = 0;
        for (auto& el : categoryDataJson.items())
        {
            double value = el.value();
            string key = el.key();

            allSum+=value;

            ListBox1 -> Append(key);
        }
        new wxStaticText(this, ID_STATICTEXT_ALL_SUM, "All spending: " + to_string(allSum), wxPoint(660, 230), wxDefaultSize, 0, _T("ID_STATICTEXT_ALL_SUM"));
        Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&finance_system_guiFrame::OnButton1Click);
        Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&finance_system_guiFrame::OnListBox1Select1);
        Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&finance_system_guiFrame::OnQuit);
        Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&finance_system_guiFrame::OnAbout);
    } else {
        Create(parent, id, "Finance system", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
        SetClientSize(wxSize(1205,450));

        new wxButton(this, ID_BUTTON1, _("Add category"), wxPoint(660,160), wxSize(600,60), 0, wxDefaultValidator, _T("ID_BUTTON1"));
        TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(660,60), wxSize(600,60), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
        ListBox1 = new wxListBox(this, ID_LISTBOX1, wxPoint(660,260), wxSize(600,300), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));

        Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&finance_system_guiFrame::OnButton1Click);
        Connect(ID_LISTBOX1, wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&finance_system_guiFrame::OnListBox1Select1);
        Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&finance_system_guiFrame::OnQuit);
        Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&finance_system_guiFrame::OnAbout);
    }
}

finance_system_guiFrame::~finance_system_guiFrame()
{
    //(*Destroy(finance_system_guiFrame)
    //*)
}

void finance_system_guiFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void finance_system_guiFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void finance_system_guiFrame::OnButton1Click(wxCommandEvent& event)
{
    wxString category = TextCtrl1 -> GetValue();

    if(!category.empty()) {
        try {
            categoryDataJson[category.ToStdString()].get<float>();

            wxMessageBox("This category already exist !", "Error");

            return;
        } catch(...) {
            categoryDataJson[string(category.mb_str())] = 0;
            string stringJson = categoryDataJson.dump();

            ofstream write;
            write.open(pathToCategoryDataFile);
            write << stringJson;
            write.close();
            ListBox1 -> Append(string(category.mb_str()));

            return;
        }
    }
    wxMessageBox("Write category in input !", "Error");
}

void finance_system_guiFrame::OnListBox1Select1(wxCommandEvent& event)
{
    string category = event.GetString().ToStdString();

    try {
        string data;
        ifstream read;

        read.open(pathToCategoryDataFile);
        getline(read, data);
        read.close();

        categoryDataJson = nlohmann::json::parse(data);

        wxFrame* frame = new finance_system_gui_category(NULL, 1, category, categoryDataJson[category].get<double>(), categoryDataJson);
        (*frame).Show(true);
        this -> Close(true);
    } catch (...) {
        wxMessageBox("Some error ...");
    }
}
