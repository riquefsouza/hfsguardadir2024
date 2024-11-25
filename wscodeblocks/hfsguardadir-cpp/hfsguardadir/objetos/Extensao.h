#ifndef EXTENSAO_H
#define EXTENSAO_H

#include <string>
#include "../comum/Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetos {

class Extensao
{
private:
    int codigo;
    std::string nome;
    int ordem;
    ImagemBuffer bmp16;
    ImagemBuffer bmp32;
	int tamanhoBmp16;
	int tamanhoBmp32;

public:
    Extensao();
    Extensao(int codigo, const std::string &nome, int ordem,
		ImagemBuffer bmp16, ImagemBuffer bmp32);
    int getCodigo();
    void setCodigo(int codigo);
    std::string &getNome();
    void setNome(const std::string &nome);
    int getOrdem();
    void setOrdem(int ordem);
    ImagemBuffer getBmp16();
    void setBmp16(ImagemBuffer bmp16);
    ImagemBuffer getBmp32();
    void setBmp32(ImagemBuffer bmp32);
	int getTamanhoBmp16();
	void setTamanhoBmp16(int tamanhoBmp16);
	int getTamanhoBmp32();
	void setTamanhoBmp32(int tamanhoBmp32);
    void limparDados();
    bool equals(Extensao *obj);
    std::string &toString();

};

}
}

#endif // EXTENSAO_H
