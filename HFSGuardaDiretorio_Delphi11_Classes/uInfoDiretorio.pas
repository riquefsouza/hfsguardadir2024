unit uInfoDiretorio;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes,
  Vcl.Graphics,  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.Grids,
  Vcl.ExtCtrls, uDiretorio;

type
  TFrmInfoDiretorio = class(TForm)
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    sgInfo: TStringGrid;
    Panel1: TPanel;
    btnOk: TButton;
    procedure FormShow(Sender: TObject);
    procedure sgInfoDrawCell(Sender: TObject; ACol, ARow: Integer; Rect: TRect;
      State: TGridDrawState);
  private
    { Private declarations }
  public
    { Public declarations }
    diretorio: TDiretorio;
  end;

var
  FrmInfoDiretorio: TFrmInfoDiretorio;

implementation

{$R *.dfm}

procedure TFrmInfoDiretorio.FormShow(Sender: TObject);
begin
  sgInfo.FixedCols := 0;
  sgInfo.FixedRows := 1;
  sgInfo.ColCount := 2;
  sgInfo.RowCount := 8;
  sgInfo.DefaultRowHeight := 25;

  sgInfo.Cells[1, 1] := diretorio.aba.nome;
  sgInfo.Cells[1, 2] := diretorio.nome;
  sgInfo.Cells[1, 3] := diretorio.tamanhoFormatado;
  sgInfo.Cells[1, 4] := diretorio.tipo.nome;
  sgInfo.Cells[1, 5] := diretorio.modificadoFormatado;
  sgInfo.Cells[1, 6] := diretorio.atributos;
  sgInfo.Cells[1, 7] := diretorio.caminho;

  sgInfo.ColWidths[1]:= Length(diretorio.caminho)*10;
end;

procedure TFrmInfoDiretorio.sgInfoDrawCell(Sender: TObject; ACol, ARow: Integer;
  Rect: TRect; State: TGridDrawState);
begin
  if (ACol = 0) then begin
    sgInfo.Canvas.Font.Style:=[fsbold];
    case ARow of
      0 : sgInfo.Canvas.TextOut(Rect.Left + 2, Rect.Top + 2, 'Item');
      1 : sgInfo.Canvas.TextOut(Rect.Left + 2, Rect.Top + 2, 'Aba:');
      2 : sgInfo.Canvas.TextOut(Rect.Left + 2, Rect.Top + 2, 'Nome:');
      3 : sgInfo.Canvas.TextOut(Rect.Left + 2, Rect.Top + 2, 'Tamanho:');
      4 : sgInfo.Canvas.TextOut(Rect.Left + 2, Rect.Top + 2, 'Tipo:');
      5 : sgInfo.Canvas.TextOut(Rect.Left + 2, Rect.Top + 2, 'Modificado:');
      6 : sgInfo.Canvas.TextOut(Rect.Left + 2, Rect.Top + 2, 'Atributos:');
      7 : sgInfo.Canvas.TextOut(Rect.Left + 2, Rect.Top + 2, 'Caminho:');
    end;
  end;

  if (ACol = 1) and (ARow = 0) then begin
    sgInfo.Canvas.Font.Style:=[fsbold];
    sgInfo.Canvas.TextOut(Rect.Left + 2, Rect.Top + 2, 'Descrição');
  end;
end;

end.
