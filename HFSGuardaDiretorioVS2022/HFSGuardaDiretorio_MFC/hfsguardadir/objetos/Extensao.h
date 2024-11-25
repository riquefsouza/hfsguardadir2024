#ifndef EXTENSAO_H
#define EXTENSAO_H

#pragma once

namespace hfsguardadir {

namespace objetos {

class Extensao
{
private:
    int codigo;
    CString nome;
    int ordem;
    CBitmap* bmp16;
    CBitmap* bmp32;

public:
    Extensao();
    Extensao(int codigo, const CString &nome, int ordem,
		CBitmap* bmp16, CBitmap* bmp32);
    int getCodigo();
    void setCodigo(int codigo);
    CString &getNome();
    void setNome(const CString &nome);
    int getOrdem();
    void setOrdem(int ordem);
	CBitmap* getBmp16();
    void setBmp16(CBitmap* bmp16);
	CBitmap* getBmp32();
    void setBmp32(CBitmap* bmp32);
    void limparDados();
    bool equals(Extensao *obj);
    CString &toString();

};

}
}

#endif // EXTENSAO_H
