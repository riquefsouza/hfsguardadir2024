program HFSGuardaDiretorio;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Interfaces, // this includes the LCL widgetset
  Forms,
  uSplash in 'uSplash.pas' {FrmSplash},
  uArquivo in 'uArquivo.pas',
  uCadExtensao in 'uCadExtensao.pas' {FrmCadExtensao},
  uCompararDiretorio in 'uCompararDiretorio.pas' {FrmCompararDiretorio},
  uDataModule in 'uDataModule.pas' {dm: TDataModule},
  uDiretorio in 'uDiretorio.pas',
  uExtensao in 'uExtensao.pas',
  uImportar in 'uImportar.pas',
  uImportarDiretorio in 'uImportarDiretorio.pas' {FrmImportarDiretorio},
  uPrincipal in 'uPrincipal.pas' {FrmPrincipal},
  uRotinas in 'uRotinas.pas',
  uSobre in 'uSobre.pas',
  uInfoDiretorio in 'uInfoDiretorio.pas', uAba {FrmInfoDiretorio},
  uListaDiretorio in 'especifico\uListaDiretorio.pas',
  uListaExtensao in 'especifico\uListaExtensao.pas',
  uListaImportar in 'especifico\uListaImportar.pas',
  SQLiteTable3 in 'especifico\SQLiteTable3.pas',
  SQLite3 in 'especifico\SQLite3.pas',
  sqlite3udf in 'especifico\sqlite3udf.pas',
  uListaAba in 'especifico\uListaAba.pas',
  uAbaObjeto in 'especifico\uAbaObjeto.pas',
  uDiretorioObjeto in 'especifico\uDiretorioObjeto.pas',
  uExtensaoObjeto in 'especifico\uExtensaoObjeto.pas',
  uImportarObjeto in 'especifico\uImportarObjeto.pas';

{$R *.res}

begin
  RequireDerivedFormResource := True;
  Application.Initialize;

  FrmSplash := TFrmSplash.Create(Application);
  FrmSplash.Show;
  FrmSplash.Update;

  Application.CreateForm(TFrmPrincipal, FrmPrincipal);
  Application.CreateForm(Tdm, dm);
  Application.Run;
end.

