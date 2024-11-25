unit uImportarDiretorio;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants,
  System.UITypes, System.Classes, System.Generics.Collections, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ComCtrls, uRotinas,
  uPrincipal, uImportar, uDiretorio;

type
  TFrmImportarDiretorio = class(TForm)
    memoImportaDir: TMemo;
    barraStatus: TStatusBar;
    pbImportar: TProgressBar;
    procedure memoImportaDirChange(Sender: TObject);
    procedure FormActivate(Sender: TObject);
  private
    { Private declarations }
    procedure ProgressoLog(progresso: TProgresso);
  public
    { Public declarations }
    bSubDiretorio: Boolean;
    listaImportar: TList<TImportar>;
    listaDiretorio: TList<TDiretorio>;
  end;

var
  FrmImportarDiretorio: TFrmImportarDiretorio;

implementation

{$R *.dfm}

procedure TFrmImportarDiretorio.ProgressoLog(progresso: TProgresso);
begin
  if progresso.posicao = 0 then begin
     pbImportar.Min := progresso.minimo;
     pbImportar.Max := progresso.maximo;
     pbImportar.Step := progresso.passo;
  end;

  pbImportar.Position := progresso.posicao;
end;

procedure TFrmImportarDiretorio.FormActivate(Sender: TObject);
var
  i: integer;
  sLog: String;
  importar: TImportar;
begin
  try
    for i := 0 to listaImportar.Count - 1 do
    begin
      importar := listaImportar.Items[i];
      FrmPrincipal.nGlobalOrdem := 1;

      if not bSubDiretorio then begin
          screen.Cursor := crHourGlass;

          Importar.ImportacaoCompleta(importar, FrmPrincipal.nGlobalOrdem,
            FrmPrincipal.listaExtensoes, memoImportaDir.Lines, ProgressoLog);

          screen.Cursor := crDefault;
      end else begin
        if not cDiretorio.verificaCodDir(importar.aba, importar.rotuloRaiz,
          FrmPrincipal.listaDiretorioPai) then begin
          screen.Cursor := crHourGlass;

          Importar.ImportacaoCompleta(importar, FrmPrincipal.nGlobalOrdem,
            FrmPrincipal.listaExtensoes, memoImportaDir.Lines, ProgressoLog);

          screen.Cursor := crDefault;
        end else
          MessageDlg('Este diretório [' + importar.rotuloRaiz +
            '] já existe no catálogo!', mtError, [mbOk], 0);
      end;

    end;
  finally
    listaImportar.Free;
  end;

  if FrmPrincipal.GravarLogImportacao1.Checked then begin
    if memoImportaDir.Lines.Count > 0 then begin
      sLog:=ExtractFilePath(ParamStr(0)) +
        FormatDateTime('yyyy-mm-dd_hh_nn_ss',now)+'_Importacao.log';
      memoImportaDir.Lines.SaveToFile(sLog);
    end;
  end;

  PostMessage(Self.Handle, WM_CLOSE, 0, 0);
  ModalResult := mrCancel;
end;



procedure TFrmImportarDiretorio.memoImportaDirChange(Sender: TObject);
begin
barraStatus.Panels[1].Text:=IntToStr(memoImportaDir.Lines.Count);
barraStatus.Refresh;
end;

end.
