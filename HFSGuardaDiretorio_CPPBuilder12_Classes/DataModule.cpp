// ---------------------------------------------------------------------------

#pragma hdrstop

#include "DataModule.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "Vcl.Controls.TControl"
#pragma resource "*.dfm"
Tdm *dm;

// ---------------------------------------------------------------------------
__fastcall Tdm::Tdm(TComponent* Owner) : TDataModule(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall Tdm::DataModuleCreate(TObject *Sender) {
	/*
	 SQLAbas="select cod, nome from Abas";

	 SQLDiretorios="select aba, cod, ordem, nome, tam, tipo, " \
	 "modificado, atributos, coddirpai, caminho from Diretorios";

	 SQLExtensoes="select cod, nome, bmp16, bmp32 from Extensoes";

	 consultaDirPai="select aba, cod, ordem, coddirpai, nome, tam, " \
	 "tipo, modificado, atributos, caminho, nomeaba, nomepai, caminhopai " \
	 "from consultadirpai " \
	 "order by 1,2,3,4";
	 consultaDirFilho="select aba, cod, ordem, coddirpai, nome, tam, " \
	 "tipo, modificado, atributos, caminho, nomeaba, nomepai, caminhopai " \
	 "from consultadirfilho " \
	 "order by 1,2,3,4";
	 consultaArquivo="select aba, cod, ordem, coddirpai, nome, tam, " \
	 "tipo, modificado, atributos, caminho, nomeaba, nomepai, caminhopai " \
	 "from consultaarquivo " \
	 "order by tipo desc, ordem";
	 */
}

// ---------------------------------------------------------------------------
void __fastcall Tdm::cdsExtensoesBeforeRefresh(TDataSet *DataSet) {
	cdsExtensoes->ApplyUpdates(-1);
}
// ---------------------------------------------------------------------------
