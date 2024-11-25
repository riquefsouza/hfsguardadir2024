unit uSplash;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants,
  System.Classes, Vcl.Graphics, Vcl.Controls, Vcl.Forms, Vcl.Dialogs,
  Vcl.StdCtrls, Vcl.ComCtrls, uRotinas;

type
  TFrmSplash = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    pb: TProgressBar;
  private
    { Private declarations }
  public
    { Public declarations }
    procedure ProgressoLog(progresso: TProgresso);
  end;

var
  FrmSplash: TFrmSplash;

implementation

{$R *.dfm}

procedure TFrmSplash.ProgressoLog(progresso: TProgresso);
begin
  if progresso.posicao = 0 then begin
     pb.Min := progresso.minimo;
     pb.Max := progresso.maximo;
     pb.Step := progresso.passo;
  end;

  pb.Position := progresso.posicao;
end;

end.
