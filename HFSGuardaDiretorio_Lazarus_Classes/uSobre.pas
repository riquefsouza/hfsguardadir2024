unit uSobre;

{$mode objfpc}{$H+}

interface

uses
  Controls, StdCtrls, Classes, Forms, ExtCtrls, SysUtils,
  Graphics;

type

  { TFrmSobre }

  TFrmSobre = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    btnOk: TButton;
    procedure Label4Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  FrmSobre: TFrmSobre;

implementation

{$R *.lfm}

{ TFrmSobre }


procedure TFrmSobre.Label4Click(Sender: TObject);
begin

end;

end.
