#ifndef FrmSobre_H
#define FrmSobre_H
// ---------------------------------------------------------------------------
#include <gtkmm/dialog.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/button.h>
// ---------------------------------------------------------------------------
class FrmSobre : public Gtk::Dialog {
public:
	FrmSobre();
	~FrmSobre();
	static void mostrar();
protected:
	Gtk::VBox *dialog_vbox1;
	Gtk::VBox *vbox4;
	Gtk::Label *label;
	Gtk::Label *label8;
	Gtk::Label *label9;
	Gtk::Label *label10;
	Gtk::HButtonBox *dialog_action_area1;
	Gtk::Button *btbOk;

private:
	void on_btbOk_clicked();

};
// ---------------------------------------------------------------------------
extern FrmSobre *frmSobre;
// ---------------------------------------------------------------------------
#endif
