program HFSGuardaDiretorio;

uses
  Vcl.Forms,
  uPrincipal in 'uPrincipal.pas' {FrmPrincipal},
  uDataModule in 'uDataModule.pas' {dm: TDataModule},
  uRotinas in 'uRotinas.pas',
  uEscolherDir in 'uEscolherDir.pas' {FrmEscolherDir},
  uImportarDiretorio in 'uImportarDiretorio.pas' {FrmImportarDiretorio},
  uSobre in 'uSobre.pas' {FrmSobre},
  uCadExtensao in 'uCadExtensao.pas' {FrmCadExtensao},
  uSplash in 'uSplash.pas' {FrmSplash},
  uDiretorio in 'uDiretorio.pas',
  uAba in 'uAba.pas',
  uArquivo in 'uArquivo.pas',
  uExtensao in 'uExtensao.pas',
  uImportar in 'uImportar.pas',
  uCompararDiretorio in 'uCompararDiretorio.pas' {FrmCompararDiretorio},
  Bmp2tiff in 'Bmp2tiff.pas',
  SQLite3 in 'especifico\SQLite3.pas',
  sqlite3udf in 'especifico\sqlite3udf.pas',
  SQLiteTable3 in 'especifico\SQLiteTable3.pas',
  uInfoDiretorio in 'uInfoDiretorio.pas' {FrmInfoDiretorio};

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;

  FrmSplash := TFrmSplash.Create(Application);
  FrmSplash.Show;
  FrmSplash.Update;

  Application.CreateForm(TFrmPrincipal, FrmPrincipal);
  Application.CreateForm(Tdm, dm);
  Application.Run;
end.
