unit uListaDiretorio;

{$mode objfpc}{$H+}

interface

uses Classes, SysUtils, uDiretorioObjeto;

Type
  TListaDiretorio = class
  private
    { private declarations }
    FListaDiretorio : TList;
  protected
    { protected declarations }
  public
    { public declarations }
    constructor Create;
    procedure Add(pDiretorio: TDiretorioObjeto);
    procedure Delete(Index: Integer);
    function Count: Integer;
    function Items(indice: integer): TDiretorioObjeto;
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

procedure TListaDiretorio.Add(pDiretorio: TDiretorioObjeto);
begin
  FListaDiretorio.Add(pDiretorio);
end;

procedure TListaDiretorio.Delete(Index: Integer);
begin
  FListaDiretorio.Delete(Index)
end;

function TListaDiretorio.Items(indice: integer): TDiretorioObjeto;
begin
  result:=TDiretorioObjeto(FListaDiretorio.Items[indice]);
end;

procedure TListaDiretorio.Free;
begin
  FListaDiretorio.Free;
end;

procedure TListaDiretorio.Clear;
begin
  FListaDiretorio.Clear;
end;

end.

