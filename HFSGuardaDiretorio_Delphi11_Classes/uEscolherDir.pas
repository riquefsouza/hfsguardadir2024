unit uEscolherDir;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Grids, DirOutln, StdCtrls, ExtCtrls, Vcl.FileCtrl;

type
  TFrmEscolherDir = class(TForm)
    DirectoryListBox1: TDirectoryListBox;
    DriveComboBox1: TDriveComboBox;
    btnOk: TButton;
    Label1: TLabel;
    labDiretorio: TLabel;
    Shape1: TShape;
    btnCancelar: TButton;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  FrmEscolherDir: TFrmEscolherDir;

implementation

{$R *.DFM}

end.
