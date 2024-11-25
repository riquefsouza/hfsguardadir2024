//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "InfoDiretorio.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmInfoDiretorio *FrmInfoDiretorio;
//---------------------------------------------------------------------------
__fastcall TFrmInfoDiretorio::TFrmInfoDiretorio(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmInfoDiretorio::FormShow(TObject *Sender)
{
  sgInfo->FixedCols = 0;
  sgInfo->FixedRows = 1;
  sgInfo->ColCount = 2;
  sgInfo->RowCount = 8;
  sgInfo->DefaultRowHeight = 18;

  sgInfo->Cells[1][1] = diretorio.aba.nome;
  sgInfo->Cells[1][2] = diretorio.nome;
  sgInfo->Cells[1][3] = diretorio.tamanhoFormatado;
  sgInfo->Cells[1][4] = diretorio.tipo.nome;
  sgInfo->Cells[1][5] = diretorio.modificadoFormatado;
  sgInfo->Cells[1][6] = diretorio.atributos;
  sgInfo->Cells[1][7] = diretorio.caminho;

  sgInfo->ColWidths[1]= diretorio.caminho.Length()*10;

}
//---------------------------------------------------------------------------

void __fastcall TFrmInfoDiretorio::sgInfoDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State)
{
  if (ACol == 0) {
	sgInfo->Canvas->Font->Style = TFontStyles() << fsBold;
	switch (ARow) {
	  case 0 : sgInfo->Canvas->TextOut(Rect.Left + 2, Rect.Top + 2, "Item"); break;
	  case 1 : sgInfo->Canvas->TextOut(Rect.Left + 2, Rect.Top + 2, "Aba:"); break;
	  case 2 : sgInfo->Canvas->TextOut(Rect.Left + 2, Rect.Top + 2, "Nome:"); break;
	  case 3 : sgInfo->Canvas->TextOut(Rect.Left + 2, Rect.Top + 2, "Tamanho:"); break;
	  case 4 : sgInfo->Canvas->TextOut(Rect.Left + 2, Rect.Top + 2, "Tipo:"); break;
	  case 5 : sgInfo->Canvas->TextOut(Rect.Left + 2, Rect.Top + 2, "Modificado:"); break;
	  case 6 : sgInfo->Canvas->TextOut(Rect.Left + 2, Rect.Top + 2, "Atributos:"); break;
	  case 7 : sgInfo->Canvas->TextOut(Rect.Left + 2, Rect.Top + 2, "Caminho:"); break;
	}
  }

  if ((ACol == 1) && (ARow == 0)) {
	sgInfo->Canvas->Font->Style = TFontStyles() << fsBold;
	sgInfo->Canvas->TextOut(Rect.Left + 2, Rect.Top + 2, "Descrição");
  }
}
//---------------------------------------------------------------------------

