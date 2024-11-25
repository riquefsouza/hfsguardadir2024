object FrmCadExtensao: TFrmCadExtensao
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Cadastro de Extens'#227'o de Arquivo'
  ClientHeight = 380
  ClientWidth = 290
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object sgExtensao: TStringGrid
    Left = 0
    Top = 0
    Width = 290
    Height = 328
    Align = alClient
    ColCount = 2
    DefaultColWidth = 100
    DefaultRowHeight = 18
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSelect]
    TabOrder = 0
    OnDrawCell = sgExtensaoDrawCell
    ExplicitLeft = 8
    ExplicitTop = 8
    ExplicitWidth = 220
    ExplicitHeight = 217
  end
  object Panel1: TPanel
    Left = 0
    Top = 328
    Width = 290
    Height = 52
    Align = alBottom
    TabOrder = 1
    object btnIncluir: TButton
      Left = 56
      Top = 14
      Width = 75
      Height = 25
      Caption = '&Incluir'
      TabOrder = 0
      OnClick = IncluirExtensao1Click
    end
    object btnExcluir: TButton
      Left = 153
      Top = 14
      Width = 75
      Height = 25
      Caption = '&Excluir'
      TabOrder = 1
      OnClick = ExcluirExtensao1Click
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'Todos os Arquivos (*.*)|*.*'
    Left = 56
    Top = 80
  end
  object MainMenu1: TMainMenu
    Left = 56
    Top = 152
    object Extensao1: TMenuItem
      Caption = 'Extens'#227'o'
      object IncluirExtensao1: TMenuItem
        Caption = 'Incluir Extens'#227'o'
        OnClick = IncluirExtensao1Click
      end
      object ExcluirExtensao1: TMenuItem
        Caption = 'Excluir Extens'#227'o'
        OnClick = ExcluirExtensao1Click
      end
      object ExcluirTodasExtensoes1: TMenuItem
        Caption = 'Excluir Todas Extens'#245'es'
        OnClick = ExcluirTodasExtensoes1Click
      end
    end
    object ExportarTodos1: TMenuItem
      Caption = 'Exportar Todos'
      object ExportarBitmap1: TMenuItem
        Caption = 'Exportar para Bitmap'
        OnClick = ExportarBitmap1Click
      end
      object ExportarIcone1: TMenuItem
        Caption = 'Exportar para '#205'cone'
        OnClick = ExportarIcone1Click
      end
      object ExportarGIF1: TMenuItem
        Caption = 'Exportar para GIF'
        OnClick = ExportarGIF1Click
      end
      object ExportarJPEG1: TMenuItem
        Caption = 'Exportar para JPEG'
        OnClick = ExportarJPEG1Click
      end
      object ExportarPNG1: TMenuItem
        Caption = 'Exportar para PNG'
        OnClick = ExportarPNG1Click
      end
      object ExportarTIFF1: TMenuItem
        Caption = 'Exportar para TIFF'
        OnClick = ExportarTIFF1Click
      end
    end
    object ImportarTodos1: TMenuItem
      Caption = 'Importar Todos'
      object ImportarIconesArquivos1: TMenuItem
        Caption = 'Importar '#205'cones dos Arquivos'
        OnClick = ImportarIconesArquivos1Click
      end
      object ExtrairIconesArquivos1: TMenuItem
        Caption = 'Extrair '#205'cones dos Arquivos'
        OnClick = ExtrairIconesArquivos1Click
      end
    end
  end
end
