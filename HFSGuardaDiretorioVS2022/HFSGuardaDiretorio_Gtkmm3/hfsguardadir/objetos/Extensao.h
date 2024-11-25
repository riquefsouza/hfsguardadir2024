#ifndef EXTENSAO_H
#define EXTENSAO_H

#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX (std::numeric_limits<ptrdiff_t>::max())
#endif

#include <glibmm/ustring.h>
#include <gdkmm/pixbuf.h>

namespace hfsguardadir {

namespace objetos {

class Extensao
{
private:
    int codigo;
    Glib::ustring nome;
    int ordem;
    Glib::RefPtr<Gdk::Pixbuf> bmp16;
    Glib::RefPtr<Gdk::Pixbuf> bmp32;
	int tamanhoBmp16;
	int tamanhoBmp32;

public:
    Extensao();
    Extensao(int codigo, const Glib::ustring &nome, int ordem,
		Glib::RefPtr<Gdk::Pixbuf> bmp16, Glib::RefPtr<Gdk::Pixbuf> bmp32);
    int getCodigo();
    void setCodigo(int codigo);
    Glib::ustring &getNome();
    void setNome(const Glib::ustring &nome);
    int getOrdem();
    void setOrdem(int ordem);
    Glib::RefPtr<Gdk::Pixbuf> getBmp16();
    void setBmp16(Glib::RefPtr<Gdk::Pixbuf> bmp16);
    Glib::RefPtr<Gdk::Pixbuf> getBmp32();
    void setBmp32(Glib::RefPtr<Gdk::Pixbuf> bmp32);
	int getTamanhoBmp16();
	void setTamanhoBmp16(int tamanhoBmp16);
	int getTamanhoBmp32();
	void setTamanhoBmp32(int tamanhoBmp32);
    void limparDados();
    bool equals(Extensao *obj);
    Glib::ustring &toString();

};

}
}

#endif // EXTENSAO_H
