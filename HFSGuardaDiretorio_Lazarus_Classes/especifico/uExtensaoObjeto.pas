unit uExtensaoObjeto;

{$mode objfpc}{$H+}

interface

uses
  Graphics;
  
type
  TExtensaoObjeto = class
  private
    { Private declarations }
  public
    { Public declarations }
    codigo: integer;
    nome: String;
    ordem: integer;
    bmp16: Graphics.TBitmap;
    bmp32: Graphics.TBitmap;
  end;    

implementation

end.
