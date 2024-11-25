#ifndef ARVORE_H
#define ARVORE_H

#pragma once

namespace hfsguardadir {

namespace objetosgui {

class Arvore //: public CTreeCtrl
{
	//DECLARE_DYNCREATE(Arvore)
	
public:
	Arvore();
	virtual ~Arvore();

	static TV_INSERTSTRUCT item(const CString &stexto, HTREEITEM hPrev, HTREEITEM hInsertAfter, int nNivel);
	static void limpar(CTreeCtrl &arvore);
	static VOID expandirTodos(CTreeCtrl &arvore);
	static VOID colapsarTodos(CTreeCtrl &arvore);
	static CString GetItemText(CTreeCtrl &arvore, HTREEITEM item);
	static VOID encontrarCaminhoPorNome(CTreeCtrl &arvore, CStringList &nomes);
	static BOOL isSelecionado(CTreeCtrl &arvore);
/*
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
*/

};

}
}

#endif

