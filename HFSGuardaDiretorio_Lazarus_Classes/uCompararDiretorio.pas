unit uCompararDiretorio;

{$mode objfpc}{$H+}

interface

uses
 LCLIntf, LCLType, SysUtils, Variants, Classes, uListaDiretorio, Graphics,
  Controls, Forms, Dialogs, ComCtrls, StdCtrls, ExtCtrls, uDiretorio,
  uAba, uAbaObjeto, uDiretorioObjeto, uRotinas;

type

  { TFrmCompararDiretorio }

  TFrmCompararDiretorio = class(TForm)
    gbDiretorio1: TGroupBox;
    cmbAba1: TComboBox;
    tvDiretorio1: TTreeView;
    gbDiretorio2: TGroupBox;
    cmbAba2: TComboBox;
    tvDiretorio2: TTreeView;
    panelPesquisa: TPanel;
    pb: TProgressBar;
    btnCompararDiretorios: TButton;
    btnSalvarLog: TButton;
    lvCompara: TListView;
    barraStatus: TStatusBar;
    Label1: TLabel;
    procedure FormShow(Sender: TObject);
    procedure cmbAba1Change(Sender: TObject);
    procedure cmbAba2Change(Sender: TObject);
    procedure btnCompararDiretoriosClick(Sender: TObject);
    procedure btnSalvarLogClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure lvComparaColumnClick(Sender: TObject; Column: TListColumn);
    procedure lvComparaCompare(Sender: TObject; Item1, Item2: TListItem;
      Data: Integer; var Compare: Integer);
  private
    { Private declarations }
    listaCompara: TListaDiretorio;
    procedure ProgressoLog(progresso: TProgresso);
    procedure LimparComparacao;
    function SQLCompara(aba1, aba2: TAbaObjeto; 
      caminho1, caminho2: String): String;
    procedure Comparar(sCaminhoDir1: String; sCaminhoDir2: String);
  public
    { Public declarations }
  end;

var
  FrmCompararDiretorio: TFrmCompararDiretorio;

implementation

{$R *.lfm}

uses uPrincipal;

procedure TFrmCompararDiretorio.ProgressoLog(progresso: TProgresso);
begin
  if progresso.posicao = 0 then begin
     pb.Min := progresso.minimo;
     pb.Max := progresso.maximo;
     pb.Step := progresso.passo;
  end;

  pb.Position := progresso.posicao;
end;

function TFrmCompararDiretorio.SQLCompara(aba1, aba2: TAbaObjeto; 
  caminho1, caminho2: String): String;
var sSQL: String;
begin
  sSQL:=SQL_CONSULTA_ARQUIVO+
  ' WHERE aba='+IntToStr(aba1.codigo)+
  ' AND caminho LIKE '+QuotedStr(caminho1+'%')+
  ' AND nome NOT IN ( '+
  ' SELECT nome '+
  ' FROM Diretorios '+
  ' WHERE aba='+IntToStr(aba2.codigo)+
  ' AND caminho LIKE '+QuotedStr(caminho2+'%')+')'+
  ' ORDER BY 1, 2, 3';
  result:=sSQL;
end;

procedure TFrmCompararDiretorio.Comparar(sCaminhoDir1: String;
  sCaminhoDir2: String);
var sSQL: String;
  aba1: TAbaObjeto;
  aba2: TAbaObjeto;
begin
  aba1 := cAba.pegaAbaPorOrdem(FrmPrincipal.listaAbas, cmbAba1.ItemIndex + 1);
  aba2 := cAba.pegaAbaPorOrdem(FrmPrincipal.listaAbas, cmbAba2.ItemIndex + 1);
  sSQL := SQLCompara(aba1, aba2, sCaminhoDir1, sCaminhoDir2);
  cDiretorio.carregarDiretorio(sSQL, listaCompara, @ProgressoLog);
  if listaCompara.Count > 0 then
  begin
    FrmPrincipal.CarregarItensLista(True, lvCompara, listaCompara);
    barraStatus.Panels[1].Text := IntToStr(listaCompara.Count);
    barraStatus.Refresh;
    btnSalvarLog.Enabled := True;
  end
  else
    MessageDlg('Nenhuma diferença encontrada!', mtInformation, [mbOk], 0);
end;

procedure TFrmCompararDiretorio.LimparComparacao;
begin
  pb.Position:=1;
  lvCompara.Clear; 
  btnSalvarLog.Enabled:=False;
  barraStatus.Panels[1].Text:='';
end;

procedure TFrmCompararDiretorio.btnCompararDiretoriosClick(Sender: TObject);
var
 sCaminhoDir1, sCaminhoDir2: String;
 bSelecionado: Boolean;
begin
  bSelecionado:=False;
  
  if tvDiretorio1.Selected<>nil then begin
    if tvDiretorio1.Selected.Selected then begin
      FrmPrincipal.LerArvoreDiretorio(tvDiretorio1.Selected, barraStatus);
      sCaminhoDir1:=barraStatus.Panels[1].Text;

      if tvDiretorio2.Selected<>nil then begin
        if tvDiretorio2.Selected.Selected then begin
          FrmPrincipal.LerArvoreDiretorio(tvDiretorio2.Selected, barraStatus);
          sCaminhoDir2:=barraStatus.Panels[1].Text;
          bSelecionado:=True;
        end;
      end;

    end;
  end;

  LimparComparacao;
  
  if bSelecionado then
    Comparar(sCaminhoDir1, sCaminhoDir2)
  else
    MessageDlg('Diretórios não selecionados!', mtInformation, [mbOk], 0);
end;

procedure TFrmCompararDiretorio.btnSalvarLogClick(Sender: TObject);
var sLog: String;
  i: integer;
  diretorio: TDiretorioObjeto;
  listaLocal: TStringList;
begin
  if listaCompara.Count > 0 then begin
    listaLocal:=TStringList.Create;
    try
      sLog:=ExtractFilePath(ParamStr(0)) +
        FormatDateTime('yyyy-mm-dd_hh_nn_ss',now)+'_Comparacao.log';

      for i := 0 to listaCompara.Count - 1 do begin
        diretorio := listaCompara.Items(i);
        listaLocal.Append(diretorio.caminho);
      end;
      listaLocal.SaveToFile(sLog);
      MessageDlg('Log salvo no mesmo diretório do sistema!',
        mtInformation, [mbOk], 0);    
    finally
      listaLocal.Free;
    end;
  end;
end;

procedure TFrmCompararDiretorio.cmbAba1Change(Sender: TObject);
var aba: TAbaObjeto;
begin
  Screen.Cursor:=crHourGlass;
  tvDiretorio1.Items.Clear;
  aba:=cAba.pegaAbaPorOrdem(FrmPrincipal.listaAbas, cmbAba1.ItemIndex+1);
  FrmPrincipal.CarregarArvore(tvDiretorio1, aba);
  LimparComparacao;
  Screen.Cursor:=crDefault;
end;

procedure TFrmCompararDiretorio.cmbAba2Change(Sender: TObject);
var aba: TAbaObjeto;
begin
  Screen.Cursor:=crHourGlass;
  tvDiretorio2.Items.Clear;
  aba:=cAba.pegaAbaPorOrdem(FrmPrincipal.listaAbas, cmbAba2.ItemIndex+1);
  FrmPrincipal.CarregarArvore(tvDiretorio2, aba);
  LimparComparacao;  
  Screen.Cursor:=crDefault;  
end;

procedure TFrmCompararDiretorio.FormCreate(Sender: TObject);
begin
  listaCompara:=TListaDiretorio.Create;
end;

procedure TFrmCompararDiretorio.FormDestroy(Sender: TObject);
begin
  listaCompara.Free;
end;

procedure TFrmCompararDiretorio.lvComparaColumnClick(Sender: TObject;
  Column: TListColumn);
begin
  FrmPrincipal.listaColunaClick(Sender, Column);
end;

procedure TFrmCompararDiretorio.lvComparaCompare(Sender: TObject; Item1,
  Item2: TListItem; Data: Integer; var Compare: Integer);
begin
  FrmPrincipal.listaCompara(Sender, Item1, Item2, Data, Compare);
end;

procedure TFrmCompararDiretorio.FormShow(Sender: TObject);
var i: integer;
 aba: TAbaObjeto;
begin

  for i := 0 to FrmPrincipal.listaAbas.Count - 1 do
  begin
    aba := FrmPrincipal.listaAbas.Items(i);
    cmbAba1.Items.Append(aba.nome);
    cmbAba2.Items.Append(aba.nome);
  end;
  cmbAba1.ItemIndex:=0;
  cmbAba2.ItemIndex:=0;

  FrmPrincipal.CarregarArvore(tvDiretorio1, 
    cAba.pegaAbaPorOrdem(FrmPrincipal.listaAbas,cmbAba1.ItemIndex+1));
  FrmPrincipal.CarregarArvore(tvDiretorio2,
    cAba.pegaAbaPorOrdem(FrmPrincipal.listaAbas,cmbAba2.ItemIndex+1));
end;

end.
