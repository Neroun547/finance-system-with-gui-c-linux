/***************************************************************
 * Name:      finance_system_guiMain.h
 * Purpose:   Defines Application Frame
 * Author:    Gosha ()
 * Created:   2022-06-11
 * Copyright: Gosha ()
 * License:
 **************************************************************/

#ifndef FINANCE_SYSTEM_GUIMAIN_H
#define FINANCE_SYSTEM_GUIMAIN_H

#include <wx/button.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/listbox.h>
#include <wx/stattext.h>


class finance_system_guiFrame: public wxFrame
{
    public:

        finance_system_guiFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~finance_system_guiFrame();

    private:

        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnListBox1Select(wxCommandEvent& event);
        void OnListBox1Select1(wxCommandEvent& event);


        static const long ID_BUTTON1;
        static const long ID_TEXTCTRL1;
        static const long ID_LISTBOX1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_STATICTEXT_ALL_SUM;

        wxListBox* ListBox1;
        wxStatusBar* StatusBar1;
        wxButton* Button1;
        wxTextCtrl* TextCtrl1;

        DECLARE_EVENT_TABLE()
};

#endif // FINANCE_SYSTEM_GUIMAIN_H
