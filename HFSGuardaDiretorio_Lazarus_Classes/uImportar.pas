unit uImportar;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, uImportarObjeto,
  uListaDiretorio, uListaExtensao, uRotinas,
  uArquivo, uDiretorio, uExtensao;

type
  TImportar = class(TImportarObjeto)
  private
    { Private declarations }
  public
    { Public declarations }
    procedure CarregarListaDiretorios(importar: TImportarObjeto; var nOrdem: integer;
       listaDiretorio: TListaDiretorio; log: TStrings);
    procedure ImportacaoCompleta(importar: TImportarObjeto; var nOrdem: integer;
      listaExtensao: TListaExtensao; log: TStrings; progressoLog: TProgressoLog);
  end;

var
  cImportar: TImportar;

implementation

procedure TImportar.CarregarListaDiretorios(importar: TImportarObjeto;
   var nOrdem: integer; listaDiretorio: TListaDiretorio; log: TStrings);
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

procedure TImportar.ImportacaoCompleta(importar: TImportarObjeto;
  var nOrdem: integer; listaExtensao: TListaExtensao; log: TStrings;
  progressoLog: TProgressoLog);
var
  listaDiretorio: TListaDiretorio;
begin
  listaDiretorio := TListaDiretorio.Create;
  try
    CarregarListaDiretorios(importar, nOrdem, listaDiretorio, log);
    cExtensao.salvarExtensoes(listaDiretorio, listaExtensao, log, progressoLog);
    cDiretorio.salvarDiretorio(listaDiretorio, log, progressoLog);
  finally
    listaDiretorio.Free;
  end;
end;

end.
