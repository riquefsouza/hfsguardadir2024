unit uListaExtensao;

{$mode objfpc}{$H+}

interface

uses Classes, SysUtils, Graphics, uExtensaoObjeto;

Type
  TListaExtensao = class
  private
    { private declarations }
    FListaExtensao : TList;
  protected
    { protected declarations }
  public
    { public declarations }
    constructor Create;
    procedure Add(pExtensao: TExtensaoObjeto);
    procedure Delete(Index: Integer);
    function Count: Integer;
    function Items(indice: integer): TExtensaoObjeto;
    procedure Free;
    procedure Clear;
  published
    { published declarations }
  end;
implementation

constructor TListaExtensao.Create;
begin
  inherited Create;
  FListaExtensao := TList.Create;
end;

function TListaExtensao.Count: Integer;
begin
  Result := FListaExtensao.Count;
end;

procedure TListaExtensao.Add(pExtensao: TExtensaoObjeto);
begin
  FListaExtensao.Add(pExtensao);
end;

procedure TListaExtensao.Delete(Index: Integer);
begin
  FListaExtensao.Delete(Index)
end;

function TListaExtensao.Items(indice: integer): TExtensaoObjeto;
begin
  result:=TExtensaoObjeto(FListaExtensao.Items[indice]);
end;

procedure TListaExtensao.Free;
begin
  FListaExtensao.Free;
end;

procedure TListaExtensao.Clear;
begin
  FListaExtensao.Clear;
end;

end.

