unit uDataModule;

interface

uses
  System.SysUtils, System.Classes, SQLiteTable3;

type
  Tdm = class(TDataModule)
    procedure DataModuleCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    conexao: TSQLiteDatabase;
    tabelaExtensoes, tabelaAbas: TSQLiteTable;
    SQLDiretorios, SQLExtensoes, SQLAbas: String;
    consultaDirPai, consultaDirFilho, consultaArquivo: String;
  end;

var
  dm: Tdm;

implementation

{%CLASSGROUP 'Vcl.Controls.TControl'}

{$R *.dfm}

procedure Tdm.DataModuleCreate(Sender: TObject);
begin
  SQLAbas:='select cod, nome from Abas';

  SQLDiretorios:='select aba, cod, ordem, nome, tam, tipo, '+
      'modificado, atributos, coddirpai, caminho from Diretorios';

  SQLExtensoes:='select cod, nome, bmp16, bmp32 from Extensoes';

  consultaDirPai:='select aba, cod, ordem, coddirpai, nome, tam, '+
      'tipo, modificado, atributos, caminho, nomeaba, nomepai, caminhopai '+
      'from consultadirpai '+
      'order by 1,2,3,4';
  consultaDirFilho:='select aba, cod, ordem, coddirpai, nome, tam, '+
      'tipo, modificado, atributos, caminho, nomeaba, nomepai, caminhopai '+
      'from consultadirfilho '+
      'order by 1,2,3,4';
  consultaArquivo:='select aba, cod, ordem, coddirpai, nome, tam, '+
      'tipo, modificado, atributos, caminho, nomeaba, nomepai, caminhopai '+
      'from consultaarquivo '+
      'order by tipo desc, ordem';

end;

end.
