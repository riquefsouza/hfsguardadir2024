unit uListaAba;

interface

uses Classes, SysUtils;

Type
  PTAba = ^TAba;
  TAba = record
    codigo: integer;
    nome: String;
    ordem: integer;
  end;

  TListaAba = class
  private
    { private declarations }
    FListaAba : TList;
    RAba: PTAba;
  protected
    { protected declarations }
  public
    { public declarations }
    constructor Create;
    procedure Add(pAba: TAba);
    procedure Delete(Index: Integer);
    function Count: Integer;
    function Items(indice: integer): TAba;
    procedure Free;
    procedure Clear;    
  published
    { published declarations }
  end;
implementation

constructor TListaAba.Create;
begin
  inherited Create;
  FListaAba := TList.Create;
end;

function TListaAba.Count: Integer;
begin
  Result := FListaAba.Count;
end;

procedure TListaAba.Add(pAba: TAba);
begin
  New(RAba);
  RAba^.codigo:=pAba.codigo;
  RAba^.nome:=pAba.nome;
  RAba^.ordem:=pAba.ordem;
  FListaAba.Add(RAba);
end;

procedure TListaAba.Delete(Index: Integer);
begin
  FListaAba.Delete(Index)
end;

function TListaAba.Items(indice: integer): TAba;
var aba: TAba;
begin
  RAba:=FListaAba.Items[indice];
  aba.codigo:=RAba^.codigo;
  aba.nome:=RAba^.nome;
  aba.ordem:=RAba^.ordem;
  result:= aba;
end;

procedure TListaAba.Free;
var i: integer;
begin
  for i := 0 to FListaAba.Count - 1 do begin
    RAba:=FListaAba.Items[i];
    Dispose(RAba);
  end;
  FListaAba.Free;
end;

procedure TListaAba.Clear;
var i: integer;
begin
  for i := 0 to FListaAba.Count - 1 do begin
    RAba:=FListaAba.Items[i];
    Dispose(RAba);
  end;
  FListaAba.Clear;
end;

end.

