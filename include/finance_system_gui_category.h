#ifndef FINANCE_SYSTEM_GUI_CATEGORY_H
#define FINANCE_SYSTEM_GUI_CATEGORY_H
#include <wx/frame.h>
#include <string>
#include <json.hpp>

using namespace std;

//(*Headers(finance_system_guiFrame)
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/listbox.h>
#include <wx/stattext.h>
//*)

class finance_system_gui_category: public wxFrame
{
    public:
        nlohmann::json categoryDataJson;
        string category;
        double sum;
        wxStaticText* StaticText;
        wxTextCtrl* TextCtrl;

        finance_system_gui_category(wxWindow* parent, wxWindowID id= -1, string category="", double sum=0, nlohmann::json categoryDataJson={});
        virtual ~finance_system_gui_category();


        //(*Identifiers(finance_system_guiFrame)
        static const long ID_TEXTCTRL;
        static const long ID_BUTTON_DEL;
        static const long ID_STATICTEXT;
        static const long ID_BUTTON_ADD;
        static const long ID_BUTTON_DEL_CATEGORY;
        static const long ID_BUTTON_PREV_FRAME;
        //*)

        void OnButtonClickAdd(wxCommandEvent& event);
        void OnButtonClickDel(wxCommandEvent& event);
        void OnButtonClickDelCategory(wxCommandEvent& event);
        void OnButtonClickPrevFrame(wxCommandEvent& event);

    protected:

    private:
};

#endif // FINANCE_SYSTEM_GUI_CATEGORY_H
