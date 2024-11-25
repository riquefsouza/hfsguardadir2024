#ifndef EXAMPLEWINDOW_H
#define EXAMPLEWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/menubutton.h>
#include <gtkmm/box.h>
#include <giomm.h>

class ExampleWindow : public Gtk::Window {
public:
    ExampleWindow();
    virtual ~ExampleWindow();

protected:
    void on_menu_item_activated(const Glib::ustring& item_name);

    Gtk::Box m_Box;
    Gtk::MenuButton m_Button;
    Glib::RefPtr<Gio::Menu> m_Menu;
    Glib::RefPtr<Gio::SimpleActionGroup> m_ActionGroup;
};

#endif
