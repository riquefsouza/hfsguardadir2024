unit uRotinas;

{$mode objfpc}{$H+}

interface

uses
 Classes, SysUtils, Graphics, SQLiteTable3, uDataModule, Math, DateUtils,
 Controls, LCLIntf, LCLType, FileUtil, ShellApi;

const
  BARRA_NORMAL: Char = '\';
  BARRA_INVERTIDA: Char = '/';

type
  TTipoExportarExtensao = (teNUL, teBMP, teICO, teGIF, teJPG, tePNG, teTIF);

  TProgresso = record
    minimo: Integer;
    maximo: Integer;
    posicao: Integer;
    passo : Integer;
  end;

  TProgressoLog = procedure(progresso: TProgresso) of object;

  TRotinas = class
  private
    { Private declarations }
  public
    { Public declarations }
    function criarVisao(visao: String):boolean;
    function execConsulta(sSQL: String; bComTransacao: Boolean): boolean;
    function atribuirParamsConexao: Boolean;
    function extrairIconeArquivo(sNomeArquivo: String): TIcon;
    function IconeParaBmp( Icone: TIcon; nTamanho: integer ):  Graphics.TBitmap;
    function BmpParaIcone( Bitmap:  Graphics.TBitmap ): TIcon;
    function BMPParaGIF(bmp: Graphics.TBitmap): TGIFImage;
    function GIFParaBMP(gif: TGIFImage; nTamanho: integer): Graphics.TBitmap;
    function BMPParaJPG(bmp: Graphics.TBitmap): TJPEGImage;
    function JPGParaBMP(jpg: TJPEGImage; nTamanho: integer): Graphics.TBitmap;
    function BMPParaPNG(bmp: Graphics.TBitmap): TPortableNetworkGraphic;
    function PNGParaBMP(png: TPortableNetworkGraphic; nTamanho: integer): Graphics.TBitmap;
    function BMPParaTIF(bmp: Graphics.TBitmap): TTiffImage;
    function DetectImage(const InputFileName: string; BM: Graphics.TBitmap):
      TTipoExportarExtensao;
    function StreamParaIcone(ms: TMemoryStream): TIcon;
    function StreamParaGIF(ms: TMemoryStream): TGIFImage;
    function StreamParaJPG(ms: TMemoryStream): TJPEGImage;
    function JPGParaStream(imagem: TJPEGImage): TMemoryStream;
    function RedimensionarBMP( imagem: Graphics.TBitmap;
      nTamanho: integer):  Graphics.TBitmap;
    function StreamParaBMP(ms: TMemoryStream): Graphics.TBitmap;
    function CompareTextAsInteger(const s1, s2: string): Integer;
    function CompareTextAsDateTime(const s1, s2: string): Integer;
  end;

var
  Rotinas: TRotinas;

implementation

uses uDiretorio, uExtensao, uAba;

function TRotinas.execConsulta(sSQL: String; bComTransacao: Boolean): boolean;
begin
  if bComTransacao then begin
    dm.conexao.BeginTransaction;
  end;

  dm.conexao.ExecSQL(AnsiString(sSQL));

  if bComTransacao then begin
    dm.conexao.Commit;
  end;

  result:=True;
end;

function TRotinas.atribuirParamsConexao: Boolean;
var sDLL, sBanco: String;
 aba: TAba;
begin
  sDLL:=ExtractFilePath(ParamStr(0)) + 'sqlite3.dll';

  if FileExists(sDLL) then begin
    sBanco:=ExtractFilePath(ParamStr(0)) + 'GuardaDir.db';

    dm.conexao := TSQLiteDatabase.Create(sBanco);

    if not FileExists(sBanco) then begin

       cAba.criarTabelaAbas;

       aba:=TAba.Create;
       aba.codigo:=1;
       aba.nome:='DVD';
       cAba.incluirAba(aba);

       cExtensao.criarTabelaExtensoes;
       cDiretorio.criarTabelaDiretorios;
       Rotinas.criarVisao('consultadirpai');
       Rotinas.criarVisao('consultadirfilho');
       Rotinas.criarVisao('consultaarquivo');
    end;

    result:=True;
  end else
    result:=False;
end;

function TRotinas.extrairIconeArquivo(sNomeArquivo: String): TIcon;
var
  icone: TIcon;
  filtro: ^Word;
begin
  New(filtro);
  filtro^:=0;
  icone:=TIcon.Create;
  icone.Handle:=ExtractAssociatedIcon(hInstance, PChar(sNomeArquivo), filtro);
  result:=icone;
end;

function TRotinas.criarVisao(visao: String):boolean;
var sSQL: string;
begin
  sSQL:='create view '+visao+' as '+
  'SELECT d.aba,d.cod,d.ordem,d.coddirpai,d.nome,d.tam,d.tipo,d.modificado,'+
  'd.atributos,d.caminho'+
  ',(select nome as nomeaba from Abas where cod=d.aba) as nomeaba'+
  ',(select nome as nomepai from Diretorios where cod=d.cod '+
  '  and ordem=d.coddirpai and aba=d.aba) as nomepai'+
  ',(select caminho as caminhopai from Diretorios where cod=d.cod '+
  ' and ordem=d.coddirpai and aba=d.aba) as caminhopai '+
  'FROM Diretorios d ';

  if visao='consultadirpai' then
    sSQL:=sSQL+'where d.tipo=''D'' and d.coddirpai = 0'
  else if visao='consultadirfilho' then
    sSQL:=sSQL+'where d.tipo=''D'' and d.coddirpai > 0';

  result:=execConsulta(sSQL, False);
end;

function TRotinas.IconeParaBmp( Icone: TIcon; nTamanho: integer):  Graphics.TBitmap;
var
//  IconInfo: TIconInfo;
  bmp: Graphics.TBitmap;
begin
  //GetIconInfo( Icone.Handle, IconInfo );
  bmp:=Graphics.TBitmap.Create;
  //bmp.Width := ( IconInfo.xHotspot * 2 );
  //bmp.Height := ( IconInfo.yHotspot * 2 );
  bmp.Width:=nTamanho;
  bmp.Height:=nTamanho;
// para salvar bmp com formato de 256 cores
//  bmp.PixelFormat := pf8bit;
//  bmp.PixelFormat := pfDevice;
//  bmp.Transparent := True;
//  bmp.TransparentMode := tmAuto;
  bmp.Canvas.StretchDraw( Rect( 0, 0, bmp.Width, bmp.Height ), Icone );

  result:=bmp;
end;

function TRotinas.RedimensionarBMP( imagem: Graphics.TBitmap;
  nTamanho: integer):  Graphics.TBitmap;
var
  bmp: Graphics.TBitmap;
begin
  bmp:=Graphics.TBitmap.Create;
  bmp.Width:=nTamanho;
  bmp.Height:=nTamanho;
//  bmp.PixelFormat := pf8bit;
//  bmp.Transparent := True;
//  bmp.TransparentMode := tmAuto;
  bmp.Canvas.StretchDraw( Rect( 0, 0, bmp.Width, bmp.Height ), imagem );
  result:=bmp;
end;

function TRotinas.BmpParaIcone( Bitmap: Graphics.TBitmap ): TIcon;
var
  IconInfo: PIconInfo;
begin
  New(IconInfo);
  IconInfo^.fIcon := true;
  IconInfo^.xHotspot := Bitmap.Width;
  IconInfo^.yHotspot := Bitmap.Height;
  IconInfo^.hbmColor := Bitmap.Handle;
  IconInfo^.hbmMask := Bitmap.MaskHandle;
  Result := TIcon.Create;
  with Result do
    Handle := CreateIconIndirect( IconInfo );
end;

function TRotinas.BMPParaGIF(bmp: Graphics.TBitmap): TGIFImage;
var
  gif: TGIFImage;
begin
  gif := TGIFImage.Create;
  gif.Width:=bmp.Width;
  gif.Height:=bmp.Height;
  gif.Assign(bmp);
  result:=gif;
end;

function TRotinas.GIFParaBMP(gif: TGIFImage; nTamanho: integer): Graphics.TBitmap;
var
  bmp: Graphics.TBitmap;
begin
  bmp:=Graphics.TBitmap.Create;
  bmp.Width:=nTamanho;
  bmp.Height:=nTamanho;
// para salvar bmp com formato de 256 cores
  bmp.PixelFormat := pf8bit;
  bmp.Canvas.StretchDraw( Rect( 0, 0, bmp.Width, bmp.Height ), gif );
//  bmp.Assign(gif);
  result:=bmp;
end;

function TRotinas.BMPParaJPG(bmp: Graphics.TBitmap): TJPEGImage;
var
  jpg: TJPEGImage;
begin
  jpg := TJPEGImage.Create;
  jpg.CompressionQuality := 100;
  jpg.Assign(bmp);
  result:=jpg;
end;

function TRotinas.JPGParaBMP(jpg: TJPEGImage; nTamanho: integer): Graphics.TBitmap;
var
  bmp: Graphics.TBitmap;
begin
  bmp:=Graphics.TBitmap.Create;
  bmp.Width:=nTamanho;
  bmp.Height:=nTamanho;
// para salvar bmp com formato de 256 cores
  bmp.PixelFormat := pf8bit;
  bmp.Canvas.StretchDraw( Rect( 0, 0, bmp.Width, bmp.Height ), jpg );
//  bmp.Assign(jpg);
  result:=bmp;
end;

function TRotinas.BMPParaPNG(bmp: Graphics.TBitmap): TPortableNetworkGraphic;
var
  png: TPortableNetworkGraphic;
begin
  png := TPortableNetworkGraphic.Create;
  png.Assign(bmp);
  result:=png;
end;

function TRotinas.PNGParaBMP(png: TPortableNetworkGraphic; nTamanho: integer): Graphics.TBitmap;
var
  bmp: Graphics.TBitmap;
begin
  bmp:=Graphics.TBitmap.Create;
  bmp.Width:=nTamanho;
  bmp.Height:=nTamanho;
// para salvar bmp com formato de 256 cores
  bmp.PixelFormat := pf8bit;
  bmp.Canvas.StretchDraw( Rect( 0, 0, bmp.Width, bmp.Height ), png );
//  bmp.Assign(png);
  result:=bmp;
end;

function TRotinas.BMPParaTIF(bmp: Graphics.TBitmap): TTiffImage;
var
  tif: TTiffImage;
begin
  tif := TTiffImage.Create;
  tif.Assign(bmp);
  result:=tif;
end;

function TRotinas.DetectImage(const InputFileName: string;
  BM: Graphics.TBitmap): TTipoExportarExtensao;
var
  FS: TFileStream;
  FirstBytes: AnsiString;
  Graphic: TGraphic;
begin
  result:=teNUL;

  Graphic := nil;
  FS := TFileStream.Create(InputFileName, fmOpenRead);
  try
    SetLength(FirstBytes, 8);
    FS.Read(FirstBytes[1], 8);
    if Copy(FirstBytes, 1, 2) = 'BM' then
    begin
      Graphic := Graphics.TBitmap.Create;
      result:=teBMP;
    end else
    if FirstBytes = #137'PNG'#13#10#26#10 then
    begin
      Graphic := TPortableNetworkGraphic.Create;
      result:=tePNG;
    end else
    if Copy(FirstBytes, 1, 3) =  'GIF' then
    begin
      Graphic := TGIFImage.Create;
      result:=teGIF;
    end else
    if Copy(FirstBytes, 1, 2) = #$FF#$D8 then
    begin
      Graphic := TJPEGImage.Create;
      result:=teJPG;
    end;
    if Assigned(Graphic) then
    begin
      try
        FS.Seek(0, soFromBeginning);
        Graphic.LoadFromStream(FS);
        BM.Assign(Graphic);
      except
      end;
      Graphic.Free;
    end;
  finally
    FS.Free;
  end;
end;

function TRotinas.StreamParaIcone(ms: TMemoryStream): TIcon;
var
  imagem: TIcon;
begin
  imagem := TIcon.Create;
  ms.Position := 0;
  imagem.LoadFromStream(ms);
  result:=imagem;
end;

function TRotinas.StreamParaGIF(ms: TMemoryStream): TGIFImage;
var
  imagem: TGIFImage;
begin
  imagem := TGIFImage.Create;
  ms.Position := 0;
  imagem.LoadFromStream(ms);
  result:=imagem;
end;

function TRotinas.StreamParaJPG(ms: TMemoryStream): TJPEGImage;
var
  imagem: TJPEGImage;
begin
  imagem := TJPEGImage.Create;
  imagem.CompressionQuality := 100;

  ms.Position := 0;
  imagem.LoadFromStream(ms);
  result:=imagem;
end;

function TRotinas.JPGParaStream(imagem: TJPEGImage): TMemoryStream;
var
  ms: TMemoryStream;
begin
  ms := TMemoryStream.Create;
  imagem.SaveToStream(ms);
  ms.Position := 0;
  result:=ms;
end;

function TRotinas.StreamParaBMP(ms: TMemoryStream): Graphics.TBitmap;
var
  imagem: Graphics.TBitmap;
begin
  imagem := Graphics.TBitmap.Create;
  ms.Position := 0;
  imagem.LoadFromStream(ms);
  result:=imagem;
end;

function TRotinas.CompareTextAsInteger(const s1, s2: string): Integer;
begin
  Result := CompareValue(StrToInt(s1), StrToInt(s2));
end;

function TRotinas.CompareTextAsDateTime(const s1, s2: string): Integer;
begin
  Result := CompareDateTime(StrToDateTime(s1), StrToDateTime(s2));
end;

end.
