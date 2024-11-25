unit uListaImportar;

interface

uses Classes, SysUtils;

Type
  PTImportar = ^TImportar;
  TImportar = record
    aba: integer;
    codDirRaiz: integer;
    rotuloRaiz: String;
    nomeDirRaiz: String;
    caminho: String;
  end;

  TListaImportar = class
  private
    { private declarations }
    FListaImportar : TList;
    RImportar: PTImportar;
  protected
    { protected declarations }
  public
    { public declarations }
    constructor Create;
    procedure Add(pImportar: TImportar);
    procedure Delete(Index: Integer);
    function Count: Integer;
    function Items(indice: integer): TImportar;
    procedure Free;
    procedure Clear;    
  published
    { published declarations }
  end;
implementation

constructor TListaImportar.Create;
begin
  inherited Create;
  FListaImportar := TList.Create;
end;

function TListaImportar.Count: Integer;
begin
  Result := FListaImportar.Count;
end;

procedure TListaImportar.Add(pImportar: TImportar);
begin
  New(RImportar);
  RImportar^.aba:=pImportar.aba;
  RImportar^.codDirRaiz:=pImportar.codDirRaiz;
  RImportar^.rotuloRaiz:=pImportar.rotuloRaiz;
  RImportar^.nomeDirRaiz:=pImportar.nomeDirRaiz;
  RImportar^.caminho:=pImportar.caminho;
  FListaImportar.Add(RImportar);
end;

procedure TListaImportar.Delete(Index: Integer);
begin
  FListaImportar.Delete(Index)
end;

function TListaImportar.Items(indice: integer): TImportar;
var importar: TImportar;
begin
  RImportar:=FListaImportar.Items[indice];
  importar.aba:=RImportar^.aba;
  importar.codDirRaiz:=RImportar^.codDirRaiz;
  importar.rotuloRaiz:=RImportar^.rotuloRaiz;
  importar.nomeDirRaiz:=RImportar^.nomeDirRaiz;
  importar.caminho:=RImportar^.caminho;
  result:= importar;
end;

procedure TListaImportar.Free;
var i: integer;
begin
  for i := 0 to FListaImportar.Count - 1 do begin
    RImportar:=FListaImportar.Items[i];
    Dispose(RImportar);
  end;
  FListaImportar.Free;
end;

procedure TListaImportar.Clear;
var i: integer;
begin
  for i := 0 to FListaImportar.Count - 1 do begin
    RImportar:=FListaImportar.Items[i];
    Dispose(RImportar);
  end;
  FListaImportar.Clear;
end;

end.

