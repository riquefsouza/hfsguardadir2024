object FrmCompararDiretorio: TFrmCompararDiretorio
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Comparar Diret'#243'rios'
  ClientHeight = 572
  ClientWidth = 688
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 329
    Width = 114
    Height = 13
    Caption = 'Diferen'#231'as Encontradas'
  end
  object gbDiretorio1: TGroupBox
    Left = 8
    Top = 39
    Width = 329
    Height = 284
    Caption = 'Diret'#243'rio 1'
    TabOrder = 0
    object cmbAba1: TComboBox
      Left = 13
      Top = 24
      Width = 300
      Height = 21
      Style = csDropDownList
      TabOrder = 0
      OnChange = cmbAba1Change
    end
    object tvDiretorio1: TTreeView
      Left = 13
      Top = 51
      Width = 300
      Height = 222
      HideSelection = False
      Indent = 19
      RowSelect = True
      TabOrder = 1
    end
  end
  object gbDiretorio2: TGroupBox
    Left = 343
    Top = 39
    Width = 330
    Height = 284
    Caption = 'Diret'#243'rio 2'
    TabOrder = 1
    object cmbAba2: TComboBox
      Left = 16
      Top = 23
      Width = 297
      Height = 21
      Style = csDropDownList
      TabOrder = 0
      OnChange = cmbAba2Change
    end
    object tvDiretorio2: TTreeView
      Left = 16
      Top = 50
      Width = 300
      Height = 223
      HideSelection = False
      Indent = 19
      RowSelect = True
      TabOrder = 1
    end
  end
  object panelPesquisa: TPanel
    Left = 0
    Top = 0
    Width = 688
    Height = 33
    Align = alTop
    TabOrder = 2
    object pb: TProgressBar
      Left = 128
      Top = 6
      Width = 458
      Height = 17
      Min = 1
      Position = 1
      Step = 1
      TabOrder = 0
    end
    object btnCompararDiretorios: TButton
      Left = 4
      Top = 2
      Width = 118
      Height = 25
      Caption = '&Comparar Diret'#243'rios'
      TabOrder = 1
      OnClick = btnCompararDiretoriosClick
    end
    object btnSalvarLog: TButton
      Left = 592
      Top = 2
      Width = 87
      Height = 25
      Caption = '&Salvar Log'
      Enabled = False
      TabOrder = 2
      OnClick = btnSalvarLogClick
    end
  end
  object lvCompara: TListView
    Left = 0
    Top = 348
    Width = 688
    Height = 205
    Align = alBottom
    Columns = <
      item
        Caption = 'Nome'
        Width = 300
      end
      item
        Caption = 'Tamanho'
        Width = 100
      end
      item
        Caption = 'Tipo'
        Width = 70
      end
      item
        Caption = 'Modificado'
        Width = 120
      end
      item
        Caption = 'Atributos'
        Width = 90
      end
      item
        AutoSize = True
        Caption = 'Caminho'
      end>
    GridLines = True
    ReadOnly = True
    TabOrder = 3
    ViewStyle = vsReport
    OnColumnClick = lvComparaColumnClick
    OnCompare = lvComparaCompare
  end
  object barraStatus: TStatusBar
    Left = 0
    Top = 553
    Width = 688
    Height = 19
    Panels = <
      item
        Text = 'Total de diferen'#231'as encontradas:'
        Width = 200
      end
      item
        Width = 50
      end>
  end
end
