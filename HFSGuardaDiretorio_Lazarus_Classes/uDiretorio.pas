unit uDiretorio;

{$mode objfpc}{$H+}

interface

uses
 Classes, SysUtils, StrUtils, uDiretorioObjeto, uListaDiretorio,
 uDataModule, SQLiteTable3, uAbaObjeto,
  uAba, uArquivo, uRotinas, FileUtil;

const
  SQL_CONSULTA_ARQUIVO : String = 'select aba, cod, ordem, coddirpai, nome, ' +
  'tam, tipo, modificado, atributos, caminho, nomeaba, nomepai, caminhopai '+
  'from consultaarquivo';

type
  TTipoExportar = (teTXT, teCSV, teHTML, teXML, teSQL);
  TDiretorio = class(TDiretorioObjeto)
  private
    { Private declarations }
  public
    { Public declarations }
    constructor Create;
    destructor Destroy; override;
    procedure carregarDiretorio(sSQL: String;
      listaDiretorio: TListaDiretorio; progressoLog: TProgressoLog);
    function atribuiDiretorio(nAba, nCodDirRaiz: integer;
      sNomeDirRaiz, sDiretorio: string; bDiretorio: boolean;
      listaLocal: TListaDiretorio; arquivo: TArquivo;
      var nOrdem: integer): TDiretorio;
    procedure atribuiListaDiretorio(nAba, nCodDirRaiz: integer;
      sNomeDirRaiz, sDiretorio: string; listaLocal: TListaDiretorio;
      SearchRec: TSearchRec; var nOrdem: integer; log: TStrings);
    procedure ImportarDiretorio(nAba, nCodDirRaiz: integer;
      sNomeDirRaiz, sDiretorio:string; listaLocal: TListaDiretorio;
      var nOrdem: integer; log: TStrings);
    function verificaCodDir(nAba: integer; sDiretorio: string;
      listaLocal: TListaDiretorio): boolean;
    function retMaxCodDir(nAba: integer; listaLocal: TListaDiretorio): integer;
    function diretorioToSQL(diretorio: TDiretorioObjeto; bInsert: boolean): String;
    procedure salvarDiretorio(listaDiretorio: TListaDiretorio; log: TStrings;
     progressoLog: TProgressoLog);
    function excluirDiretorio(abaobj: TAbaObjeto; sCaminho: String):boolean;
    procedure excluirListaDiretorio(listaDiretorio: TListaDiretorio;
              abaobj: TAbaObjeto; sCaminho: String);
    function diretorioToCSV(diretorio: TDiretorioObjeto): string;
    function diretorioToXML(diretorio: TDiretorioObjeto): string;
    function diretorioToTXT(diretorio: TDiretorioObjeto): string;
    function diretorioToHTML(diretorio: TDiretorioObjeto): string;
    procedure exportarDiretorio(tipoexp: TTipoExportar; abaobj: TAbaObjeto;
      sNomeArquivo :String; progressoLog: TProgressoLog);
    function criarTabelaDiretorios:boolean;
    function importarDiretorioViaXML(abaobj: TAbaObjeto; sNomeArquivo:String;
      listaDirPai: TListaDiretorio; log: TStrings; progressoLog: TProgressoLog): integer;
    function XMLParaDiretorio(sTexto: string; nArquivo: Integer;
      var diretorio: TDiretorioObjeto): Integer;
    function carregarSubDiretorios(sDiretorio: String; listaLocal: TStringList): Boolean;
    function carregarArquivos(sDiretorio: String; listaLocal: TStringList): Boolean;
    function MontaTamanho(nTam: Int64): String;
    function MontaTamanhoBig(nTam: Extended): String;
    function itensFilhos(lista_pai: TListaDiretorio; naba, nCodDirPai, ncodigo: integer)
      : TListaDiretorio;
    function arquivoAtributos(npAtributos: integer): String;
    function retCodDirPai(nAba: integer; sDiretorio: string;
      listaLocal: TListaDiretorio): integer;
    function searchRecToArquivo(SearchRec: TSearchRec): TArquivo;
    function removerDrive(sDiretorio: string):string;
    function carregarTodosArquivos(sDiretorio: String;
      listaLocal: TStringList): boolean;
  end;

var
  cDiretorio: TDiretorio;

implementation

constructor TDiretorio.Create;
begin
  inherited Create;

  aba:=TAba.Create;
end;

destructor TDiretorio.Destroy;
begin
  aba.Free;
  inherited Destroy;
end;

function TDiretorio.criarTabelaDiretorios:boolean;
var sSQL: String;
begin
  sSQL:='create table IF NOT EXISTS Diretorios('+
  'aba integer not null,'+
  'cod integer not null,'+
  'ordem integer not null,'+
  'nome varchar(255) not null,'+
  'tam numeric not null,'+
  'tipo char(1) not null,'+
  'modificado date not null,'+
  'atributos varchar(20) not null,'+
  'coddirpai integer not null,'+
  'caminho varchar(255) not null,'+
  'primary key (aba, cod, ordem))';
  result:=Rotinas.execConsulta(sSQL, False);
end;

function TDiretorio.MontaTamanho(nTam: Int64): String;
begin
  if nTam > 0 then begin
    result:=MontaTamanhoBig(nTam);
  end else
    result:='';
end;

function TDiretorio.MontaTamanhoBig(nTam: Extended): String;
var
  nUmKilo, nUmMega, nUmGiga, nUmTera, nUmPeta: Extended;
begin
  nUmKilo := 1024;
  nUmMega := nUmKilo * 1024;
  nUmGiga := nUmMega * 1024;
  nUmTera := nUmGiga * 1024;
  nUmPeta := nUmTera * 1024;

  if (nTam < nUmKilo) then
  begin
    Result := FormatFloat('#,##0.00', nTam) + ' Byte(s)';
  end
  else if (nTam > nUmKilo) and (nTam < nUmMega) then
  begin
    nTam:=nTam / nUmKilo;
    Result := FormatFloat('#,##0.00', nTam) + ' KByte(s)';
  end
  else if (nTam > nUmMega) and (nTam < nUmGiga) then
  begin
    nTam:=nTam / nUmMega;
    Result := FormatFloat('#,##0.00', nTam) + ' MByte(s)';
  end
  else if (nTam > nUmGiga) and (nTam < nUmTera) then
  begin
    nTam:=nTam / nUmGiga;
    Result := FormatFloat('#,##0.00', nTam) + ' GByte(s)';
  end
  else if (nTam > nUmTera) and (nTam < nUmPeta) then
  begin
    nTam := nTam / nUmTera;
    Result := FormatFloat('#,##0.00', nTam) + ' TByte(s)';
  end
  else
  begin
    nTam := nTam / nUmPeta;
    Result := FormatFloat('#,##0.00', nTam) + ' PByte(s)';
  end;
end;

procedure TDiretorio.carregarDiretorio(sSQL: String;
  listaDiretorio: TListaDiretorio; progressoLog: TProgressoLog);
var
  diretorio: TDiretorio;
  i, total: integer;
  consultaDir: TSQLiteTable;
  sTamanho: String;
  nTamanho: double;
  pb: TProgresso;
begin
  listaDiretorio.Clear;

  consultaDir:=dm.conexao.GetTable(AnsiString(sSQL));
  total := consultaDir.Count;
  consultaDir.MoveFirst;

  if total > 0 then begin
    pb.minimo := 0;
    pb.maximo := total - 1;
    pb.posicao := 0;
    pb.passo := 1;

    for i := 0 to total - 1 do begin
      diretorio:=TDiretorio.Create;

      with diretorio do begin
        aba.codigo := consultaDir.FieldAsInteger(consultaDir.FieldIndex['aba']);
        codigo := consultaDir.FieldAsInteger(consultaDir.FieldIndex['cod']);
        ordem := consultaDir.FieldAsInteger(consultaDir.FieldIndex['ordem']);

        if (not consultaDir.FieldIsNull(consultaDir.FieldIndex['coddirpai'])) then
          codDirPai := consultaDir.FieldAsInteger(consultaDir.FieldIndex['coddirpai'])
        else
          codDirPai := -1;

        nome := consultaDir.FieldAsString(consultaDir.FieldIndex['nome']);
		
        if (not consultaDir.FieldIsNull(consultaDir.FieldIndex['tam'])) then
        begin
          nTamanho:=consultaDir.FieldAsDouble(consultaDir.FieldIndex['tam']);
          sTamanho := FloatToStr(nTamanho);
          if Pos('.', sTamanho) > 0 then
            sTamanho:=StringReplace(sTamanho, '.0', '', [rfReplaceAll, rfIgnoreCase]);
          tamanho := StrToInt64(sTamanho);
        end else
          tamanho := 0;		

		tipo.codigo := consultaDir.FieldAsString(consultaDir.FieldIndex['tipo']);
        modificado := StrToDateTime(consultaDir.FieldAsString(consultaDir.FieldIndex['modificado']));
        atributos := consultaDir.FieldAsString(consultaDir.FieldIndex['atributos']);
        caminho := consultaDir.FieldAsString(consultaDir.FieldIndex['caminho']);
        aba.nome := consultaDir.FieldAsString(consultaDir.FieldIndex['nomeaba']);
        nomePai := consultaDir.FieldAsString(consultaDir.FieldIndex['nomepai']);
        caminhoPai := consultaDir.FieldAsString(consultaDir.FieldIndex['caminhopai']);
        tamanhoFormatado:=MontaTamanho(tamanho);
        if tipo.codigo='D' then
          tipo.nome:='Diretório'
        else
          tipo.nome:='Arquivo';
        modificadoFormatado:=FormatDateTime('dd/mm/yyyy hh:nn:ss', modificado);
      end;

      listaDiretorio.Add(diretorio);

      consultaDir.Next;

      pb.posicao := i;

      if Assigned(progressoLog) then begin
        progressoLog(pb);
      end;
    end;
  end;
  consultaDir.Free;

end;


function TDiretorio.itensFilhos(lista_pai: TListaDiretorio; naba, ncodDirPai, ncodigo: integer)
  : TListaDiretorio;
var
  diretorio: TDiretorioObjeto;
  lista: TListaDiretorio;
  i: integer;
begin
  lista := TListaDiretorio.Create;
  for i := 0 to lista_pai.Count - 1 do
  begin
    diretorio:=lista_pai.Items(i);
    if (diretorio.aba.codigo = naba) then begin
      if (lista_pai.Items(i).codDirPai = ncodDirPai) then begin
        if (lista_pai.Items(i).codigo = ncodigo) then begin
          lista.Add(lista_pai.Items(i));
        end;
      end;
    end;
  end;
  Result := lista;
end;

function TDiretorio.arquivoAtributos(npAtributos: integer): String;
var sAtributos: string;
begin
  sAtributos:='';
  if (npAtributos and SysUtils.faReadOnly > 0) then sAtributos:=sAtributos+'[ROL]';
  if (npAtributos and SysUtils.faHidden > 0) then sAtributos:=sAtributos+'[HID]';
  if (npAtributos and SysUtils.faSysFile > 0) then sAtributos:=sAtributos+'[SYS]';
  //if (npAtributos and SysUtils.faVolumeID > 0) then sAtributos:=sAtributos+'[VOL]';
  if (npAtributos and SysUtils.faDirectory > 0) then sAtributos:=sAtributos+'[DIR]';
  if (npAtributos and SysUtils.faArchive > 0) then sAtributos:=sAtributos+'[ARQ]';
  //if (npAtributos and SysUtils.faAnyFile > 0) then sAtributos:=sAtributos+'[Q]';
  result:=sAtributos;
end;

function TDiretorio.retCodDirPai(nAba: integer; sDiretorio: string;
  listaLocal: TListaDiretorio): integer;
var i: integer;
  diretorio: TDiretorioObjeto;
begin
  result:=0;

  for i := 0 to listaLocal.Count - 1 do begin
    diretorio := listaLocal.Items(i);
    if (diretorio.aba.codigo = nAba) then begin
      if diretorio.caminho = sDiretorio then begin
         result:=diretorio.ordem;
         break;
      end;
    end;
  end;

end;

function TDiretorio.atribuiDiretorio(nAba, nCodDirRaiz: integer;
  sNomeDirRaiz, sDiretorio: string; bDiretorio: boolean;
  listaLocal: TListaDiretorio; arquivo: TArquivo;
  var nOrdem: integer): TDiretorio;
var
  diretorio: TDiretorio;
  sCaminho: String;
begin
  sCaminho:=removerDrive(sDiretorio);

  if (Length(sCaminho) > 0) and (Length(sNomeDirRaiz) > 0) then begin
    if AnsiStartsStr(sNomeDirRaiz, sCaminho) then begin
      sCaminho:=Copy(sCaminho, Length(sNomeDirRaiz)+2, Length(sCaminho));
    end else begin
      sCaminho:=sNomeDirRaiz+BARRA_INVERTIDA+sCaminho;
    end;
  end;

  diretorio:=TDiretorio.Create;
  with diretorio do begin
    aba.codigo := nAba;
    codigo := nCodDirRaiz;
    ordem := nOrdem;
    nome := arquivo.nome;
    tamanho := arquivo.tamanho;
    modificado := arquivo.modificado;
    atributos := arquivoAtributos(arquivo.natributos);

    if sDiretorio='' then begin
      caminho:=arquivo.nome;
      caminhoPai := '';
    end else begin
      caminho:=sCaminho;
      caminhoPai := copy(caminho,1,LastDelimiter(BARRA_INVERTIDA, caminho)-1);
    end;

    if bDiretorio then begin
      tipo.codigo:='D';
      if nOrdem=1 then
        codDirPai:=0
      else
        codDirPai := retCodDirPai(aba.codigo, caminhoPai, listaLocal);
    end else begin
      tipo.codigo:='A';
      codDirPai := retCodDirPai(aba.codigo, caminhoPai, listaLocal);
    end;

    aba.nome := '';
    nomePai := '';
    tamanhoFormatado:=MontaTamanho(tamanho);
    if tipo.codigo='D' then
      tipo.nome:='Diretório'
    else begin
      tipo.nome:='Arquivo';
    end;
    modificadoFormatado:=FormatDateTime('dd/mm/yyyy hh:nn:ss', modificado);
    caminhoOriginal:=sDiretorio;
  end;

  inc(nOrdem);

  result:=diretorio;
end;

function TDiretorio.searchRecToArquivo(SearchRec: TSearchRec): TArquivo;
var
  arquivo: TArquivo;
begin
  arquivo:=TArquivo.Create;
  arquivo.nome:=SearchRec.Name;
  arquivo.tamanho:=SearchRec.Size;
  arquivo.modificado:=FileDateToDateTime(SearchRec.Time);
  arquivo.natributos:=SearchRec.Attr;
  result:=arquivo;
end;

procedure TDiretorio.atribuiListaDiretorio(nAba, nCodDirRaiz: integer;
  sNomeDirRaiz, sDiretorio: string; listaLocal: TListaDiretorio;
  SearchRec: TSearchRec; var nOrdem: integer; log: TStrings);
var
  diretorio: TDiretorio;
begin
    if FileExists(sDiretorio) then begin
      diretorio:=atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
        sDiretorio, false, listaLocal,
        searchRecToArquivo(SearchRec), nOrdem);
      listaLocal.Add(diretorio);
      log.Append(sDiretorio);
    end else if DirectoryExists(sDiretorio) then begin
      if (SearchRec.Name<>'.') and (SearchRec.Name<>'..') then begin
        diretorio:=atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
          sDiretorio, true, listaLocal,
          searchRecToArquivo(SearchRec), nOrdem);
        listaLocal.Add(diretorio);
        log.Append(sDiretorio);

        ImportarDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz, sDiretorio,
          listaLocal, nOrdem, log);
      end;
    end;
end;

procedure TDiretorio.ImportarDiretorio(nAba, nCodDirRaiz: integer;
  sNomeDirRaiz, sDiretorio:string; listaLocal: TListaDiretorio;
  var nOrdem: integer; log: TStrings);
var
  SearchRec : TSearchRec;
  sCaminho, sSeparador: String;
begin
  if Copy(sDiretorio,Length(sDiretorio),1)=BARRA_NORMAL then
    sSeparador := ''
  else
    sSeparador := BARRA_NORMAL;

  sCaminho:=sDiretorio+sSeparador+'*.*';
  if FindFirst(sCaminho,faAnyFile,SearchRec) = 0 then begin

    sCaminho:=sDiretorio+sSeparador+SearchRec.Name;
    atribuiListaDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz, sCaminho,
      listaLocal, SearchRec, nOrdem, log);

    while FindNext(SearchRec) = 0 do begin
      sCaminho:=sDiretorio+sSeparador+SearchRec.Name;
      atribuiListaDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz, sCaminho,
        listaLocal, SearchRec, nOrdem, log);
    end;
  end;
  FindClose(SearchRec);
end;

function TDiretorio.removerDrive(sDiretorio: string):string;
var sDir: string;
begin
  sDir:=Copy(sDiretorio, 4, Length(sDiretorio));
  sDir:=StringReplace(sDir,BARRA_NORMAL,BARRA_INVERTIDA,
    [rfReplaceAll, rfIgnoreCase]);
  result:=Trim(sDir);
end;

function TDiretorio.verificaCodDir(nAba: integer; sDiretorio: string;
  listaLocal: TListaDiretorio): boolean;
var i: integer;
  diretorio: TDiretorioObjeto;
begin
  result:=false;

  if Length(sDiretorio) > 0 then begin
    for i := 0 to listaLocal.Count - 1 do begin
      diretorio := listaLocal.Items(i);
      if (diretorio.aba.codigo = nAba) then begin
        if (diretorio.ordem = 1) then begin
          if (diretorio.codDirPai = 0) then begin
            if diretorio.caminho = sDiretorio then begin
               result:=true;
               break;
            end;
          end;
        end;
      end;
    end;
  end;

end;

function TDiretorio.retMaxCodDir(nAba: integer; listaLocal: TListaDiretorio): integer;
var i, nMaior: integer;
  diretorio: TDiretorioObjeto;
begin
  nMaior:=-1;

  for i := 0 to listaLocal.Count - 1 do begin
    diretorio := listaLocal.Items(i);
    if (diretorio.aba.codigo = nAba) then begin
      if (diretorio.codigo > nMaior) then begin
         nMaior:=diretorio.codigo;
      end;
    end;
  end;

  result:=nMaior+1;
end;

function TDiretorio.diretorioToSQL(diretorio: TDiretorioObjeto; bInsert: boolean): String;
var sSQL: String;
begin
  if bInsert then begin
    sSQL:='insert into Diretorios(aba, cod, ordem, coddirpai, nome, tam,'+
    'tipo,modificado, atributos, caminho) values(';
  end;

  with diretorio do
  begin
    sSQL := sSQL + IntToStr(aba.codigo) + ',';
    sSQL := sSQL + IntToStr(codigo) + ',';
    sSQL := sSQL + IntToStr(ordem) + ',';
    sSQL := sSQL + IntToStr(codDirPai) + ',';
    sSQL := sSQL + QuotedStr(nome) + ',';
    sSQL := sSQL + IntToStr(tamanho) + ',';
    sSQL := sSQL + QuotedStr(tipo.codigo) + ',';
    sSQL := sSQL + QuotedStr(modificadoFormatado) + ',';
    sSQL := sSQL + QuotedStr(atributos) + ',';
    sSQL := sSQL + QuotedStr(caminho);

    if bInsert then
      sSQL := sSQL + ')';
  end;
  result:=sSQL;
end;


procedure TDiretorio.salvarDiretorio(listaDiretorio: TListaDiretorio; log: TStrings;
  progressoLog: TProgressoLog);
var sSQL: String;
  diretorio: TDiretorioObjeto;
  i: integer;
  pb: TProgresso;
begin
  pb.minimo := 0;
  pb.maximo := listaDiretorio.Count - 1;
  pb.posicao := 0;
  pb.passo := 1;

  dm.conexao.BeginTransaction;
  for i := 0 to listaDiretorio.Count - 1 do begin
    diretorio := listaDiretorio.Items(i);

    sSQL:=diretorioToSQL(diretorio, true);
    Rotinas.execConsulta(sSQL, False);

    log.Append(IntToStr(i+1)+' - Salvando Diretório: '+diretorio.caminho);
    pb.posicao := i;

    if Assigned(progressoLog) then begin
      progressoLog(pb);
    end;
  end;
  dm.conexao.Commit;
end;


function TDiretorio.excluirDiretorio(abaobj: TAbaObjeto; sCaminho: String):boolean;
var sSQL: string;
begin
  sSQL:='delete from Diretorios where caminho like '+QuotedStr(sCaminho+'%')+
  ' and aba='+inttostr(abaobj.codigo);
  result:=Rotinas.execConsulta(sSQL, True);
end;

procedure TDiretorio.excluirListaDiretorio(listaDiretorio: TListaDiretorio;
          abaobj: TAbaObjeto; sCaminho: String);
var
  i: integer;
  diretorio: TDiretorioObjeto;
begin
  for i := listaDiretorio.Count - 1 downto 0 do
  begin
    diretorio := listaDiretorio.items(i);
    if (diretorio.aba.codigo = abaobj.codigo) then
    begin
      if Length(Trim(sCaminho)) > 0 then begin
        if AnsiStartsStr(sCaminho, diretorio.caminho) then begin
          listaDiretorio.Delete(i);
        end;
      end else begin
        listaDiretorio.Delete(i);
      end;
    end;
  end;
end;

function TDiretorio.diretorioToCSV(diretorio: TDiretorioObjeto): string;
var sCSV: string;
begin
  sCSV:='"';

  with diretorio do
  begin
    sCSV := sCSV + aba.nome + '";"';
    sCSV := sCSV + nome + '";"';
    sCSV := sCSV + IntToStr(tamanho) + '";"';
    sCSV := sCSV + tamanhoFormatado + '";"';
    sCSV := sCSV + tipo.nome + '";"';
    sCSV := sCSV + modificadoFormatado + '";"';
    sCSV := sCSV + atributos + '";"';
    sCSV := sCSV + caminho + '"';
  end;
  result:=sCSV;
end;

function TDiretorio.diretorioToXML(diretorio: TDiretorioObjeto): string;
var sXML, sCR, sTAB, sTAB2: string;
begin
  sTAB:=chr(9);
  sTAB2:=chr(9)+chr(9);
  sCR:=chr(13)+chr(10);

  sXML:=sTAB + '<arquivo>' + sCR;

  with diretorio do
  begin
    sXML := sXML + sTAB2 + '<aba>' + IntToStr(aba.codigo) + '</aba>' + sCR;
    sXML := sXML + sTAB2 + '<nomeAba>' + aba.nome + '</nomeAba>' + sCR;
    sXML := sXML + sTAB2 + '<codigo>' + IntToStr(codigo) + '</codigo>' + sCR;
    sXML := sXML + sTAB2 + '<ordem>' + IntToStr(ordem) + '</ordem>' + sCR;
    sXML := sXML + sTAB2 + '<nome>' + nome + '</nome>' + sCR;
    sXML := sXML + sTAB2 + '<tamanho>' + IntToStr(tamanho) + '</tamanho>' + sCR;
    sXML := sXML + sTAB2 + '<tipo>' + tipo.codigo + '</tipo>' + sCR;
    sXML := sXML + sTAB2 + '<modificado>' + modificadoFormatado + '</modificado>' + sCR;
    sXML := sXML + sTAB2 + '<atributos>' + atributos + '</atributos>' + sCR;
    sXML := sXML + sTAB2 + '<codDirPai>' + IntToStr(codDirPai) + '</codDirPai>' + sCR;
    sXML := sXML + sTAB2 + '<caminho>' + caminho + '</caminho>' + sCR;
  end;

  sXML := sXML + sTAB + '</arquivo>';

  result:=sXML;
end;

function TDiretorio.diretorioToTXT(diretorio: TDiretorioObjeto): string;
var sTXT, sTAB: string;
begin
  sTAB:=chr(9);
  sTXT:='';
  with diretorio do
  begin
    sTXT := sTXT + aba.nome + sTAB;
    sTXT := sTXT + nome + sTAB;
    sTXT := sTXT + IntToStr(tamanho) + sTAB;
    sTXT := sTXT + tamanhoFormatado + sTAB;
    sTXT := sTXT + tipo.nome + sTAB;
    sTXT := sTXT + modificadoFormatado + sTAB;
    sTXT := sTXT + atributos + sTAB;
    sTXT := sTXT + caminho;
  end;
  result:=sTXT;
end;

function TDiretorio.diretorioToHTML(diretorio: TDiretorioObjeto): string;
var sHTML, sCR, sTAB, sTAB2: string;
begin
  sTAB:=chr(9);
  sTAB2:=chr(9)+chr(9);
  sCR:=chr(13)+chr(10);

  sHTML := sTAB + '<tr>' + sCR;

  with diretorio do
  begin
    sHTML := sHTML + sTAB2 + '<td>' + aba.nome + '</td>' + sCR;
    sHTML := sHTML + sTAB2 + '<td>' + nome + '</td>' + sCR;
    sHTML := sHTML + sTAB2 + '<td>' + IntToStr(tamanho) + '</td>' + sCR;
    sHTML := sHTML + sTAB2 + '<td>' +
      StringReplace(tamanhoFormatado,' ','&nbsp;',
      [rfReplaceAll, rfIgnoreCase]) + '</td>' + sCR;
    sHTML := sHTML + sTAB2 + '<td>' + tipo.nome + '</td>' + sCR;
    sHTML := sHTML + sTAB2 + '<td>' +
      StringReplace(modificadoFormatado,' ','&nbsp;',
      [rfReplaceAll, rfIgnoreCase]) + '</td>' + sCR;
    sHTML := sHTML + sTAB2 + '<td>' + atributos + '</td>' + sCR;
    sHTML := sHTML + sTAB2 + '<td>' + caminho + '</td>' + sCR;
  end;
  sHTML := sHTML + sTAB + '</tr>';
  result:=sHTML;
end;

procedure TDiretorio.exportarDiretorio(tipoexp: TTipoExportar; abaobj: TAbaObjeto;
  sNomeArquivo :String; progressoLog: TProgressoLog);
var sTexto, sCR, sTAB, sTAB2, sSQL: string;
  abaLocal: TAba;
  diretorio: TDiretorioObjeto;
  i: integer;
  listaLocal: TStringList;
  listaDiretorio: TListaDiretorio;
begin
  sTAB:=chr(9);
  sTAB2:=chr(9)+chr(9);
  sCR:=chr(13)+chr(10);

  listaDiretorio:=TListaDiretorio.Create;
  sSQL:=SQL_CONSULTA_ARQUIVO +
  ' where aba='+ IntToStr(abaobj.codigo) +' order by 1, 2, 3';
  carregarDiretorio(sSQL, listaDiretorio, progressoLog);

  listaLocal:=TStringList.Create;
  try
    case tipoexp of
      teCSV: begin
        sTexto:='"Aba";"Nome";"TamanhoBytes";"Tamanho";"Tipo";"Modificado";"Atributos";"Caminho"';
      end;
      teHTML: begin
        sTexto:='<!DOCTYPE html>' + sCR;
        sTexto := sTexto + '<html>' + sCR;
        sTexto := sTexto + '<body>' + sCR;
        sTexto := sTexto + '<table border="1" cellpadding="5" cellspacing="0">' + sCR;
        sTexto := sTexto + sTAB + '<tr>' + sCR;
        sTexto := sTexto + sTAB2 + '<th>Aba</th>' + sCR;
        sTexto := sTexto + sTAB2 + '<th>Nome</th>' + sCR;
        sTexto := sTexto + sTAB2 + '<th>Tamanho</th>' + sCR;
        sTexto := sTexto + sTAB2 + '<th>Tamanho Formatado</th>' + sCR;
        sTexto := sTexto + sTAB2 + '<th>Tipo</th>' + sCR;
        sTexto := sTexto + sTAB2 + '<th>Modificado</th>' + sCR;
        sTexto := sTexto + sTAB2 + '<th>Atributos</th>' + sCR;
        sTexto := sTexto + sTAB2 + '<th>Caminho</th>' + sCR;
        sTexto := sTexto + sTAB + '</tr>';
      end;
      teXML: begin
        sTexto:='<diretorio>';
      end;
      teSQL: begin
        abaLocal:=TAba.Create;
        abaLocal.codigo:=listaDiretorio.Items(0).aba.codigo;
        abaLocal.nome:=listaDiretorio.Items(0).aba.nome;
        sTexto:=cAba.abaToSQL(abaLocal);
      end;
    end;
    listaLocal.Append(sTexto);

    for i := 0 to listaDiretorio.Count - 1 do begin
      diretorio := listaDiretorio.Items(i);
      if (diretorio.aba.codigo = abaobj.codigo) then begin
        case tipoexp of
          teTXT: sTexto:=diretorioToTXT(diretorio);
          teCSV: sTexto:=diretorioToCSV(diretorio);
          teHTML: sTexto:=diretorioToHTML(diretorio);
          teXML: sTexto:=diretorioToXML(diretorio);
          teSQL: sTexto:=diretorioToSQL(diretorio, true)+';';
        end;
        listaLocal.Append(sTexto);
      end;
    end;

    case tipoexp of
      teHTML: begin
        sTexto := sTexto + sCR + '</table>' + sCR;
        sTexto := sTexto + '</body>' + sCR;
        sTexto := sTexto + '</html>' + sCR;
      end;
      teXML: begin
        sTexto:='</diretorio>';
      end;
    end;
    listaLocal.Append(sTexto);

    listaLocal.SaveToFile(sNomeArquivo);
  finally
    listaDiretorio.Free;
    listaLocal.Free;
  end;
end;


function TDiretorio.XMLParaDiretorio(sTexto: string; nArquivo: Integer;
  var diretorio: TDiretorioObjeto): Integer;
var
  sTagInicio: string;
  sValor: string;
  sTagFim: string;
begin
  result:=nArquivo;

  if Pos('>', sTexto) > 0 then
    sTagInicio := Copy(sTexto, 1, Pos('>', sTexto));
  if (Pos('>', sTexto) > 0) and (Pos('</', sTexto) > 1) then
      sValor := copy(sTexto, Pos('>', sTexto) + 1,
                Pos('</', sTexto) - Pos('>', sTexto) - 1);
  if LastDelimiter('>', sTexto) > 0 then
    sTagFim := Copy(sTexto, LastDelimiter('<', sTexto), LastDelimiter('>', sTexto));

  if (nArquivo = 1) and (sTagInicio <> '<arquivo>') then
  begin
    result := -1;
  end;
  if (nArquivo = 2) and (sTagInicio <> '<aba>') and (sTagFim <> '</aba>') then
  begin
    //diretorio.aba.codigo := StrToInt(sValor);
    result := -1;
  end;
  if (nArquivo = 3) and (sTagInicio <> '<nomeAba>') and (sTagFim <> '</nomeAba>') then
  begin
    //diretorio.aba.nome := sValor;
    result := -1;
  end;
  if (nArquivo = 4) and (sTagInicio = '<codigo>') and (sTagFim = '</codigo>') then
  begin
    diretorio.codigo := StrToInt(sValor);
  end;
  if (nArquivo = 5) and (sTagInicio = '<ordem>') and (sTagFim = '</ordem>') then
  begin
    diretorio.ordem := StrToInt(sValor);
  end;
  if (nArquivo = 6) and (sTagInicio = '<nome>') and (sTagFim = '</nome>') then
  begin
    diretorio.nome := sValor;
  end;
  if (nArquivo = 7) and (sTagInicio = '<tamanho>') and (sTagFim = '</tamanho>') then
  begin
    diretorio.tamanho := StrToInt64(sValor);
  end;
  if (nArquivo = 8) and (sTagInicio = '<tipo>') and (sTagFim = '</tipo>') then
  begin
    diretorio.tipo.codigo := sValor;
  end;
  if (nArquivo = 9) and (sTagInicio = '<modificado>') and (sTagFim = '</modificado>') then
  begin
    diretorio.modificado := StrToDateTime(sValor);
    diretorio.modificadoFormatado := sValor;
  end;
  if (nArquivo = 10) and (sTagInicio = '<atributos>') and (sTagFim = '</atributos>') then
  begin
    diretorio.atributos := sValor;
  end;
  if (nArquivo = 11) and (sTagInicio = '<codDirPai>') and (sTagFim = '</codDirPai>') then
  begin
    diretorio.codDirPai := StrToInt(sValor);
  end;
  if (nArquivo = 12) and (sTagInicio = '<caminho>') and (sTagFim = '</caminho>') then
  begin
    diretorio.caminho := sValor;
  end;
  if (nArquivo = 13) and (sTagInicio <> '</arquivo>') then
  begin
    result := -1;
  end;
  if (sTagInicio = '</diretorio>') then
  begin
      result := -3;
  end;

end;

function TDiretorio.importarDiretorioViaXML(abaobj: TAbaObjeto; sNomeArquivo:String;
  listaDirPai: TListaDiretorio; log: TStrings; progressoLog: TProgressoLog): integer;
var sTexto: string;
  i, nArquivo: integer;
  listaLocal: TStringList;
  diretorio: TDiretorioObjeto;
  listaDiretorio: TListaDiretorio;
begin
  result:=0;

  diretorio := TDiretorio.Create;
  listaDiretorio:=TListaDiretorio.Create;
  listaLocal:=TStringList.Create;
  listaLocal.LoadFromFile(sNomeArquivo);
  try
    if Trim(listaLocal.Strings[0])<>'<diretorio>' then
      result:=-1
    else begin
      nArquivo:=0;
      for i := 0 to listaLocal.Count - 1 do begin
        sTexto := Trim(listaLocal.Strings[i]);
        nArquivo:=XMLParaDiretorio(sTexto, nArquivo, diretorio);

        if nArquivo=-1 then begin
          result:=-1;
          break;
        end else if nArquivo = 13 then begin
          nArquivo := 1;
          diretorio.aba.codigo:=abaobj.codigo;
          listaDiretorio.Add(diretorio);

          if verificaCodDir(abaobj.codigo,
            diretorio.caminho, listaDirPai) then begin
            result:=-2;
            break;
          end;

          diretorio := TDiretorio.Create;

        end else if nArquivo = -3 then
        begin
          result := nArquivo;
        end
        else
          Inc(nArquivo);

      end;
    end;

    salvarDiretorio(listaDiretorio, log, progressoLog);

  finally
    listaDiretorio.Free;
    listaLocal.Free;
  end;
end;

function TDiretorio.carregarSubDiretorios(sDiretorio: String; listaLocal: TStringList): boolean;
var
  SearchRec : TSearchRec;
  sCaminho, sSeparador: String;
begin
  if Copy(sDiretorio,Length(sDiretorio),1)=BARRA_NORMAL then
    sSeparador := ''
  else
    sSeparador := BARRA_NORMAL;

  sCaminho:=sDiretorio+sSeparador+'*.*';
  if FindFirst(sCaminho,faDirectory,SearchRec) = 0 then begin

    while FindNext(SearchRec) = 0 do begin
      sCaminho:=sDiretorio+sSeparador+SearchRec.Name;

      if SearchRec.Attr=faDirectory then begin
        if DirectoryExists(sCaminho) then begin
          if (SearchRec.Name<>'.') and (SearchRec.Name<>'..') then begin
              listaLocal.Add(sCaminho);
          end;
        end;
      end;
    end;
  end;
  FindClose(SearchRec);

  result:=(listaLocal.Count > 0);
end;

function TDiretorio.carregarArquivos(sDiretorio: String; listaLocal: TStringList): boolean;
var
  SearchRec : TSearchRec;
  sCaminho, sSeparador: String;
begin
  if Copy(sDiretorio,Length(sDiretorio),1)=BARRA_NORMAL then
    sSeparador := ''
  else
    sSeparador := BARRA_NORMAL;

  sCaminho:=sDiretorio+sSeparador+'*.*';
  if FindFirst(sCaminho,faArchive,SearchRec) = 0 then begin

    while FindNext(SearchRec) = 0 do begin
      sCaminho:=sDiretorio+sSeparador+SearchRec.Name;

      if SearchRec.Attr=faArchive then begin
        if FileExists(sCaminho) then begin
          if (SearchRec.Name<>'.') and (SearchRec.Name<>'..') then begin
              listaLocal.Add(sCaminho);
          end;
        end;
      end;
    end;
  end;
  FindClose(SearchRec);

  result:=(listaLocal.Count > 0);
end;

function TDiretorio.carregarTodosArquivos(sDiretorio: String;
  listaLocal: TStringList): boolean;
var
  SearchRec : TSearchRec;
  sCaminho, sSeparador: String;
begin
  if Copy(sDiretorio,Length(sDiretorio),1)=BARRA_NORMAL then
    sSeparador := ''
  else
    sSeparador := BARRA_NORMAL;

  sCaminho:=sDiretorio+sSeparador+'*.*';
  if FindFirst(sCaminho,faAnyFile,SearchRec) = 0 then begin
    sCaminho:=sDiretorio+sSeparador+SearchRec.Name;

    if FileExists(sCaminho) then begin
      listaLocal.Add(sCaminho);
    end else if DirectoryExists(sCaminho) then begin
      if (SearchRec.Name<>'.') and (SearchRec.Name<>'..') then begin
        carregarTodosArquivos(sCaminho, listaLocal);
      end;
    end;

    while FindNext(SearchRec) = 0 do begin
      sCaminho:=sDiretorio+sSeparador+SearchRec.Name;

      if FileExists(sCaminho) then begin
        listaLocal.Add(sCaminho);
      end else if DirectoryExists(sCaminho) then begin
        if (SearchRec.Name<>'.') and (SearchRec.Name<>'..') then begin
          carregarTodosArquivos(sCaminho, listaLocal);
        end;
      end;

    end;
  end;
  FindClose(SearchRec);

  result:=(listaLocal.Count > 0);
end;

end.
