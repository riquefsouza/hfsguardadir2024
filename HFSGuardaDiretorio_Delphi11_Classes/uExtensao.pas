unit uExtensao;

interface

uses
  System.Classes, System.SysUtils, System.StrUtils, System.Generics.Collections,
  Vcl.ComCtrls, Data.DB, uDataModule, Vcl.Graphics, Vcl.Controls, uDiretorio,
  Vcl.Imaging.GIFImg, Vcl.Imaging.Jpeg, Vcl.Imaging.PNGImage,
  Vcl.Dialogs, System.UITypes, uRotinas;

type
  TExtensao = class
  private
    { Private declarations }
  public
    { Public declarations }
    codigo: integer;
    nome: String;
    ordem: integer;
    bmp16: Vcl.Graphics.TBitmap;
    bmp32: Vcl.Graphics.TBitmap;

    procedure carregarExtensao(listaExtensao: TList<TExtensao>; progressoLog: TProgressoLog);
    function existeExtensao(sExtensao: String;
       listaLocal: TList<TExtensao>): boolean;
    function retMaxCodExtensao(listaLocal: TList<TExtensao>): integer;
    function SalvarExtensao(listaExtensao: TList<TExtensao>;
      sNomeDiretorio, sCaminhoOriginal: String; log: TStrings): boolean;
    procedure salvarExtensoes(listaDiretorio: TList<TDiretorio>;
      listaExtensao: TList<TExtensao>; log: TStrings; progressoLog: TProgressoLog);
    function extensaoToSQL(extensao: TExtensao; bInsert: boolean): String;
    function excluirExtensao(listaExtensao: TList<TExtensao>;
      codigo: integer): boolean;
    function excluirTodasExtensoes(listaExtensao: TList<TExtensao>): boolean;
    function criarTabelaExtensoes:boolean;
    procedure incluirExtensao(extensao: TExtensao);
    procedure carregarExtensoes(lista: TList<TExtensao>;
      listaImg16, listaImg32: TImageList);
    function indiceExtensao(lista: TList<TExtensao>; nomeExtensao: String): integer;
    procedure ExportarExtensao(tipo: TTipoExportarExtensao;
      listaExtensao: TList<TExtensao>);
    function pegaExtensaoPorOrdem(lista: TList<TExtensao>; ordem: Integer):
      TExtensao;
    procedure ImportarExtensao(caminho: String; listaExtensao: TList<TExtensao>);
    procedure ExtrairExtensao(caminho: String; listaExtensao: TList<TExtensao>);
  end;

var
  cExtensao: TExtensao;

implementation

function TExtensao.criarTabelaExtensoes:boolean;
var sSQL: String;
begin
  sSQL:='create table IF NOT EXISTS Extensoes('+
  'cod integer not null,'+
  'nome varchar(20) not null,'+
  'bmp16 BLOB COLLATE NOCASE null,'+
  'bmp32 BLOB COLLATE NOCASE null,'+
  'primary key (cod))';
  result:=Rotinas.execConsulta(sSQL, False);
end;

function TExtensao.extensaoToSQL(extensao: TExtensao; bInsert: boolean): String;
var sSQL: String;
begin
  if bInsert then begin
    sSQL:='insert into Extensoes(cod, nome) values(';
  end;

  with extensao do
  begin
    sSQL := sSQL + IntToStr(codigo) + ',';
    sSQL := sSQL + QuotedStr(nome);

    if bInsert then
      sSQL := sSQL + ')';
  end;
  result:=sSQL;
end;

procedure TExtensao.incluirExtensao(extensao: TExtensao);
var sSQL: String;
  ms: TMemoryStream;
begin
  sSQL:=extensaoToSQL(extensao, True);
  Rotinas.execConsulta(sSQL, False);

  ms := TMemoryStream.Create;
	try
    extensao.bmp16.SaveToStream(ms);
    ms.Position := 0;
   	dm.conexao.UpdateBlob(AnsiString('UPDATE Extensoes set bmp16=? WHERE cod=' +
      IntToStr(extensao.codigo)), ms);
	finally
    ms.Free;
	end;

  ms := TMemoryStream.Create;
	try
    extensao.bmp32.SaveToStream(ms);
    ms.Position := 0;
   	dm.conexao.UpdateBlob(AnsiString('UPDATE Extensoes set bmp32=? WHERE cod=' +
      IntToStr(extensao.codigo)), ms);
	finally
    ms.Free;
	end;

end;

procedure TExtensao.carregarExtensao(listaExtensao: TList<TExtensao>; progressoLog: TProgressoLog);
var
  Extensao: TExtensao;
  i, total: integer;
  msBMP16, msBMP32: TMemoryStream;
  pb: TProgresso;
begin
  listaExtensao.Clear;

  dm.tabelaExtensoes:=dm.conexao.GetTable(AnsiString(dm.SQLExtensoes));
  total := dm.tabelaExtensoes.Count;
  dm.tabelaExtensoes.MoveFirst;

  if total > 0 then begin
    pb.minimo := 0;
    pb.maximo := total - 1;
    pb.posicao := 0;
    pb.passo := 1;

    for i := 0 to total - 1 do begin
      Extensao:=TExtensao.Create;

      with Extensao do begin
        codigo := dm.tabelaExtensoes.FieldAsInteger(dm.tabelaExtensoes.FieldIndex['cod']);
        nome := dm.tabelaExtensoes.FieldAsString(dm.tabelaExtensoes.FieldIndex['nome']);

        msBMP16 := dm.tabelaExtensoes.FieldAsBlob(dm.tabelaExtensoes.FieldIndex['bmp16']);
        bmp16 := Rotinas.StreamParaBMP(msBMP16);
        msBMP16.Free;

        msBMP32 := dm.tabelaExtensoes.FieldAsBlob(dm.tabelaExtensoes.FieldIndex['bmp32']);
        bmp32 := Rotinas.StreamParaBMP(msBMP32);
        msBMP32.Free;

        ordem:=(i+1);
      end;

      listaExtensao.Add(Extensao);

      dm.tabelaExtensoes.Next;

      pb.posicao := i;

      if Assigned(progressoLog) then begin
        progressoLog(pb);
      end;

    end;
  end;

end;

function TExtensao.existeExtensao(sExtensao: String;
  listaLocal: TList<TExtensao>): boolean;
var i: integer;
  extensao: TExtensao;
begin
  result:=false;

  if Length(Trim(sExtensao)) > 0 then begin
    for i := 0 to listaLocal.Count - 1 do begin
      extensao := listaLocal.Items[i];
      if LowerCase(Trim(extensao.nome)) = LowerCase(Trim(sExtensao)) then begin
         result:=true;
         break;
      end;
    end;
  end;

end;

function TExtensao.retMaxCodExtensao(listaLocal: TList<TExtensao>): integer;
var i, nMaior: integer;
  extensao: TExtensao;
begin
  nMaior:=0;

  for i := 0 to listaLocal.Count - 1 do begin
    extensao := listaLocal.Items[i];
    if (extensao.codigo > nMaior) then begin
       nMaior:=extensao.codigo;
    end;
  end;

  result:=nMaior+1;
end;

function TExtensao.SalvarExtensao(listaExtensao: TList<TExtensao>;
  sNomeDiretorio, sCaminhoOriginal: string; log: TStrings): boolean;
var
  sExtensao: string;
  extensao: TExtensao;
  icone: TIcon;
begin
  result:=false;

  if LastDelimiter('.', sNomeDiretorio) > 0 then begin
    sExtensao := Copy(sNomeDiretorio, LastDelimiter('.', sNomeDiretorio) + 1,
      Length(sNomeDiretorio));
    if not existeExtensao(sExtensao, listaExtensao) then begin
      extensao:=TExtensao.Create;
      extensao.codigo := retMaxCodExtensao(listaExtensao);
      extensao.nome := LowerCase(sExtensao);
      icone := Rotinas.extrairIconeArquivo(sCaminhoOriginal);
      extensao.bmp32 := Rotinas.IconeParaBmp(icone, 32);
      extensao.bmp16 := Rotinas.RedimensionarBMP(extensao.bmp32, 16);
      incluirExtensao(extensao);
      listaExtensao.Add(extensao);
      log.Append('Salvando Extens�o: '+extensao.nome);
      result:=true;
    end;
  end;
end;

procedure TExtensao.salvarExtensoes(listaDiretorio: TList<TDiretorio>;
  listaExtensao: TList<TExtensao>; log: TStrings; progressoLog: TProgressoLog);
var
  diretorio: TDiretorio;
  i: integer;
  pb: TProgresso;
begin
  pb.minimo := 0;
  pb.maximo := listaDiretorio.Count - 1;
  pb.posicao := 0;
  pb.passo := 1;

  dm.conexao.BeginTransaction;
  for i := 0 to listaDiretorio.Count - 1 do begin
    diretorio := listaDiretorio.Items[i];

    if diretorio.tipo.codigo='A' then begin
      SalvarExtensao(listaExtensao, diretorio.nome,
        diretorio.caminhoOriginal, log);
    end;

    pb.posicao := i;

    if Assigned(progressoLog) then begin
      progressoLog(pb);
    end;

  end;
  dm.conexao.Commit;

end;

function TExtensao.excluirExtensao(listaExtensao: TList<TExtensao>;
  codigo: integer): boolean;
var sSQL: String;
 extensao: TExtensao;
 i: integer;
begin
  sSQL:='delete from Extensoes where cod='+inttostr(codigo);
  if Rotinas.execConsulta(sSQL, True) then begin

    for i := 0 to listaExtensao.Count - 1 do begin
      extensao := listaExtensao.Items[i];
      if extensao.codigo = codigo then begin
         listaExtensao.Delete(i);
         break;
      end;
    end;
    result:=true;
  end else begin
    result:=false;
  end;
end;

function TExtensao.excluirTodasExtensoes(listaExtensao: TList<TExtensao>): boolean;
var sSQL: String;
begin
  sSQL:='delete from Extensoes';
  if Rotinas.execConsulta(sSQL, True) then begin
    listaExtensao.Clear;
    result:=true;
  end else begin
    result:=false;
  end;
end;

procedure TExtensao.carregarExtensoes(lista: TList<TExtensao>;
  listaImg16, listaImg32: TImageList);
var i: integer;
 extensao: TExtensao;
begin
  for i := 0 to lista.Count - 1 do begin
    extensao := lista.Items[i];
    listaImg16.Add(extensao.bmp16, nil);
    listaImg32.Add(extensao.bmp32, nil);
  end;
end;

function TExtensao.indiceExtensao(lista: TList<TExtensao>; nomeExtensao: String): integer;
var i: integer;
 extensao: TExtensao;
begin
  result:=-1;
  nomeExtensao := Copy(nomeExtensao,
    LastDelimiter('.', nomeExtensao)+1, Length(nomeExtensao));

  for i := 0 to lista.Count - 1 do begin
    extensao := lista.Items[i];
    if LowerCase(Trim(extensao.nome)) = LowerCase(Trim(nomeExtensao)) then begin
       result:=extensao.ordem+1;
       break;
    end;
  end;
end;

procedure TExtensao.ImportarExtensao(caminho: String; listaExtensao: TList<TExtensao>);
var listaArquivos: TStringList;
  i: integer;
  extensao: TExtensao;
  sExtensao, sArquivo: String;
  tipo: TTipoExportarExtensao;
  bmp: Vcl.Graphics.TBitmap;
begin
  listaArquivos:= TStringList.Create;
  try
    if cDiretorio.carregarArquivos(caminho, listaArquivos) then begin

       dm.conexao.BeginTransaction;
       for i := 0 to listaArquivos.Count - 1 do begin
          sArquivo:=listaArquivos.Strings[i];
          sExtensao := Copy(sArquivo, LastDelimiter(BARRA_NORMAL, sArquivo)+1,
            Length(sArquivo));
          sExtensao := Copy(sExtensao, 1, Pos('.', sExtensao)-1);

          if not existeExtensao(sExtensao, listaExtensao) then begin
            bmp:=Vcl.Graphics.TBitmap.Create;
            tipo:=Rotinas.DetectImage(sArquivo, bmp);

            if tipo<>teNUL then begin
              extensao:=TExtensao.Create;
              extensao.codigo := retMaxCodExtensao(listaExtensao);
              extensao.nome := LowerCase(sExtensao);
              extensao.bmp32 := Rotinas.RedimensionarBMP(bmp, 32);
              extensao.bmp16 := Rotinas.RedimensionarBMP(bmp, 16);

              incluirExtensao(extensao);
              listaExtensao.Add(extensao);
            end;
          end;
       end;
       dm.conexao.Commit;

    end;
  finally
    listaArquivos.Free;
  end;

end;

procedure TExtensao.ExtrairExtensao(caminho: String; listaExtensao: TList<TExtensao>);
var listaArquivos: TStringList;
  i: integer;
  sArquivo: String;
  log: TStringList;
begin
  listaArquivos:= TStringList.Create;
  log:=TStringList.Create;
  try
    if cDiretorio.carregarTodosArquivos(caminho, listaArquivos) then begin

       dm.conexao.BeginTransaction;
       for i := 0 to listaArquivos.Count - 1 do begin
          sArquivo:=listaArquivos.Strings[i];
          SalvarExtensao(listaExtensao, ExtractFileName(sArquivo),
            sArquivo, log);
       end;
       dm.conexao.Commit;

    end;
  finally
    listaArquivos.Free;
    log.Free;
  end;

end;

procedure TExtensao.ExportarExtensao(tipo: TTipoExportarExtensao;
  listaExtensao: TList<TExtensao>);
var sCaminho, sImg16, sImg32, sExtensao: String;
  i: integer;
  extensao: TExtensao;
  icone: TIcon;
  gifImagem: TGIFImage;
  jpgImagem: TJPEGImage;
  pngImagem: TPngImage;
begin
  if listaExtensao.Count > 0 then begin
    sCaminho:=ExtractFilePath(ParamStr(0));

      case tipo of
        teBMP: sExtensao:='.bmp';
        teICO: sExtensao:='.ico';
        teGIF: sExtensao:='.gif';
        teJPG: sExtensao:='.jpg';
        tePNG: sExtensao:='.png';
        teTIF: sExtensao:='.tif';
      end;

    for i := 0 to listaExtensao.Count - 1 do begin
      extensao := listaExtensao.Items[i];

      sImg16:=sCaminho+extensao.nome+'16'+sExtensao;
      if FileExists(sImg16) then
        DeleteFile(sImg16);

      sImg32:=sCaminho+extensao.nome+'32'+sExtensao;;
      if FileExists(sImg32) then
        DeleteFile(sImg32);

      case tipo of
        teBMP: begin
          extensao.bmp16.SaveToFile(sImg16);
          extensao.bmp32.SaveToFile(sImg32);
        end;
        teICO: begin
          icone:=Rotinas.BmpParaIcone(extensao.bmp16);
          icone.SaveToFile(sImg16);
          icone.Free;

          icone:=Rotinas.BmpParaIcone(extensao.bmp32);
          icone.SaveToFile(sImg32);
          icone.Free;
        end;
        teGIF: begin
          gifImagem:=Rotinas.BmpParaGIF(extensao.bmp16);
          gifImagem.SaveToFile(sImg16);
          gifImagem.Free;

          gifImagem:=Rotinas.BmpParaGIF(extensao.bmp32);
          gifImagem.SaveToFile(sImg32);
          gifImagem.Free;
        end;
        teJPG: begin
          jpgImagem:=Rotinas.BmpParaJPG(extensao.bmp16);
          jpgImagem.SaveToFile(sImg16);
          jpgImagem.Free;

          jpgImagem:=Rotinas.BmpParaJPG(extensao.bmp32);
          jpgImagem.SaveToFile(sImg32);
          jpgImagem.Free;
        end;
        tePNG: begin
          pngImagem:=Rotinas.BmpParaPNG(extensao.bmp16);
          pngImagem.SaveToFile(sImg16);
          pngImagem.Free;

          pngImagem:=Rotinas.BmpParaPNG(extensao.bmp32);
          pngImagem.SaveToFile(sImg32);
          pngImagem.Free;
        end;
        teTIF: begin
          Rotinas.BMPParaTIF(extensao.bmp16, sImg16);
          Rotinas.BMPParaTIF(extensao.bmp32, sImg32);
        end;
      end;

    end;
    MessageDlg('�cones salvos no mesmo diret�rio do sistema!',
      mtInformation, [mbOk], 0);
  end;
end;

function TExtensao.pegaExtensaoPorOrdem(lista: TList<TExtensao>; ordem: Integer):
  TExtensao;
var i: integer;
 extensao: TExtensao;
begin
  result:=nil;

  for i := 0 to lista.Count - 1 do begin
    extensao := lista.Items[i];
    if extensao.ordem = ordem then begin
       result:=extensao;
       break;
    end;
  end;
end;


end.
