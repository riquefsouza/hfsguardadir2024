#include "MenuPopup.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;
// ---------------------------------------------------------------------------
MenuPopup *menuPopup = (MenuPopup*) NULL;
// ---------------------------------------------------------------------------
MenuPopup::MenuPopup()
	: Gtk::Menu() {

	menuExcluirAbaAtiva2 = manage(new class Gtk::MenuItem());
	menuExcluirAbaAtiva2->set_name("menuExcluirAbaAtiva2");
	menuExcluirAbaAtiva2->set_visible(true);
	menuExcluirAbaAtiva2->set_can_focus(false);
	menuExcluirAbaAtiva2->set_label("Excluir aba ativa");
	menuExcluirAbaAtiva2->set_use_underline(true);
	
	menuAlterarNomeAbaAtiva2 = manage(new class Gtk::MenuItem());
	menuAlterarNomeAbaAtiva2->set_name("menuAlterarNomeAbaAtiva2");
	menuAlterarNomeAbaAtiva2->set_visible(true);
	menuAlterarNomeAbaAtiva2->set_can_focus(false);
	menuAlterarNomeAbaAtiva2->set_label("Alterar nome da aba ativa");
	menuAlterarNomeAbaAtiva2->set_use_underline(true);
	
	menuIncluirNovaAba2 = manage(new class Gtk::MenuItem());
	menuIncluirNovaAba2->set_name("menuIncluirNovaAba2");
	menuIncluirNovaAba2->set_visible(true);
	menuIncluirNovaAba2->set_can_focus(false);
	menuIncluirNovaAba2->set_label("Incluir nova aba");
	menuIncluirNovaAba2->set_use_underline(true);
	
	separador2 = manage(new class Gtk::SeparatorMenuItem());
	separador2->set_name("separador2");
	separador2->set_visible(true);
	separador2->set_can_focus(false);
	
	menuColapsarDiretorios2 = manage(new class Gtk::MenuItem());
	menuColapsarDiretorios2->set_name("menuColapsarDiretorios2");
	menuColapsarDiretorios2->set_visible(true);
	menuColapsarDiretorios2->set_can_focus(false);
	menuColapsarDiretorios2->set_label("Colapsar Diretórios");
	menuColapsarDiretorios2->set_use_underline(true);
	
	menuExpandirDiretorios2 = manage(new class Gtk::MenuItem());
	menuExpandirDiretorios2->set_name("menuExpandirDiretorios2");
	menuExpandirDiretorios2->set_visible(true);
	menuExpandirDiretorios2->set_can_focus(false);
	menuExpandirDiretorios2->set_label("Expandir Diretórios");
	menuExpandirDiretorios2->set_use_underline(true);
	
	menuExcluirDiretorioSelecionado = manage(new class Gtk::MenuItem());
	menuExcluirDiretorioSelecionado->set_name("menuExcluirDiretorioSelecionado");
	menuExcluirDiretorioSelecionado->set_visible(true);
	menuExcluirDiretorioSelecionado->set_can_focus(false);
	menuExcluirDiretorioSelecionado->set_label("Excluir Diretório Selecionado");
	menuExcluirDiretorioSelecionado->set_use_underline(true);
	
	menuInformacoesDiretorioArquivo = manage(new class Gtk::MenuItem());
	menuInformacoesDiretorioArquivo->set_name("menuInformacoesDiretorioArquivo");
	menuInformacoesDiretorioArquivo->set_visible(true);
	menuInformacoesDiretorioArquivo->set_can_focus(false);
	menuInformacoesDiretorioArquivo->set_label("Informações do Diretório / Arquivo");
	menuInformacoesDiretorioArquivo->set_use_underline(true);
	
	this->set_name("menuPopup");
	this->set_visible(true);
	this->set_can_focus(false);
	this->add(*menuInformacoesDiretorioArquivo);
	this->add(*menuExcluirDiretorioSelecionado);
	this->add(*menuExpandirDiretorios2);
	this->add(*menuColapsarDiretorios2);
	this->add(*separador2);
	this->add(*menuIncluirNovaAba2);
	this->add(*menuAlterarNomeAbaAtiva2);
	this->add(*menuExcluirAbaAtiva2);
	

	menuInformacoesDiretorioArquivo->signal_activate().connect(sigc::mem_fun(*this, &MenuPopup::on_menuInformacoesDiretorioArquivo_activate));
	menuExcluirDiretorioSelecionado->signal_activate().connect(sigc::mem_fun(*this, &MenuPopup::on_menuExcluirDiretorioSelecionado_activate));
	menuExpandirDiretorios2->signal_activate().connect(sigc::mem_fun(*this, &MenuPopup::on_menuExpandirDiretorios2_activate));
	menuColapsarDiretorios2->signal_activate().connect(sigc::mem_fun(*this, &MenuPopup::on_menuColapsarDiretorios2_activate));
	menuIncluirNovaAba2->signal_activate().connect(sigc::mem_fun(*this, &MenuPopup::on_menuIncluirNovaAba2_activate));
	menuAlterarNomeAbaAtiva2->signal_activate().connect(sigc::mem_fun(*this, &MenuPopup::on_menuAlterarNomeAbaAtiva2_activate));
	menuExcluirAbaAtiva2->signal_activate().connect(sigc::mem_fun(*this, &MenuPopup::on_menuExcluirAbaAtiva2_activate));

}
// ---------------------------------------------------------------------------
MenuPopup::~MenuPopup(){
	
}
// ---------------------------------------------------------------------------
void MenuPopup::mostrar() 
{
    
}
// ---------------------------------------------------------------------------
void MenuPopup::on_menuInformacoesDiretorioArquivo_activate(){

}

void MenuPopup::on_menuExcluirDiretorioSelecionado_activate(){
		
}

void MenuPopup::on_menuExpandirDiretorios2_activate(){
		
}

void MenuPopup::on_menuColapsarDiretorios2_activate(){
		
}

void MenuPopup::on_menuIncluirNovaAba2_activate(){
		
}

void MenuPopup::on_menuAlterarNomeAbaAtiva2_activate(){
		
}

void MenuPopup::on_menuExcluirAbaAtiva2_activate(){
		
}


// ---------------------------------------------------------------------------
