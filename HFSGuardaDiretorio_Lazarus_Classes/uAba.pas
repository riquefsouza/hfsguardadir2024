unit uAba;

{$mode objfpc}{$H+}

interface

uses
Classes, SysUtils, uDataModule, uAbaObjeto, uListaAba, uRotinas;

type
  TAba = class(TAbaObjeto)
  private
    { Private declarations }
  public
    { Public declarations }
    procedure carregarAba(listaAba: TListaAba; progressoLog: TProgressoLog);
    function retMaxCodAba(listaLocal: TListaAba): integer;
    function abaToSQL(aba: TAbaObjeto): String;
    function incluirAba(aba: TAbaObjeto): boolean;
    function alterarAba(aba: TAbaObjeto): boolean;
    function excluirAba(aba: TAbaObjeto): boolean;
    function criarTabelaAbas:boolean;
    function pegaAbaPorOrdem(lista: TListaAba; nordem: Integer): TAbaObjeto;
    function pegaOrdemPorNomeAba(lista: TListaAba; nomeAba: String): Integer;
  end;

var
  cAba: TAba;

implementation

procedure TAba.carregarAba(listaAba: TListaAba; progressoLog: TProgressoLog);
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

function TAba.retMaxCodAba(listaLocal: TListaAba): integer;
var i, nMaior: integer;
  aba: TAbaObjeto;
begin
  nMaior:=0;

  for i := 0 to listaLocal.Count - 1 do begin
    aba := listaLocal.Items(i);
    if (aba.codigo > nMaior) then begin
       nMaior:=aba.codigo;
    end;
  end;

  result:=nMaior+1;
end;

function TAba.abaToSQL(aba: TAbaObjeto): String;
begin
  result:='insert into Abas(cod, nome) values('+
  inttostr(aba.codigo)+','+QuotedStr(aba.nome)+')';
end;

function TAba.incluirAba(aba: TAbaObjeto): boolean;
var sSQL: String;
begin
  sSQL:=abaToSQL(aba);
  result:=Rotinas.execConsulta(sSQL, True);
end;

function TAba.alterarAba(aba: TAbaObjeto): boolean;
var sSQL: String;
begin
  sSQL:='update Abas set nome='+QuotedStr(aba.nome)+
  ' where cod='+inttostr(aba.codigo);
  result:=Rotinas.execConsulta(sSQL, True);
end;

function TAba.excluirAba(aba: TAbaObjeto): boolean;
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

function TAba.pegaAbaPorOrdem(lista: TListaAba; nordem: Integer): TAbaObjeto;
var i: integer;
 aba: TAbaObjeto;
begin
  result:=nil;

  for i := 0 to lista.Count - 1 do begin
    aba := lista.Items(i);
    if aba.ordem = nordem then begin
       result:=aba;
       break;
    end;
  end;
end;

function TAba.pegaOrdemPorNomeAba(lista: TListaAba; nomeAba: String): Integer;
var i: integer;
 aba: TAbaObjeto;
begin
  result:=-1;

  for i := 0 to lista.Count - 1 do begin
    aba := lista.Items(i);
    if aba.nome = nomeAba then begin
       result:=aba.ordem;
       break;
    end;
  end;

end;

end.
