object FrmInfoDiretorio: TFrmInfoDiretorio
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Informa'#231#245'es do Diret'#243'rio / Arquivo'
  ClientHeight = 339
  ClientWidth = 407
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poScreenCenter
  OnShow = FormShow
  TextHeight = 15
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 407
    Height = 89
    Align = alTop
    Caption = 'Legenda dos Atributos'
    TabOrder = 0
    ExplicitWidth = 352
    object Label1: TLabel
      Left = 16
      Top = 24
      Width = 130
      Height = 15
      Caption = '[ARQ] - Arquivo comum'
    end
    object Label2: TLabel
      Left = 16
      Top = 45
      Width = 120
      Height = 15
      Caption = '[HID] - Arquivo Oculto'
    end
    object Label3: TLabel
      Left = 192
      Top = 24
      Width = 83
      Height = 15
      Caption = '[DIR] - Diret'#243'rio'
    end
    object Label4: TLabel
      Left = 192
      Top = 45
      Width = 95
      Height = 15
      Caption = '[VOL] - Volume ID'
    end
    object Label5: TLabel
      Left = 16
      Top = 65
      Width = 140
      Height = 15
      Caption = '[SYS] - Arquivo de Sistema'
    end
    object Label6: TLabel
      Left = 192
      Top = 65
      Width = 172
      Height = 15
      Caption = '[ROL] - Arquivo Somente Leitura'
    end
  end
  object sgInfo: TStringGrid
    Left = 0
    Top = 89
    Width = 407
    Height = 209
    Align = alClient
    ColCount = 2
    DefaultColWidth = 128
    DefaultRowHeight = 20
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSelect]
    TabOrder = 1
    OnDrawCell = sgInfoDrawCell
    ExplicitWidth = 358
    ExplicitHeight = 182
    ColWidths = (
      112
      271)
  end
  object Panel1: TPanel
    Left = 0
    Top = 298
    Width = 407
    Height = 41
    Align = alBottom
    TabOrder = 2
    ExplicitTop = 262
    ExplicitWidth = 352
    object btnOk: TButton
      Left = 168
      Top = 6
      Width = 76
      Height = 25
      Caption = '&Ok'
      ModalResult = 1
      TabOrder = 0
    end
  end
end
