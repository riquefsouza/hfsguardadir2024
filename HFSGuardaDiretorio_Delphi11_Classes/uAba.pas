unit uAba;

interface

uses
  System.Classes, System.SysUtils, System.StrUtils, System.Generics.Collections,
  Data.DB, uDataModule, uRotinas;

type
  TAba = class
  private
    { Private declarations }
  public
    { Public declarations }
    codigo: integer;
    nome: String;
    ordem: integer;

    procedure carregarAba(listaAba: TList<TAba>; progressoLog: TProgressoLog);
    function retMaxCodAba(listaLocal: TList<TAba>): integer;
    function abaToSQL(aba: TAba): String;
    function incluirAba(aba: TAba): boolean;
    function alterarAba(aba: TAba): boolean;
    function excluirAba(aba: TAba): boolean;
    function criarTabelaAbas:boolean;
    function pegaAbaPorOrdem(lista: TList<TAba>; ordem: Integer): TAba;
    function pegaOrdemPorNomeAba(lista: TList<TAba>; nomeAba: String): Integer;
  end;

var
  cAba: TAba;

implementation

procedure TAba.carregarAba(listaAba: TList<TAba>; progressoLog: TProgressoLog);
var
  aba: TAba;
  i, total: integer;
  pb: TProgresso;
begin
  listaAba.Clear;

  dm.tabelaAbas:=dm.conexao.GetTable(AnsiString(dm.SQLAbas));
  total := dm.tabelaAbas.Count;
  dm.tabelaAbas.MoveFirst;

  if total > 0 then begin
    pb.minimo := 0;
    pb.maximo := total - 1;
    pb.posicao := 0;
    pb.passo := 1;

    for i := 0 to total - 1 do begin
      aba:=TAba.Create;

      with aba do begin
        codigo := dm.tabelaAbas.FieldAsInteger(dm.tabelaAbas.FieldIndex['cod']);  //0
        nome := dm.tabelaAbas.FieldAsString(dm.tabelaAbas.FieldIndex['nome']); //1
        ordem:=(i+1);
      end;

      listaAba.Add(aba);

      dm.tabelaAbas.Next;

      pb.posicao := i;

      if Assigned(progressoLog) then begin
        progressoLog(pb);
      end;

    end;
  end;
end;

function TAba.retMaxCodAba(listaLocal: TList<TAba>): integer;
var i, nMaior: integer;
  aba: TAba;
begin
  nMaior:=0;

  for i := 0 to listaLocal.Count - 1 do begin
    aba := listaLocal.Items[i];
    if (aba.codigo > nMaior) then begin
       nMaior:=aba.codigo;
    end;
  end;

  result:=nMaior+1;
end;

function TAba.abaToSQL(aba: TAba): String;
begin
  result:='insert into Abas(cod, nome) values('+
  inttostr(aba.codigo)+','+QuotedStr(aba.nome)+')';
end;

function TAba.incluirAba(aba: TAba): boolean;
var sSQL: String;
begin
  sSQL:=abaToSQL(aba);
  result:=Rotinas.execConsulta(sSQL, True);
end;

function TAba.alterarAba(aba: TAba): boolean;
var sSQL: String;
begin
  sSQL:='update Abas set nome='+QuotedStr(aba.nome)+
  ' where cod='+inttostr(aba.codigo);
  result:=Rotinas.execConsulta(sSQL, True);
end;

function TAba.excluirAba(aba: TAba): boolean;
var sSQL: String;
begin
  sSQL:='delete from Diretorios where aba='+inttostr(aba.codigo);
  Rotinas.execConsulta(sSQL, True);
  sSQL:='delete from Abas where cod='+inttostr(aba.codigo);
  result:=Rotinas.execConsulta(sSQL, True);
end;

function TAba.criarTabelaAbas:boolean;
var sSQL: String;
begin
  sSQL:='create table IF NOT EXISTS Abas('+
  'cod integer not null,'+
  'nome varchar(10) not null,'+
  'primary key (cod))';
  result:=Rotinas.execConsulta(sSQL, False);
end;

function TAba.pegaAbaPorOrdem(lista: TList<TAba>; ordem: Integer): TAba;
var i: integer;
 aba: TAba;
begin
  result:=nil;

  for i := 0 to lista.Count - 1 do begin
    aba := lista.Items[i];
    if aba.ordem = ordem then begin
       result:=aba;
       break;
    end;
  end;
end;

function TAba.pegaOrdemPorNomeAba(lista: TList<TAba>; nomeAba: String): Integer;
var i: integer;
 aba: TAba;
begin
  result:=-1;

  for i := 0 to lista.Count - 1 do begin
    aba := lista.Items[i];
    if aba.nome = nomeAba then begin
       result:=aba.ordem;
       break;
    end;
  end;

end;

end.
