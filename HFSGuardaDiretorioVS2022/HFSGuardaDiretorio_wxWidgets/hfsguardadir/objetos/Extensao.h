#ifndef EXTENSAO_H
#define EXTENSAO_H

#include <wx/string.h>
#include <wx/buffer.h>

namespace hfsguardadir {

namespace objetos {

class Extensao
{
private:
    int codigo;
    wxString nome;
    int ordem;
    wxMemoryBuffer bmp16;
    wxMemoryBuffer bmp32;
    wxMemoryBuffer gif16;
    wxMemoryBuffer gif32;

public:
    Extensao();
    Extensao(int codigo, const wxString &nome, int ordem,
		const wxMemoryBuffer &bmp16, const wxMemoryBuffer &bmp32);
    int getCodigo();
    void setCodigo(int codigo);
    wxString &getNome();
    void setNome(const wxString &nome);
    int getOrdem();
    void setOrdem(int ordem);
    wxMemoryBuffer &getBmp16();
    void setBmp16(const wxMemoryBuffer &bmp16);
    wxMemoryBuffer &getBmp32();
    void setBmp32(const wxMemoryBuffer &bmp32);
    wxMemoryBuffer &getGif16();
    void setGif16(const wxMemoryBuffer &gif16);
    wxMemoryBuffer &getGif32();
    void setGif32(const wxMemoryBuffer &gif32);
    void limparDados();
    bool equals(Extensao *obj);
    wxString &toString();

};

}
}

#endif // EXTENSAO_H
