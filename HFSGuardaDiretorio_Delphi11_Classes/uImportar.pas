unit uImportar;

interface

uses
  System.Classes, System.SysUtils, System.StrUtils, System.Generics.Collections,
  Vcl.ComCtrls, uArquivo, uDiretorio, uExtensao, uRotinas;

type
  TImportar = class
  private
    { Private declarations }
  public
    { Public declarations }
    aba: integer;
    codDirRaiz: integer;
    rotuloRaiz: String;
    nomeDirRaiz: String;
    caminho: String;

    procedure CarregarListaDiretorios(importar: TImportar; var nOrdem: integer;
       listaDiretorio: TList<TDiretorio>; log: TStrings);
    procedure ImportacaoCompleta(importar: TImportar; var nOrdem: integer;
      listaExtensao: TList<TExtensao>; log: TStrings; progressoLog: TProgressoLog);
  end;

var
  cImportar: TImportar;

implementation

procedure TImportar.CarregarListaDiretorios(importar: TImportar;
  var nOrdem: integer; listaDiretorio: TList<TDiretorio>; log: TStrings);
var
  arquivo: TArquivo;
  diretorio: TDiretorio;
begin
    arquivo:=TArquivo.Create;
    arquivo.nome := importar.rotuloRaiz;
    arquivo.tamanho := 0;
    arquivo.modificado := Now;
    arquivo.natributos := faDirectory;

    diretorio := cDiretorio.atribuiDiretorio(importar.aba, importar.codDirRaiz,
      importar.nomeDirRaiz, '', true, listaDiretorio, arquivo, nOrdem);

    listaDiretorio.Add(diretorio);
    log.Append(importar.caminho);

    cDiretorio.ImportarDiretorio(importar.aba, importar.codDirRaiz, importar.nomeDirRaiz,
      importar.caminho, listaDiretorio, nOrdem, log);
end;

procedure TImportar.ImportacaoCompleta(importar: TImportar; var nOrdem: integer;
  listaExtensao: TList<TExtensao>; log: TStrings; progressoLog: TProgressoLog);
var
  listaDiretorio: TList<TDiretorio>;
begin
  listaDiretorio := TList<TDiretorio>.Create;
  try
    CarregarListaDiretorios(importar, nOrdem, listaDiretorio, log);

    if TOSVersion.Platform = pfWindows then
    begin
      cExtensao.salvarExtensoes(listaDiretorio, listaExtensao, log, progressoLog);
    end;
    cDiretorio.salvarDiretorio(listaDiretorio, log, progressoLog);
  finally
    listaDiretorio.Free;
  end;
end;

end.
