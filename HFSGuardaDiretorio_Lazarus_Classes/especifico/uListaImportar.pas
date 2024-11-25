unit uListaImportar;

{$mode objfpc}{$H+}

interface

uses Classes, SysUtils, uImportarObjeto;

Type
  TListaImportar = class
  private
    { private declarations }
    FListaImportar : TList;
  protected
    { protected declarations }
  public
    { public declarations }
    constructor Create;
    procedure Add(pImportar: TImportarObjeto);
    procedure Delete(Index: Integer);
    function Count: Integer;
    function Items(indice: integer): TImportarObjeto;
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

procedure TListaImportar.Add(pImportar: TImportarObjeto);
begin
  FListaImportar.Add(pImportar);
end;

procedure TListaImportar.Delete(Index: Integer);
begin
  FListaImportar.Delete(Index)
end;

function TListaImportar.Items(indice: integer): TImportarObjeto;
begin
  result:= TImportarObjeto(FListaImportar.Items[indice]);
end;

procedure TListaImportar.Free;
begin
  FListaImportar.Free;
end;

procedure TListaImportar.Clear;
begin
  FListaImportar.Clear;
end;

end.

