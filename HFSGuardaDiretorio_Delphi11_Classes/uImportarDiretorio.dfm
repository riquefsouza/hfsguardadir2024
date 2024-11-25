object FrmImportarDiretorio: TFrmImportarDiretorio
  Left = 0
  Top = 0
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Importando Diret'#243'rio'
  ClientHeight = 572
  ClientWidth = 895
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 15
  object memoImportaDir: TMemo
    Left = 0
    Top = 0
    Width = 895
    Height = 536
    Align = alClient
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
    OnChange = memoImportaDirChange
  end
  object barraStatus: TStatusBar
    Left = 0
    Top = 553
    Width = 895
    Height = 19
    Panels = <
      item
        Text = 'Total de linhas sendo processadas:'
        Width = 200
      end
      item
        Width = 50
      end>
  end
  object pbImportar: TProgressBar
    Left = 0
    Top = 536
    Width = 895
    Height = 17
    Align = alBottom
    TabOrder = 2
  end
end
