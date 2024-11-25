object FrmEscolherDir: TFrmEscolherDir
  Left = 306
  Top = 171
  BorderStyle = bsDialog
  Caption = 'Escolha o Diret'#243'rio'
  ClientHeight = 319
  ClientWidth = 300
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Shape1: TShape
    Left = 8
    Top = 254
    Width = 281
    Height = 22
  end
  object Label1: TLabel
    Left = 8
    Top = 240
    Width = 90
    Height = 13
    Caption = 'Diret'#243'rio escolhido:'
  end
  object labDiretorio: TLabel
    Left = 12
    Top = 258
    Width = 272
    Height = 15
    AutoSize = False
    Caption = 'C:\Windows\system32'
    Color = clWhite
    ParentColor = False
  end
  object DirectoryListBox1: TDirectoryListBox
    Left = 8
    Top = 32
    Width = 281
    Height = 201
    DirLabel = labDiretorio
    TabOrder = 0
  end
  object DriveComboBox1: TDriveComboBox
    Left = 8
    Top = 8
    Width = 281
    Height = 19
    DirList = DirectoryListBox1
    TabOrder = 1
    TextCase = tcUpperCase
  end
  object btnOk: TButton
    Left = 72
    Top = 288
    Width = 75
    Height = 25
    Caption = '&Ok'
    Default = True
    ModalResult = 1
    TabOrder = 2
  end
  object btnCancelar: TButton
    Left = 160
    Top = 288
    Width = 75
    Height = 25
    Caption = '&Cancelar'
    ModalResult = 2
    TabOrder = 3
  end
end
