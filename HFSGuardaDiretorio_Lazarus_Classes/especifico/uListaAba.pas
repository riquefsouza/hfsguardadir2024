unit uListaAba;

{$mode objfpc}{$H+}

interface

uses Classes, SysUtils, uAbaObjeto;

Type
  TListaAba = class
  private
    { private declarations }
    FListaAba : TList;
  protected
    { protected declarations }
  public
    { public declarations }
    constructor Create;
    procedure Add(pAba: TAbaObjeto);
    procedure Delete(Index: Integer);
    function Count: Integer;
    function Items(indice: integer): TAbaObjeto;
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

procedure TListaAba.Add(pAba: TAbaObjeto);
begin
  FListaAba.Add(pAba);
end;

procedure TListaAba.Delete(Index: Integer);
begin
  FListaAba.Delete(Index)
end;

function TListaAba.Items(indice: integer): TAbaObjeto;
begin
  result:=TAbaObjeto(FListaAba.Items[indice]);
end;

procedure TListaAba.Free;
begin
  FListaAba.Free;
end;

procedure TListaAba.Clear;
begin
  FListaAba.Clear;
end;

end.

