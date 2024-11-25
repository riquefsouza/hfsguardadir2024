unit uPrincipal;

{$mode objfpc}{$H+}

interface

uses
  LCLIntf, LCLType, SysUtils, Variants, StrUtils,
  Classes, Graphics, uListaDiretorio, uAbaObjeto, uDiretorioObjeto,
  Controls, Forms, Dialogs, Menus, ComCtrls, ExtCtrls,
  StdCtrls, Buttons, uRotinas,
  uDataModule, uImportar, uSobre, uCadExtensao, uSplash, uAba,
  uDiretorio, uExtensao, FileUtil, uListaExtensao, uListaAba, uListaImportar;

type

  { TFrmPrincipal }

  TFrmPrincipal = class(TForm)
    MainMenu1: TMainMenu;
    Aba1: TMenuItem;
    Diretorio1: TMenuItem;
    IncluirNovaAba1: TMenuItem;
    AlterarNomeAbaAtiva1: TMenuItem;
    ExcluirAbaAtiva1: TMenuItem;
    ExpandirDiretorios1: TMenuItem;
    ColapsarDiretorios1: TMenuItem;
    barraStatus: TStatusBar;
    InformacoesDiretorioArquivo1: TMenuItem;
    SobreCatalogador1: TMenuItem;
    panelPesquisa: TPanel;
    btnPesquisa: TBitBtn;
    edtPesquisa: TEdit;
    escolherDir: TSelectDirectoryDialog;
    tvFixa: TTreeView;
    sp: TSplitter;
    lvFixa: TListView;
    pageControl: TPageControl;
    TabSheet1: TTabSheet;
    ModoExibicao1: TMenuItem;
    Icones1: TMenuItem;
    Lista1: TMenuItem;
    Detalhes1: TMenuItem;
    IconesPequenos1: TMenuItem;
    ImportarDiretorio1: TMenuItem;
    N1: TMenuItem;
    pb: TProgressBar;
    ImageList3: TImageList;
    ImageList2: TImageList;
    ImageList1: TImageList;
    ToolbarImages: TImageList;
    spPesquisa: TSplitter;
    lvPesquisa: TListView;
    ExportarDiretoriosAbaAtiva1: TMenuItem;
    SQL1: TMenuItem;
    CSV1: TMenuItem;
    XML1: TMenuItem;
    sdExportar: TSaveDialog;
    PopupMenu1: TPopupMenu;
    ExcluirDiretorioSelecionado1: TMenuItem;
    MenuItem1: TMenuItem;
    MenuItem2: TMenuItem;
    Alterarabaativa1: TMenuItem;
    MenuItem3: TMenuItem;
    TXT1: TMenuItem;
    HTML1: TMenuItem;
    Viso1: TMenuItem;
    MostrarOcultArvoreDirAbaAtiva1: TMenuItem;
    MostrarOcultarListaItensPesquisados1: TMenuItem;
    Sobre1: TMenuItem;
    CadastrarExtensaoArquivo1: TMenuItem;
    ImportarDiretoriosViaXML1: TMenuItem;
    odImportar: TOpenDialog;
    btnImportarDiretorio: TButton;
    ImportarSubDiretorios1: TMenuItem;
    ExpandirDiretorios2: TMenuItem;
    ColapsarDiretorios2: TMenuItem;
    GravarLogImportacao1: TMenuItem;
    CompararDiretorios1: TMenuItem;
    procedure FormClose(Sender: TObject; var CloseAction: TCloseAction);
    procedure GravarLogImportacao1Click(Sender: TObject);
    procedure Icones1Click(Sender: TObject);
    procedure InformacoesDiretorioArquivo1Click(Sender: TObject);
    procedure Lista1Click(Sender: TObject);
    procedure Detalhes1Click(Sender: TObject);
    procedure IconesPequenos1Click(Sender: TObject);
    procedure AlterarNomeAbaAtiva1Click(Sender: TObject);
    procedure ExcluirAbaAtiva1Click(Sender: TObject);
    procedure lvFixaCompare(Sender: TObject; Item1, Item2: TListItem;
      Data: Integer; var Compare: Integer);
    procedure lvPesquisaCompare(Sender: TObject; Item1, Item2: TListItem;
      Data: Integer; var Compare: Integer);
    procedure pageControlChange(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure SobreCatalogador1Click(Sender: TObject);
    procedure tvFixaChange(Sender: TObject; Node: TTreeNode);
    procedure lvFixaColumnClick(Sender: TObject; Column: TListColumn);
    procedure lvFixaDblClick(Sender: TObject);
    procedure btnPesquisaClick(Sender: TObject);
    procedure lvPesquisaColumnClick(Sender: TObject; Column: TListColumn);
    procedure lvPesquisaClick(Sender: TObject);
    procedure ColapsarDiretorios1Click(Sender: TObject);
    procedure ExpandirDiretorios1Click(Sender: TObject);
    procedure ImportarDiretorio1Click(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure IncluirNovaAba1Click(Sender: TObject);
    procedure SQL1Click(Sender: TObject);
    procedure CSV1Click(Sender: TObject);
    procedure tvFixaCollapsing(Sender: TObject; Node: TTreeNode;
      var AllowCollapse: Boolean);
    procedure tvFixaExpanding(Sender: TObject; Node: TTreeNode;
      var AllowExpansion: Boolean);
    procedure XML1Click(Sender: TObject);
    procedure TXT1Click(Sender: TObject);
    procedure HTML1Click(Sender: TObject);
    procedure MostrarOcultArvoreDirAbaAtiva1Click(Sender: TObject);
    procedure MostrarOcultarListaItensPesquisados1Click(Sender: TObject);
    procedure Sobre1Click(Sender: TObject);
    procedure ExcluirDiretorioSelecionado1Click(Sender: TObject);
    procedure CadastrarExtensaoArquivo1Click(Sender: TObject);
    procedure ImportarDiretoriosViaXML1Click(Sender: TObject);
    procedure ImportarSubDiretorios1Click(Sender: TObject);
    procedure CompararDiretorios1Click(Sender: TObject);
  private
    { Private declarations }
    colOrdem: integer;
    listaDiretorioFilho: TListaDiretorio;
    listaArquivos: TListaDiretorio;
    procedure ProgressoLog(progresso: TProgresso);
    procedure CarregarDados(pLog: TProgressoLog; bExtensao, bDiretorio: boolean);
    procedure ExcluirDados(abaobj: TAbaObjeto; sCaminho: String);
    procedure AddItemArvore(tvAba: TTreeView; diretorio: TDiretorioObjeto;
      Nivel: integer; var node1: TTreeNode);
    procedure IncluirNovaAba(nomeAba: String);
    procedure CarregarAbas;
    procedure ListarArquivos(lvArquivos: TListView; Node: TTreeNode);
    procedure AdicionaItemLista(bLista1: boolean; lvArquivos: TListView;
      diretorio: TDiretorioObjeto);
    procedure CarregarArquivosLista(bLista1: boolean; lvArquivos: TListView;
      sCaminho: string);
    procedure TamTotalDiretorio(sCaminho: String);
    procedure DuploCliqueLista(lvLocal: TListView; tvLocal: TTreeView);
    function getTreeViewAtual(nIndicePagina: integer): TTreeView;
    function getSplitterAtual: TSplitter;
    function getListViewAtual: TListView;
    function getAbaAtual: TAbaObjeto;
    procedure Pesquisar(tvLocal: TTreeView);
    function PesquisarArvoreDiretorio(tvLocal: TTreeView;
      sCaminhoPai: string): TTreeNode;
    procedure EncontrarItemLista;
    function verificaNomeDiretorio(sCaminho: string;
       var sRotuloRaiz: string): integer;
    procedure ExportarArquivo(tipo: TTipoExportar);
    procedure ExcluirDiretorioSelecionado;
    procedure ImportarArquivo(log: TStrings);
    function ImportarDiretorios(listaCaminho: TStringList;
      bSubDiretorio: Boolean): Boolean;
    procedure ComecaImportacao(bSubDiretorios: Boolean);
    procedure FinalizaImportacao;
  public
    { Public declarations }
    nGlobalOrdem: integer;
    listaAbas: TListaAba;
    listaDiretorioPai: TListaDiretorio;
    listaExtensoes: TListaExtensao;
    procedure CarregarArvore(tvAba: TTreeView; aba: TAbaObjeto);
    function LerArvoreDiretorio(MyTreeNode1: TTreeNode;
      vbarraStatus: TStatusBar): TTreeNode;
    procedure CarregarItensLista(bLista1: boolean; lvArquivos: TListView;
      listaLocal: TListaDiretorio);
    procedure listaColunaClick(Sender: TObject; Column: TListColumn);
    procedure listaCompara(Sender: TObject; Item1, Item2: TListItem;
      Data: Integer; var Compare: Integer);
  end;

var
  FrmPrincipal: TFrmPrincipal;

implementation

{$R *.lfm}

uses uImportarDiretorio, uCompararDiretorio, uArquivo, uInfoDiretorio;

procedure TFrmPrincipal.IncluirNovaAba(nomeAba: String);
var
  sheet: TTabSheet;
  tvLocal: TTreeView;
  spLocal: TSplitter;
  lvLocal: TListView;
begin
  sheet := TTabSheet.Create(Self);
  sheet.pageControl := Self.pageControl;
  sheet.Caption := nomeAba;
  sheet.ImageIndex:=0;

  spLocal := TSplitter.Create(Self);
  //spLocal.Name := 'sp' + nomeAba;
  spLocal.Left := 213;
  spLocal.Top := 0;
  spLocal.Width := 5;
  spLocal.Height := 408;
  spLocal.Beveled := true;
  pageControl.Pages[pageControl.PageCount - 1].InsertControl(spLocal);

  tvLocal := TTreeView.Create(Self);
  //tvLocal.Name := 'tv' + nomeAba;
  tvLocal.Left := 0;
  tvLocal.Top := 0;
  tvLocal.Width := 300;
  tvLocal.Height := 408;
  tvLocal.Align := alLeft;
  tvLocal.OnChange := @tvFixaChange;
  tvLocal.OnCollapsing:=@tvFixaCollapsing;
  tvLocal.OnExpanding:=@tvFixaExpanding;
  tvLocal.Images := ImageList1;
  tvLocal.HideSelection:=False;
  tvLocal.ReadOnly := True;
  pageControl.Pages[pageControl.PageCount - 1].InsertControl(tvLocal);

  lvLocal := TListView.Create(Self);
  //lvLocal.Name := 'lv' + nomeAba;
  lvLocal.Left := 218;
  lvLocal.Top := 0;
  lvLocal.Width := 618;
  lvLocal.Height := 408;
  lvLocal.Align := alClient;
  lvLocal.GridLines := True;
  lvLocal.ViewStyle := vsReport;
  lvLocal.SmallImages:=ImageList1;
  lvLocal.LargeImages:=ImageList2;
  lvLocal.OnDblClick:=@lvFixaDblClick;
  lvLocal.OnColumnClick := @lvFixaColumnClick;
  lvLocal.OnCompare := @lvFixaCompare;
  with lvLocal.Columns.Add do
  begin
    Caption := 'Nome';
    Width := 300;
  end;
  with lvLocal.Columns.Add do
  begin
    Caption := 'Tamanho';
    Width := 100;
  end;
  with lvLocal.Columns.Add do
  begin
    Caption := 'Tipo';
    Width := 70;
  end;
  with lvLocal.Columns.Add do
  begin
    Caption := 'Modificado';
    Width := 120;
  end;
  with lvLocal.Columns.Add do
  begin
    Caption := 'Atributos';
    Width := 90;
  end;
  with lvLocal.Columns.Add do
  begin
    AutoSize := True;
    Caption := 'Caminho';
    Width := 300;
  end;

  pageControl.Pages[pageControl.PageCount - 1].InsertControl(lvLocal);
end;

procedure TFrmPrincipal.IncluirNovaAba1Click(Sender: TObject);
var aba: TAbaObjeto;
begin
  aba:=TAbaObjeto.Create;
  if InputQuery('Digite o nome da nova Aba?', 'Nome da Aba: ', aba.nome) then begin
    aba.codigo:=cAba.retMaxCodAba(listaAbas);
    aba.nome:=Copy(aba.nome,1,10);
    aba.ordem:=listaAbas.Count+1;
    cAba.incluirAba(aba);
    IncluirNovaAba(aba.nome);
    listaAbas.Add(aba);
  end;
end;

procedure TFrmPrincipal.AddItemArvore(tvAba: TTreeView; diretorio: TDiretorioObjeto;
  Nivel: integer; var node1: TTreeNode);
Var
  listaFilhos: TListaDiretorio;
  filho: TDiretorioObjeto;
  node2: TTreeNode;
  j: integer;
begin
  if Nivel = 0 then
  begin
    node1 := tvAba.Items.Add(nil, diretorio.nome);
    node1.ImageIndex:=0;
  end;

  listaFilhos := cDiretorio.itensFilhos(listaDiretorioFilho, diretorio.aba.codigo,
    diretorio.ordem, diretorio.codigo);

  for j := 0 to listaFilhos.Count - 1 do
  begin
    filho := listaFilhos.Items(j);
    node2 := tvAba.Items.AddChild(node1, filho.nome);
    node2.ImageIndex:=0;
    AddItemArvore(tvAba, filho, Succ(Nivel), node2);
  end;
  listaFilhos.free;

end;

procedure TFrmPrincipal.CarregarArvore(tvAba: TTreeView; aba: TAbaObjeto);
var
  Node: TTreeNode;
  i: integer;
begin
  tvAba.Items.Clear;

  tvAba.Items.BeginUpdate;
  try
    Node := nil;
    for i := 0 to listaDiretorioPai.Count - 1 do
    begin
      if (listaDiretorioPai.Items(i).aba.codigo = aba.codigo) then
      begin
        AddItemArvore(tvAba, listaDiretorioPai.Items(i), 0, Node);
      end;
    end;
  finally
    tvAba.Items.EndUpdate;
  end;
end;

procedure TFrmPrincipal.CadastrarExtensaoArquivo1Click(Sender: TObject);
begin
  Application.CreateForm(TFrmCadExtensao, FrmCadExtensao);
  try
    FrmCadExtensao.ShowModal;
  finally
    FrmCadExtensao.Free;
  end;
end;

procedure TFrmPrincipal.CarregarAbas;
var
  i: integer;
  tvAba: TTreeView;
begin
  pb.Min := 0;
  pb.Max := listaAbas.Count - 1;
  pb.Position := 0;
  pb.Step := 1;

  for i := 0 to listaAbas.Count - 1 do
  begin
    if i = 0 then
      pageControl.Pages[i].Caption := listaAbas.Items(i).nome
    else
      IncluirNovaAba(listaAbas.Items(i).nome);

    tvAba := getTreeViewAtual(i);

    CarregarArvore(tvAba, listaAbas.Items(i));

    pb.Position := i;
  end;
end;

function TFrmPrincipal.getTreeViewAtual(nIndicePagina: integer): TTreeView;
begin
  if nIndicePagina = 0 then
    result := TTreeView(pageControl.Pages[nIndicePagina].Controls[2])
  else
    result := TTreeView(pageControl.Pages[nIndicePagina].Controls[1]);
end;

function TFrmPrincipal.getSplitterAtual: TSplitter;
begin
  result := TSplitter(pageControl.Pages[pageControl.ActivePageIndex].Controls[0])
end;

function TFrmPrincipal.getAbaAtual: TAbaObjeto;
begin
  result:=cAba.pegaAbaPorOrdem(listaAbas,pageControl.ActivePageIndex + 1);
end;

procedure TFrmPrincipal.AlterarNomeAbaAtiva1Click(Sender: TObject);
var aba: TAbaObjeto;
begin
  aba:=getAbaAtual;
  if InputQuery('Digite o novo nome da Aba ativa?', 'Nome da Aba: ', aba.nome) then begin
    aba.nome:=copy(aba.nome,1,10);
    cAba.alterarAba(aba);
    pageControl.ActivePage.Caption:=aba.nome;
    CarregarDados(@ProgressoLog, false, true);
  end;
end;

procedure TFrmPrincipal.btnPesquisaClick(Sender: TObject);
begin
Pesquisar(getTreeViewAtual(pageControl.ActivePageIndex));
end;

procedure TFrmPrincipal.ExcluirAbaAtiva1Click(Sender: TObject);
var aba: TAbaObjeto;
begin
  if pageControl.ActivePageIndex > 0 then begin
    if MessageDlg('Tem Certeza, que você deseja excluir esta aba, '+
        'isto implicará na destruição de todos os seus items catalogados?',
        mtConfirmation, [mbYes, mbNo], 0) = mrYes then begin
      Screen.Cursor:=crHourGlass;

      aba:=getAbaAtual;
      cAba.excluirAba(aba);
      pageControl.ActivePage.Destroy;
      ExcluirDados(aba, '');
      CarregarDados(@ProgressoLog, false, false);
      getListViewAtual.Clear;
      barraStatus.Panels[1].Text:='';

      Screen.Cursor:=crDefault;
    end;
  end else
    MessageDlg('A primeira Aba não pode ser excluída!', mtError, [mbOk], 0);
end;

procedure TFrmPrincipal.lvFixaCompare(Sender: TObject; Item1, Item2: TListItem;
  Data: Integer; var Compare: Integer);
begin
  listaCompara(Sender, Item1, Item2, Data, Compare);
end;

procedure TFrmPrincipal.lvPesquisaCompare(Sender: TObject; Item1,
  Item2: TListItem; Data: Integer; var Compare: Integer);
begin
  listaCompara(Sender, Item1, Item2, Data, Compare);
end;

procedure TFrmPrincipal.ExcluirDiretorioSelecionado1Click(Sender: TObject);
begin
   ExcluirDiretorioSelecionado;
end;

procedure TFrmPrincipal.ExcluirDiretorioSelecionado;
var
  tvLocal: TTreeView;
  lvLocal: TListView;
begin
  tvLocal := getTreeViewAtual(pageControl.ActivePageIndex);
  lvLocal := getListViewAtual;

  if tvLocal.Selected <> nil then
  begin
    if tvLocal.Selected.Selected then
    begin
      if MessageDlg('Tem Certeza, que você deseja excluir este diretório, ' +
        'isto implicará na destruição de todos os seus items catalogados?',
        mtConfirmation, [mbYes, mbNo], 0) = mrYes then
      begin
        Screen.Cursor := crHourGlass;

        cDiretorio.excluirDiretorio(getAbaAtual, barraStatus.Panels[1].Text);
        ExcluirDados(getAbaAtual, barraStatus.Panels[1].Text);

        tvLocal.Items.Delete(tvLocal.Selected);
        lvLocal.Items.Clear;

        CarregarDados(@ProgressoLog, false, false);

        Screen.Cursor := crDefault;
      end;
    end;
  end;
end;

procedure TFrmPrincipal.ExpandirDiretorios1Click(Sender: TObject);
var
  tvLocal: TTreeView;
  ANode: TTreeNode;
begin
  tvLocal:=getTreeViewAtual(PageControl.ActivePageIndex);
  ANode := tvLocal.Items.GetFirstNode;
  while ANode <> nil do
  begin
    ANode.Expand(true);
    ANode := ANode.GetNextSibling;
  end;
end;

procedure TFrmPrincipal.FormCreate(Sender: TObject);
begin
  Rotinas:= TRotinas.Create;
  cArquivo := TArquivo.Create;
  cDiretorio := TDiretorio.Create;
  cAba := TAba.Create;
  cExtensao := TExtensao.Create;
  cImportar := TImportar.Create;

  listaAbas := TListaAba.Create;
  listaExtensoes := TListaExtensao.Create;
  listaDiretorioFilho := TListaDiretorio.Create;
  listaDiretorioPai := TListaDiretorio.Create;
  listaArquivos := TListaDiretorio.Create;
end;

procedure TFrmPrincipal.FormDestroy(Sender: TObject);
begin
  listaAbas.Free;
  listaExtensoes.Free;
  listaDiretorioFilho.Free;
  listaDiretorioPai.Free;
  listaArquivos.Free;

  Rotinas.Free;
  cArquivo.Free;
  cDiretorio.Free;
  cAba.Free;
  cExtensao.Free;
  cImportar.Free;
end;

procedure TFrmPrincipal.ProgressoLog(progresso: TProgresso);
begin
  if progresso.posicao = 0 then begin
     pb.Min := progresso.minimo;
     pb.Max := progresso.maximo;
     pb.Step := progresso.passo;
  end;

  pb.Position := progresso.posicao;
end;

procedure TFrmPrincipal.CarregarDados(pLog: TProgressoLog;
  bExtensao, bDiretorio: boolean);
begin
  cAba.carregarAba(listaAbas, pLog);
  if bExtensao then begin
    cExtensao.carregarExtensao(listaExtensoes, pLog);
    cExtensao.carregarExtensoes(listaExtensoes, ImageList1, ImageList2);
  end;
  if bDiretorio then begin
    cDiretorio.carregarDiretorio(dm.consultaDirPai, listaDiretorioPai, pLog);
    cDiretorio.carregarDiretorio(dm.consultaDirFilho, listaDiretorioFilho, pLog);
    cDiretorio.carregarDiretorio(dm.consultaArquivo, listaArquivos, pLog);
  end;
end;

procedure TFrmPrincipal.ExcluirDados(abaobj: TAbaObjeto; sCaminho: String);
begin
  cDiretorio.excluirListaDiretorio(listaDiretorioPai, abaobj, sCaminho);
  cDiretorio.excluirListaDiretorio(listaDiretorioFilho, abaobj, sCaminho);
  cDiretorio.excluirListaDiretorio(listaArquivos, abaobj, sCaminho);
end;

procedure TFrmPrincipal.ColapsarDiretorios1Click(Sender: TObject);
var
  tvLocal: TTreeView;
  ANode: TTreeNode;
begin
  tvLocal:=getTreeViewAtual(PageControl.ActivePageIndex);
  ANode := tvLocal.Items.GetFirstNode;
  while ANode <> nil do
  begin
    ANode.Collapse(true);
    ANode := ANode.GetNextSibling;
  end;
end;

procedure TFrmPrincipal.FormShow(Sender: TObject);
begin
  if Rotinas.atribuirParamsConexao then begin
    screen.Cursor := crHourGlass;
    CarregarDados(@FrmSplash.ProgressoLog, true, true);
    CarregarAbas;
    TamTotalDiretorio('');

    FrmSplash.Hide;
    FrmSplash.Free;

    screen.Cursor := crDefault;
  end else begin
    MessageDlg('Biblioteca do SQLlite 3 não encontrada!', mtError, [mbOk], 0);
    Close;
  end;
end;

procedure TFrmPrincipal.SobreCatalogador1Click(Sender: TObject);
begin
  Application.CreateForm(TFrmSobre, FrmSobre);
  FrmSobre.ShowModal;
  FrmSobre.Free;
end;

procedure TFrmPrincipal.Icones1Click(Sender: TObject);
var lvLocal: TListView;
begin
  TMenuItem(Sender).Checked:=true;
  lvLocal:=getListViewAtual;
  lvLocal.ViewStyle := vsIcon;
end;

procedure TFrmPrincipal.InformacoesDiretorioArquivo1Click(Sender: TObject);
var
  abaobj: TAbaObjeto;
  lvArquivos: TListView;
begin
  abaobj := getAbaAtual;
  lvArquivos := getListViewAtual;
  if lvArquivos.SelCount > 0 then begin
    Application.CreateForm(TFrmInfoDiretorio, FrmInfoDiretorio);
    FrmInfoDiretorio.diretorio:=TDiretorio.Create;
    FrmInfoDiretorio.diretorio.aba.nome := abaobj.nome;
    FrmInfoDiretorio.diretorio.nome := lvArquivos.Selected.Caption;
    FrmInfoDiretorio.diretorio.tamanhoFormatado := lvArquivos.Selected.SubItems.Strings[0];
    FrmInfoDiretorio.diretorio.tipo.nome := lvArquivos.Selected.SubItems.Strings[1];
    FrmInfoDiretorio.diretorio.modificadoFormatado := lvArquivos.Selected.SubItems.Strings[2];
    FrmInfoDiretorio.diretorio.atributos := lvArquivos.Selected.SubItems.Strings[3];
    FrmInfoDiretorio.diretorio.caminho := lvArquivos.Selected.SubItems.Strings[4];
    FrmInfoDiretorio.ShowModal;
    FrmInfoDiretorio.diretorio.Free;
    FrmInfoDiretorio.Free;
  end;
end;

procedure TFrmPrincipal.FormClose(Sender: TObject;
  var CloseAction: TCloseAction);
begin
   dm.conexao.Free;
end;

procedure TFrmPrincipal.GravarLogImportacao1Click(Sender: TObject);
begin
  GravarLogImportacao1.Checked:=(Not GravarLogImportacao1.Checked);
end;

procedure TFrmPrincipal.IconesPequenos1Click(Sender: TObject);
var lvLocal: TListView;
begin
  TMenuItem(Sender).Checked:=true;
  lvLocal:=getListViewAtual;
  lvLocal.ViewStyle := vsSmallIcon;
end;

function TFrmPrincipal.verificaNomeDiretorio(sCaminho: string;
  var sRotuloRaiz: string): integer;
begin
  sRotuloRaiz := cDiretorio.removerDrive(sCaminho);
  if Length(sRotuloRaiz) = 0 then begin
    if InputQuery('Este diretório não possui um nome!',
      'Digite o nome do diretório: ', sRotuloRaiz) then begin
      sRotuloRaiz := Trim(sRotuloRaiz);

      if Length(sRotuloRaiz) > 0 then
         result:=1
      else begin
        result:=0;
        MessageDlg('Nenhum nome de diretório informado!', mtInformation, [mbOk], 0);
      end;
    end else
      result:=0;
  end else if Pos(BARRA_INVERTIDA, sRotuloRaiz) > 0 then begin
    sRotuloRaiz:=Copy(sRotuloRaiz,
      LastDelimiter(BARRA_INVERTIDA, sRotuloRaiz)+1, Length(sRotuloRaiz));
    result:=2;
  end else
    result:=3;
end;

procedure TFrmPrincipal.ImportarDiretorio1Click(Sender: TObject);
begin
  ComecaImportacao(False);
end;

procedure TFrmPrincipal.ImportarDiretoriosViaXML1Click(Sender: TObject);
var log: TStringList;
begin
  log:=TStringList.Create;
  try
    ImportarArquivo(log);
  finally
    log.Free;
  end;
end;

procedure TFrmPrincipal.ImportarSubDiretorios1Click(Sender: TObject);
begin
  ComecaImportacao(True);
end;

procedure TFrmPrincipal.ComecaImportacao(bSubDiretorios: Boolean);
var
  sCaminho: string;
  listaCaminho: TStringList;
begin
  if escolherDir.Execute then begin
    sCaminho := escolherDir.FileName;

    Application.CreateForm(TFrmImportarDiretorio, FrmImportarDiretorio);
    listaCaminho:=TStringList.Create;
    try
      if bSubDiretorios then
        cDiretorio.carregarSubDiretorios(sCaminho, listaCaminho)
      else
        listaCaminho.Add(sCaminho);

      if ImportarDiretorios(listaCaminho, bSubDiretorios) then begin
        FinalizaImportacao;
      end;
    finally
      listaCaminho.Free;
      FrmImportarDiretorio.Free;
    end;
  end;

end;

procedure TFrmPrincipal.CompararDiretorios1Click(Sender: TObject);
begin
  Application.CreateForm(TFrmCompararDiretorio, FrmCompararDiretorio);
  try
    FrmCompararDiretorio.ShowModal;
  finally
    FrmCompararDiretorio.Free;
  end;
end;

procedure TFrmPrincipal.Detalhes1Click(Sender: TObject);
var lvLocal: TListView;
begin
  TMenuItem(Sender).Checked:=true;
  lvLocal:=getListViewAtual;
  lvLocal.ViewStyle := vsReport;
end;

procedure TFrmPrincipal.Lista1Click(Sender: TObject);
var lvLocal: TListView;
begin
  TMenuItem(Sender).Checked:=true;
  lvLocal:=getListViewAtual;
  lvLocal.ViewStyle := vsList;
end;

procedure TFrmPrincipal.pageControlChange(Sender: TObject);
var lvArquivos: TListView;
begin
  with (Sender as TPageControl) do begin
    lvArquivos:=getListViewAtual;
    if Icones1.Checked then
      lvArquivos.ViewStyle := vsIcon
    else if Lista1.Checked then
      lvArquivos.ViewStyle := vsList
    else if Detalhes1.Checked then
      lvArquivos.ViewStyle := vsReport
    else if IconesPequenos1.Checked then
      lvArquivos.ViewStyle := vsSmallIcon;
  end;
  TamTotalDiretorio('');
end;


function TFrmPrincipal.getListViewAtual: TListView;
begin
  if pageControl.ActivePageIndex = 0 then
    result:=TListView(pageControl.Pages[pageControl.ActivePageIndex].Controls[1])
  else
    result:=TListView(pageControl.Pages[pageControl.ActivePageIndex].Controls[2]);
end;

procedure TFrmPrincipal.tvFixaChange(Sender: TObject; Node: TTreeNode);
var lvArquivos: TListView;
begin
  lvArquivos:=getListViewAtual;
  ListarArquivos(lvArquivos, Node);
end;

procedure TFrmPrincipal.lvFixaColumnClick(Sender: TObject; Column: TListColumn);
begin
  listaColunaClick(Sender, Column);
end;

procedure TFrmPrincipal.ListarArquivos(lvArquivos: TListView; Node: TTreeNode);
begin
  if Node <> nil then
  begin
    if Node.Selected then
    begin
      LerArvoreDiretorio(Node, barraStatus);
      CarregarArquivosLista(true, lvArquivos, barraStatus.Panels[1].Text);
      TamTotalDiretorio(barraStatus.Panels[1].Text);
    end;
  end;
end;

procedure TFrmPrincipal.lvFixaDblClick(Sender: TObject);
begin
  DuploCliqueLista(TListView(Sender),
    getTreeViewAtual(pageControl.ActivePageIndex));
end;

procedure TFrmPrincipal.lvPesquisaClick(Sender: TObject);
begin
EncontrarItemLista;
end;

procedure TfrmPrincipal.EncontrarItemLista;
var ti:TListItem;
nAltura, nNumeroAba: integer;
tvLocal: TTreeView;
lvLocal: TListView;
begin
  if lvPesquisa.SelCount > 0 then begin
    nNumeroAba:=cAba.pegaOrdemPorNomeAba(listaAbas,lvPesquisa.Selected.SubItems.Strings[5]) - 1;
    //nNumeroAba:=StrToInt(lvPesquisa.Selected.SubItems.Strings[6]) - 1;
    PageControl.ActivePageIndex := nNumeroAba;
    tvLocal:=getTreeViewAtual(pageControl.ActivePageIndex);
    lvLocal:=getListViewAtual;

    tvLocal.Selected:=PesquisarArvoreDiretorio(tvLocal,
      lvPesquisa.Selected.SubItems.Strings[4]);  // Caminho

    ti:=lvLocal.FindCaption(0,lvPesquisa.Selected.Caption,false,true,true);
    lvLocal.SetFocus;
    if ti<>nil then begin
      lvLocal.ItemFocused:=ti;
      lvLocal.Selected:=ti;

      nAltura := round(abs(lvLocal.Font.Height * lvLocal.Font.PixelsPerInch) / 72)+2;
      lvLocal.ScrollBy(ti.Position.x,ti.Position.y-nAltura);
    end;
  end;
end;

procedure TFrmPrincipal.lvPesquisaColumnClick(Sender: TObject;
  Column: TListColumn);
begin
  listaColunaClick(Sender, Column);
end;

procedure TFrmPrincipal.MostrarOcultarListaItensPesquisados1Click(
  Sender: TObject);
begin
  if lvPesquisa.Visible=false then begin
    lvPesquisa.Visible:=true;
    spPesquisa.Visible:=true;
  end else begin
    lvPesquisa.Items.Clear;
    edtPesquisa.Clear;
    lvPesquisa.Visible:=false;
    spPesquisa.Visible:=false;
  end;
end;

procedure TFrmPrincipal.MostrarOcultArvoreDirAbaAtiva1Click(Sender: TObject);
var tvLocal: TTreeView;
 spLocal: TSplitter;
begin
  tvLocal:=getTreeViewAtual(pageControl.ActivePageIndex);
  spLocal:=getSplitterAtual;

  if tvLocal.Visible then begin
    tvLocal.Visible:=false;
    spLocal.Visible:=false;
  end else begin
    spLocal.Visible:=true;
    tvLocal.Visible:=true;
  end;

end;

procedure TfrmPrincipal.DuploCliqueLista(lvLocal: TListView; tvLocal: TTreeView);
var sCaminho: string;
begin
  if lvLocal.SelCount > 0 then begin
    if lvLocal.Selected.SubItems.Strings[1]='Diretório' then begin
      sCaminho:=barraStatus.Panels[1].Text;
      if copy(sCaminho,length(sCaminho),1)=BARRA_INVERTIDA then
        sCaminho:=barraStatus.Panels[1].Text+lvLocal.Selected.Caption
      else
        sCaminho:=barraStatus.Panels[1].Text+BARRA_INVERTIDA+lvLocal.Selected.Caption;

      tvLocal.Selected:=PesquisarArvoreDiretorio(tvLocal, sCaminho);

      CarregarArquivosLista(true, lvLocal, sCaminho);
      TamTotalDiretorio(sCaminho);
    end;
  end;
end;


function TFrmPrincipal.LerArvoreDiretorio(MyTreeNode1: TTreeNode;
  vbarraStatus: TStatusBar): TTreeNode;
var
  NodeAnterior: TTreeNode;
  sSep: string;
begin
  vbarraStatus.Panels[1].Text := MyTreeNode1.Text;
  vbarraStatus.Refresh;
  NodeAnterior := MyTreeNode1.Parent;
  result := NodeAnterior;
  while NodeAnterior <> nil do
  begin
    if Copy(NodeAnterior.Text, Length(NodeAnterior.Text), 1) = BARRA_INVERTIDA then
      sSep := ''
    else
      sSep := BARRA_INVERTIDA;

    vbarraStatus.Panels[1].Text := NodeAnterior.Text + sSep +
      vbarraStatus.Panels[1].Text;
    barraStatus.Refresh;
    result := NodeAnterior;
    NodeAnterior := NodeAnterior.Parent;
  end;
  if result = nil then
    result := MyTreeNode1;
end;

procedure TFrmPrincipal.CarregarItensLista(bLista1: boolean;
  lvArquivos: TListView; listaLocal: TListaDiretorio);
var
  i: Integer;
  diretorio: TDiretorioObjeto;
begin
  if listaLocal.Count > 0 then
  begin
    pb.Min := 0;
    pb.Max := listaLocal.Count - 1;
    pb.Position := 0;
    pb.Step := 1;
    for i := 0 to listaLocal.Count - 1 do
    begin
      diretorio := listaLocal.Items(i);
      AdicionaItemLista(bLista1, lvArquivos, diretorio);
      pb.Position := i;
    end;
  end;
end;


procedure TFrmPrincipal.AdicionaItemLista(bLista1: boolean;
  lvArquivos: TListView; diretorio: TDiretorioObjeto);
var
  list1: TListItem;
begin
  list1 := lvArquivos.Items.Add;

  list1.Caption := diretorio.nome;
  if diretorio.tipo.codigo = 'D' then
  begin
    list1.SubItems.Append('');
    list1.ImageIndex := 0;
  end
  else
  begin
    list1.SubItems.Append(diretorio.tamanhoFormatado);
    list1.ImageIndex := cExtensao.indiceExtensao(listaExtensoes, diretorio.nome);
  end;
  list1.SubItems.Append(diretorio.tipo.nome);
  list1.SubItems.Append(diretorio.modificadoFormatado);
  list1.SubItems.Append(diretorio.atributos);
  list1.SubItems.Append(diretorio.caminho);

  if not bLista1 then begin
    list1.SubItems.Append(diretorio.aba.nome);
    list1.SubItems.Append(IntToStr(diretorio.aba.codigo));
    list1.SubItems.Append(diretorio.nomePai);
  end;

end;

procedure TFrmPrincipal.CarregarArquivosLista(bLista1: boolean;
  lvArquivos: TListView; sCaminho: string);
var i: integer;
  sPaiCaminho: string;
  diretorio: TDiretorioObjeto;
  listaLocal: TListaDiretorio;
begin
  listaLocal:= TListaDiretorio.Create;
  lvArquivos.Items.Clear;

  if bLista1 then begin
      sPaiCaminho := sCaminho;
      if Copy(sCaminho, Length(sCaminho), 1) <> BARRA_INVERTIDA then
        sCaminho := sCaminho + BARRA_INVERTIDA;

      for i := 0 to listaArquivos.Count - 1 do begin
        diretorio := listaArquivos.Items(i);
        if (diretorio.aba.codigo = getAbaAtual.codigo) then begin
          if (diretorio.caminhoPai = sPaiCaminho) then begin
            if AnsiStartsStr(sCaminho, diretorio.caminho) then begin
              listaLocal.Add(diretorio);
            end;
          end;
        end;
      end;
  end else begin
      for i := 0 to listaArquivos.Count - 1 do begin
        diretorio := listaArquivos.Items(i);
        if AnsiContainsText(UpperCase(diretorio.caminho), UpperCase(sCaminho))
          then begin
          listaLocal.Add(diretorio);
        end;
      end;
  end;
  CarregarItensLista(bLista1, lvArquivos, listaLocal);

  listaLocal.Free;
end;

procedure TfrmPrincipal.TamTotalDiretorio(sCaminho: String);
var i: integer;
  diretorio: TDiretorioObjeto;
  conta, soma: Extended;
begin
  conta:=0;
  soma:=0;

  for i := 0 to listaArquivos.Count - 1 do
  begin
    diretorio := listaArquivos.Items(i);

    if (diretorio.aba.codigo = getAbaAtual.codigo) then
    begin
      if (diretorio.tipo.codigo<>'D') then
      begin
        if Length(Trim(sCaminho)) > 0 then begin
          if AnsiStartsStr(sCaminho, diretorio.caminho) then begin
            conta:=conta+1;
            soma:=soma+diretorio.tamanho;
          end;
        end else begin
          conta:=conta+1;
          soma:=soma+diretorio.tamanho;
        end;
      end;
    end;
  end;

  barraStatus.Panels[0].Text:='Quantidade Total: '+FormatFloat('0000',conta)+
  ', Tamanho Total: '+cDiretorio.MontaTamanhoBig(soma);

end;

procedure TfrmPrincipal.Pesquisar(tvLocal: TTreeView);
begin
  if tvLocal.Items.Count > 0 then begin
    if length(edtPesquisa.Text) >= 2 then begin
      lvPesquisa.Visible:=true;
      spPesquisa.Visible:=true;
      CarregarArquivosLista(false, lvPesquisa, edtPesquisa.Text);
    end else begin
      lvPesquisa.Visible:=false;
      spPesquisa.Visible:=false;
      lvPesquisa.Items.Clear;
      MessageDlg('A pesquisa só é feita com pelo menos 2 caracteres!',
        mtInformation, [mbOk], 0);
    end;
  end;
end;

function TfrmPrincipal.PesquisarArvoreDiretorio(tvLocal: TTreeView;
  sCaminhoPai: string): TTreeNode;
var proximoNode, diretorioNode: TTreeNode;
slTemp: TStringList;
nPos: integer;
begin
  screen.Cursor:=crHourGlass;

  slTemp:=TStringList.Create;
  slTemp.Text:=StringReplace(sCaminhoPai,
    BARRA_INVERTIDA,#13#10,[rfReplaceAll, rfIgnoreCase]);

  proximoNode:=tvLocal.Items.Item[0];
  diretorioNode:=nil;
  nPos:=0;
  while proximoNode<>nil do begin

    if slTemp.Strings[nPos]=proximoNode.Text then begin
      diretorioNode:=proximoNode;

      if nPos=(slTemp.Count-1) then begin
        break;
      end;
      nPos:=nPos+1;
    end;

    proximoNode:=proximoNode.GetNext;
  end;
  result:=diretorioNode;
  slTemp.Free;
  screen.Cursor:=crDefault;
end;

procedure TFrmPrincipal.ExportarArquivo(tipo: TTipoExportar);
var sExtensao: String;
begin
  case tipo of
    teTXT: sExtensao:='txt';
    teCSV: sExtensao:='csv';
    teHTML: sExtensao:='html';
    teXML: sExtensao:='xml';
    teSQL: sExtensao:='sql';
  end;

  sdExportar.FileName:=getAbaAtual.nome+'.'+sExtensao;
  sdExportar.Filter:='Arquivo '+UpperCase(sExtensao)+'|*.'+sExtensao;
  sdExportar.DefaultExt:='.'+sExtensao;
  if sdExportar.Execute then begin
    if FileExists(sdExportar.FileName) then
      raise Exception.Create('Arquivo já existe.')
    else begin
      Screen.Cursor:=crHourGlass;
      cDiretorio.exportarDiretorio(tipo, getAbaAtual, sdExportar.FileName, @ProgressoLog);
      Screen.Cursor:=crDefault;
      MessageDlg('Exportação realizada com sucesso!', mtInformation, [mbOk], 0);
    end;
  end;
end;

procedure TFrmPrincipal.Sobre1Click(Sender: TObject);
begin

end;

procedure TFrmPrincipal.SQL1Click(Sender: TObject);
begin
  ExportarArquivo(teSQL);
end;

procedure TFrmPrincipal.CSV1Click(Sender: TObject);
begin
  ExportarArquivo(teCSV);
end;

procedure TFrmPrincipal.tvFixaCollapsing(Sender: TObject; Node: TTreeNode;
  var AllowCollapse: Boolean);
begin
  Node.ImageIndex:=0;
end;

procedure TFrmPrincipal.tvFixaExpanding(Sender: TObject; Node: TTreeNode;
  var AllowExpansion: Boolean);
begin
  Node.ImageIndex:=1;
end;

procedure TFrmPrincipal.XML1Click(Sender: TObject);
begin
  ExportarArquivo(teXML);
end;

procedure TFrmPrincipal.TXT1Click(Sender: TObject);
begin
  ExportarArquivo(teTXT);
end;

procedure TFrmPrincipal.HTML1Click(Sender: TObject);
begin
  ExportarArquivo(teHTML);
end;

procedure TFrmPrincipal.ImportarArquivo(log: TStrings);
var nResultado: integer;
begin
  if odImportar.Execute then begin
    if not FileExists(odImportar.FileName) then
      raise Exception.Create('Arquivo não existe.')
    else begin
      Screen.Cursor:=crHourGlass;
      nResultado:=cDiretorio.importarDiretorioViaXML(getAbaAtual, odImportar.FileName,
        listaDiretorioPai, log, @ProgressoLog);
      if nResultado=-1 then
         MessageDlg('Importação não realizada!', mtError, [mbOk], 0)
      else if nResultado=-2 then
        MessageDlg('Este diretório já existe no catálogo!', mtError, [mbOk], 0)
      else
        FinalizaImportacao;
      Screen.Cursor:=crDefault;
    end;
  end;
end;

function TFrmPrincipal.ImportarDiretorios(listaCaminho: TStringList;
  bSubDiretorio: Boolean): Boolean;
var
  i, nAba, nRotuloRaiz, nCodDirRaiz: Integer;
  sRotuloRaiz, sCaminhoSemDrive, sCaminho: string;
  importar: TImportar;
begin
  FrmImportarDiretorio.listaImportar:=TListaImportar.Create;

  nAba := getAbaAtual.codigo;
  nCodDirRaiz := cDiretorio.retMaxCodDir(nAba, listaDiretorioPai);
  sRotuloRaiz:='';

  for i :=0 to listaCaminho.Count - 1 do
  begin
    importar:=TImportar.Create;
    sCaminho := listaCaminho.Strings[i];

    nRotuloRaiz := verificaNomeDiretorio(sCaminho, sRotuloRaiz);
    if nRotuloRaiz > 0 then
    begin
      importar.aba := nAba;
      importar.codDirRaiz := nCodDirRaiz;
      importar.rotuloRaiz := sRotuloRaiz;
      if nRotuloRaiz = 1 then
      begin
        importar.nomeDirRaiz := sRotuloRaiz;
      end
      else if nRotuloRaiz = 2 then
      begin
        sCaminhoSemDrive := cDiretorio.removerDrive(sCaminho);
        importar.nomeDirRaiz := Copy(sCaminhoSemDrive, 1,
          LastDelimiter(BARRA_INVERTIDA, sCaminhoSemDrive)-1);
      end
      else if nRotuloRaiz = 3 then
      begin
        importar.nomeDirRaiz := '';
      end;
      importar.caminho := sCaminho;

      FrmImportarDiretorio.listaImportar.Add(importar);
      Inc(nCodDirRaiz);
    end;

  end;

  FrmImportarDiretorio.bSubDiretorio:=bSubDiretorio;

  if bSubDiretorio then begin
    FrmImportarDiretorio.ShowModal;
    result:=True;
  end else begin
    if not cDiretorio.verificaCodDir(importar.aba, importar.rotuloRaiz,
      listaDiretorioPai) then begin
      FrmImportarDiretorio.ShowModal;
      result:=True;
    end else begin
      MessageDlg('Este diretório [' + importar.rotuloRaiz +
        '] já existe no catálogo!', mtError, [mbOk], 0);
      result:=False;
    end;
  end;

end;

procedure TFrmPrincipal.FinalizaImportacao;
var
  tvAba: TTreeView;
begin
  screen.Cursor := crHourGlass;

  CarregarDados(@ProgressoLog, true, true);
  tvAba := getTreeViewAtual(pageControl.ActivePageIndex);
  CarregarArvore(tvAba, getAbaAtual);

  screen.Cursor := crDefault;
  MessageDlg('Importação do(s) diretório(s) realizada com sucesso!',
    mtInformation, [mbOk], 0);
end;

procedure TFrmPrincipal.listaColunaClick(Sender: TObject; Column: TListColumn);
begin
  colOrdem := Column.Index;
  Column.Tag:= Column.Tag * -1;
  if Column.Tag = 0 then Column.Tag:=-1;
  (Sender as TCustomListView).AlphaSort;
end;

procedure TFrmPrincipal.listaCompara(Sender: TObject; Item1, Item2: TListItem;
  Data: Integer; var Compare: Integer);
var tg: integer;
begin
  tg := TListView(Sender).Column[colOrdem].Tag;

  case colOrdem of
    0:  Compare := tg * CompareText(Item1.Caption, Item2.Caption);
    1:  Compare := tg * CompareText(Item1.subitems[colOrdem-1],
      Item2.subitems[colOrdem-1]);
    2:  Compare := tg * CompareText(Item1.subitems[colOrdem-1],
      Item2.subitems[colOrdem-1]);
    3:  Compare := tg * Rotinas.CompareTextAsDateTime(Item1.subitems[colOrdem-1],
      Item2.subitems[colOrdem-1]);
    4:  Compare := tg * CompareText(Item1.subitems[colOrdem-1],
      Item2.subitems[colOrdem-1]);
    5:  Compare := tg * CompareText(Item1.subitems[colOrdem-1],
      Item2.subitems[colOrdem-1]);
  end;
end;

end.
