unit uListaDiretorio;

interface

uses Classes, SysUtils, uListaAba;

Type
  PTDiretorio = ^TDiretorio;
  TTipo = record
    codigo: String;
    nome: String;
  end;
  TDiretorio = record
    aba: TAba;
    codigo: integer;
    ordem: integer;
    codDirPai: integer;
    nome: String;
    tamanho: Int64;
    tipo: TTipo;
    modificado: TDatetime;
    atributos: String;
    caminho: String;
    nomePai: String;
    caminhoPai: String;
    tamanhoFormatado: String;
    modificadoFormatado: String;
    caminhoOriginal: String;
  end;

  TListaDiretorio = class
  private
    { private declarations }
    FListaDiretorio : TList;
    RDiretorio: PTDiretorio;
  protected
    { protected declarations }
  public
    { public declarations }
    constructor Create;
    procedure Add(pDiretorio: TDiretorio);
    procedure Delete(Index: Integer);
    function Count: Integer;
    function Items(indice: integer): TDiretorio;
    procedure Free;
    procedure Clear;    
  published
    { published declarations }
  end;
implementation

constructor TListaDiretorio.Create;
begin
  inherited Create;
  FListaDiretorio := TList.Create;
end;

function TListaDiretorio.Count: Integer;
begin
  Result := FListaDiretorio.Count;
end;

procedure TListaDiretorio.Add(pDiretorio: TDiretorio);
begin
  New(RDiretorio);
  RDiretorio^.aba.codigo:=pDiretorio.aba.codigo;
  RDiretorio^.aba.nome:=pDiretorio.aba.nome;
  RDiretorio^.codigo:=pDiretorio.codigo;
  RDiretorio^.ordem:=pDiretorio.ordem;
  RDiretorio^.codDirPai:=pDiretorio.codDirPai;
  RDiretorio^.nome:=pDiretorio.nome;
  RDiretorio^.tamanho:=pDiretorio.tamanho;
  RDiretorio^.tipo.codigo:=pDiretorio.tipo.codigo;
  RDiretorio^.tipo.nome:=pDiretorio.tipo.nome;  
  RDiretorio^.modificado:=pDiretorio.modificado;
  RDiretorio^.atributos:=pDiretorio.atributos;
  RDiretorio^.caminho:=pDiretorio.caminho;
  RDiretorio^.nomePai:=pDiretorio.nomePai;
  RDiretorio^.caminhoPai:=pDiretorio.caminhoPai;
  RDiretorio^.tamanhoFormatado:=pDiretorio.tamanhoFormatado;
  RDiretorio^.modificadoFormatado:=pDiretorio.modificadoFormatado;
  RDiretorio^.caminhoOriginal:=pDiretorio.caminhoOriginal;

  FListaDiretorio.Add(RDiretorio);
end;

procedure TListaDiretorio.Delete(Index: Integer);
begin
  FListaDiretorio.Delete(Index)
end;

function TListaDiretorio.Items(indice: integer): TDiretorio;
var diretorio: TDiretorio;
begin
  RDiretorio:=FListaDiretorio.Items[indice];
  diretorio.aba.codigo:=RDiretorio^.aba.codigo;
  diretorio.aba.nome:=RDiretorio^.aba.nome;
  diretorio.codigo:=RDiretorio^.codigo;
  diretorio.ordem:=RDiretorio^.ordem;
  diretorio.codDirPai:=RDiretorio^.codDirPai;
  diretorio.nome:=RDiretorio^.nome;
  diretorio.tamanho:=RDiretorio^.tamanho;
  diretorio.tipo.codigo:=RDiretorio^.tipo.codigo;
  diretorio.tipo.nome:=RDiretorio^.tipo.nome;
  diretorio.modificado:=RDiretorio^.modificado;
  diretorio.atributos:=RDiretorio^.atributos;
  diretorio.caminho:=RDiretorio^.caminho;
  diretorio.nomePai:=RDiretorio^.nomePai;
  diretorio.caminhoPai:=RDiretorio^.caminhoPai;
  diretorio.tamanhoFormatado:=RDiretorio^.tamanhoFormatado;
  diretorio.modificadoFormatado:=RDiretorio^.modificadoFormatado;
  diretorio.caminhoOriginal:=RDiretorio^.caminhoOriginal;

  result:= diretorio;
end;

procedure TListaDiretorio.Free;
var i: integer;
begin
  for i := 0 to FListaDiretorio.Count - 1 do begin
    RDiretorio:=FListaDiretorio.Items[i];
    Dispose(RDiretorio);
  end;
  FListaDiretorio.Free;
end;

procedure TListaDiretorio.Clear;
var i: integer;
begin
  for i := 0 to FListaDiretorio.Count - 1 do begin
    RDiretorio:=FListaDiretorio.Items[i];
    Dispose(RDiretorio);
  end;
  FListaDiretorio.Clear;
end;

end.

