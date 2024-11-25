unit uArquivo;

interface

type
  TArquivo = class
  private
    { Private declarations }
  public
    { Public declarations }
    nome: String;
    tamanho: Int64;
    modificado: TDatetime;
    natributos: Integer;
  end;

var
  cArquivo: TArquivo;

implementation

end.
