#include "ExampleWindow.h"
#include <iostream>

ExampleWindow::ExampleWindow() : m_Box(Gtk::Orientation::VERTICAL) {
    set_title("MenuModel Example");
    set_default_size(200, 200);

    m_Menu = Gio::Menu::create();
    m_Menu->append("Item 1", "example.item1");
    m_Menu->append("Item 2", "example.item2");
    m_Menu->append("Item 3", "example.item3");

    m_ActionGroup = Gio::SimpleActionGroup::create();
    m_ActionGroup->add_action("item1", sigc::bind(sigc::mem_fun(*this, &ExampleWindow::on_menu_item_activated), "Item 1"));
    m_ActionGroup->add_action("item2", sigc::bind(sigc::mem_fun(*this, &ExampleWindow::on_menu_item_activated), "Item 2"));
    m_ActionGroup->add_action("item3", sigc::bind(sigc::mem_fun(*this, &ExampleWindow::on_menu_item_activated), "Item 3"));

    insert_action_group("example", m_ActionGroup);

    m_Button.set_menu_model(m_Menu);
    m_Button.set_label("Open Menu");

    m_Box.append(m_Button);
    set_child(m_Box);

    //show_all_children();
    present();
}

ExampleWindow::~ExampleWindow() {}

void ExampleWindow::on_menu_item_activated(const Glib::ustring& item_name) {
    std::cout << "Menu item '" << item_name << "' activated!" << std::endl;
}
