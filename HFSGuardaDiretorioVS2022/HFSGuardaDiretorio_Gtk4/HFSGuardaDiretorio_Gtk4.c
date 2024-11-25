#include "HFSGuardaDiretorio.h"
#include "FrmPrincipal.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/objetosdao/AbaDAO.h"
#include "hfsguardadir/catalogador/Catalogador.h"

/*
GString* path;

// Função callback para abrir a AboutDialog
static void on_about_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {

    //GError* erro = NULL;
    //GdkPixbuf* pixbuf = gdk_pixbuf_new_from_file(path->str, &erro);
    //g_error_free(erro);

    GFile* logo_file = g_file_new_for_path(path->str);
    GdkTexture* example_logo = gdk_texture_new_from_file(logo_file, NULL);
    g_object_unref(logo_file);

    GtkAboutDialog* FrmSobre_frmSobre = GTK_ABOUT_DIALOG(gtk_about_dialog_new());

    gtk_widget_set_name(GTK_WIDGET(FrmSobre_frmSobre), "frmSobre");
    gtk_widget_set_can_focus(GTK_WIDGET(FrmSobre_frmSobre), FALSE);
    gtk_window_set_title(GTK_WINDOW(FrmSobre_frmSobre), "Sobre o Catalogador");
    gtk_window_set_resizable(GTK_WINDOW(FrmSobre_frmSobre), FALSE);
    gtk_window_set_modal(GTK_WINDOW(FrmSobre_frmSobre), TRUE);
    //gtk_window_set_position(GTK_WINDOW(FrmSobre_frmSobre), GTK_WINDOW_POS_CENTER);
    gtk_window_set_destroy_with_parent(GTK_WINDOW(FrmSobre_frmSobre), TRUE);
    //gtk_window_set_type_hint(GTK_WINDOW(FrmSobre_frmSobre), GDK_WINDOW_TYPE_HINT_DIALOG);
    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(FrmSobre_frmSobre), "HFSGuardaDir 2.0 - Catalogador de Diretorios");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(FrmSobre_frmSobre), "Desenvolvido em C com GTK 4");
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(FrmSobre_frmSobre), "Todos os direitos reservados, 2024");

    const char* autores[] = {
        "Henrique Figueiredo de Souza",
        NULL
    };

    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(FrmSobre_frmSobre), autores);
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(FrmSobre_frmSobre), GDK_PAINTABLE(example_logo));
    gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(FrmSobre_frmSobre), GTK_LICENSE_GPL_3_0);


    //gtk_window_set_position(GTK_WINDOW(FrmSobre_frmSobre), GTK_WIN_POS_CENTER_ALWAYS);
    //gtk_dialog_prese(GTK_DIALOG(FrmSobre_frmSobre));
    gtk_window_present(GTK_WINDOW(FrmSobre_frmSobre));
    //gtk_widget_destroy(FrmSobre_frmSobre);

}

// Callback to handle menu item activation
static void on_menu_item_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
    g_print("Menu item activated!\n");
}

static void on_activate(GtkApplication* app) {
    GtkWidget* window;
    GtkMenuButton* menu_button;
    GMenu* menu;
    GSimpleActionGroup* actions;
    GSimpleAction* action_file;
    GSimpleAction* action_about;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Hello World");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Create a GSimpleAction
    actions = g_simple_action_group_new();

    action_file = g_simple_action_new("file_action", NULL);
    g_signal_connect(action_file, "activate", G_CALLBACK(on_menu_item_activate), NULL);
    g_action_map_add_action(G_ACTION_MAP(actions), G_ACTION(action_file));

    action_about = g_simple_action_new("about_action", NULL);
    g_signal_connect(action_about, "activate", G_CALLBACK(on_about_activate), NULL);
    g_action_map_add_action(G_ACTION_MAP(actions), G_ACTION(action_about));

    gtk_widget_insert_action_group(GTK_WIDGET(window), "app", G_ACTION_GROUP(actions));


    // Create a GMenu
    menu = g_menu_new();
    GMenuItem* file_item = g_menu_item_new("File Item", "app.file_action");
    GMenuItem* about_item = g_menu_item_new("About Item", "app.about_action");

    g_menu_append_item(menu, file_item);
    g_menu_append_item(menu, about_item);

    menu_button = GTK_MENU_BUTTON(gtk_menu_button_new());
    gtk_menu_button_set_label(menu_button, "arquivo");
    gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(menu_button), G_MENU_MODEL(menu));


    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_append(GTK_BOX(box), GTK_WIDGET(menu_button));


    gtk_window_set_child(GTK_WINDOW(window), box);


    gtk_window_present(GTK_WINDOW(window));

    g_object_unref(file_item);
    g_object_unref(about_item);
    g_object_unref(menu);
    g_object_unref(actions);
    g_object_unref(action_file);
    g_object_unref(action_about);

}

int main(int argc, char* argv[]) {   
    //g_print(argv[0]);

    path = g_string_new(argv[0]);

    //gsize nBytesLidos, nBytesGravados;
    //GError* nErroOcorrido = NULL;
    //gssize tamanho = strlen(argv[0]);

    //g_string_assign(path, g_locale_to_utf8(argv[0], tamanho,
     //   &nBytesLidos, &nBytesGravados, &nErroOcorrido));

    g_string_replace(path, "HFSGuardaDiretorio_Gtk4.exe", "splash.png", 10);

    g_print(path->str);

    

    //g_print(path);

    // Create a new application
    GtkApplication* app = gtk_application_new("com.example.GtkApplication",
        G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
*/

static void on_activate(GtkApplication* app) {
    Catalogador_iniciarSistema();
    FrmPrincipal_Mostrar(app);
}

int main(int argc, char* argv[]) {
    Rotinas_argumentos(argc, argv);

    GtkApplication* app = gtk_application_new("com.hfs.hfsguardadir",
        G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}

