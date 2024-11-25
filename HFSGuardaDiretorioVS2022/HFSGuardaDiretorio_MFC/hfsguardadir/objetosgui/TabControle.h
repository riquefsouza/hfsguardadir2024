#ifndef TABCONTROLE_H
#define TABCONTROLE_H

#pragma once

namespace hfsguardadir {

namespace objetosgui {

class TabControle // : public CTabCtrl
{
	//DECLARE_DYNAMIC(TabControle)

public:
	TabControle();
	virtual ~TabControle();
	static void adiciona(CTabCtrl &tabControle, const int nIndice, const CString &sTab);
	static void altera(CTabCtrl &tabControle, const int nIndice, const CString &sTab);
	static void remove(CTabCtrl &tabControle, const int nIndice);

protected:
	//DECLARE_MESSAGE_MAP()
};

}
}

#endif
