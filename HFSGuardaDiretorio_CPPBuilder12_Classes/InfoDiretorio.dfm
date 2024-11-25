object FrmInfoDiretorio: TFrmInfoDiretorio
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Informa'#231#245'es do Diret'#243'rio / Arquivo'
  ClientHeight = 312
  ClientWidth = 358
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 358
    Height = 89
    Align = alTop
    Caption = 'Legenda dos Atributos'
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 24
      Width = 113
      Height = 13
      Caption = '[ARQ] - Arquivo comum'
    end
    object Label2: TLabel
      Left = 16
      Top = 45
      Width = 107
      Height = 13
      Caption = '[HID] - Arquivo Oculto'
    end
    object Label3: TLabel
      Left = 192
      Top = 24
      Width = 77
      Height = 13
      Caption = '[DIR] - Diret'#243'rio'
    end
    object Label4: TLabel
      Left = 192
      Top = 45
      Width = 85
      Height = 13
      Caption = '[VOL] - Volume ID'
    end
    object Label5: TLabel
      Left = 16
      Top = 65
      Width = 128
      Height = 13
      Caption = '[SYS] - Arquivo de Sistema'
    end
    object Label6: TLabel
      Left = 192
      Top = 65
      Width = 156
      Height = 13
      Caption = '[ROL] - Arquivo Somente Leitura'
    end
  end
  object sgInfo: TStringGrid
    Left = 0
    Top = 89
    Width = 358
    Height = 182
    Align = alClient
    ColCount = 2
    DefaultColWidth = 128
    DefaultRowHeight = 18
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSelect]
    TabOrder = 1
    OnDrawCell = sgInfoDrawCell
    ColWidths = (
      76
      271)
  end
  object Panel1: TPanel
    Left = 0
    Top = 271
    Width = 358
    Height = 41
    Align = alBottom
    TabOrder = 2
    object btnOk: TButton
      Left = 144
      Top = 6
      Width = 75
      Height = 25
      Caption = '&Ok'
      ModalResult = 1
      TabOrder = 0
    end
  end
end
