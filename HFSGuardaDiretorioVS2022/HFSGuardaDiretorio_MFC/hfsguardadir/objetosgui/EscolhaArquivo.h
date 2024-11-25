#pragma once
#ifndef ESCOLHAARQUIVO_H
#define ESCOLHAARQUIVO_H

#pragma once

namespace hfsguardadir {

namespace objetosgui {
		
class EscolhaArquivo
{
private:
	static CString getTextoExtensao(const CString &extensao);

public:
	EscolhaArquivo();
	virtual ~EscolhaArquivo();

	static CString abrirDiretorio(CWnd *pai);
	static CString abrirArquivo(CWnd *pai);
	static CString abrirArquivo(CWnd *pai, const CString &arquivo, const CString &extensao);
	static CString salvarArquivo(CWnd *pai, const CString &arquivo, const CString &extensao);
};

}
}

#endif
