unit uDiretorioObjeto;

{$mode objfpc}{$H+}

interface

uses
 uArquivo, uAba;

type
  TTipo = record
    codigo: String;
    nome: String;
  end;
  TDiretorioObjeto = class(TArquivo)
  private
    { Private declarations }
  public
    { Public declarations }
    aba: TAba;
    codigo: integer;
    ordem: integer;
    codDirPai: integer;
    tipo: TTipo;
    atributos: String;
    caminho: String;
    nomePai: String;
    caminhoPai: String;
    tamanhoFormatado: String;
    modificadoFormatado: String;
    caminhoOriginal: String;
  end;

implementation

end.
