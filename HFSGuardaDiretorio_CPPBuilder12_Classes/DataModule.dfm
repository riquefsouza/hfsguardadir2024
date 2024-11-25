object dm: Tdm
  OldCreateOrder = True
  OnCreate = DataModuleCreate
  Height = 250
  Width = 371
  object conexao: TSQLConnection
    ConnectionName = 'GuardaDir'
    DriverName = 'Sqlite'
    LoginPrompt = False
    Params.Strings = (
      'DriverName=Sqlite'
      'DriverUnit=Data.DbxSqlite'
      
        'DriverPackageLoader=TDBXSqliteDriverLoader,DBXSqliteDriver210.bp' +
        'l'
      
        'MetaDataPackageLoader=TDBXSqliteMetaDataCommandFactory,DbxSqlite' +
        'Driver210.bpl'
      'FailIfMissing=True'
      'Database=')
    Left = 32
    Top = 8
  end
  object consultaDirFilho: TSQLQuery
    MaxBlobSize = 1
    Params = <>
    SQL.Strings = (
      
        'select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, ' +
        'atributos, caminho, nomeaba, nomepai, caminhopai'
      'from consultadirfilho'
      'order by 1,2,3,4')
    SQLConnection = conexao
    Left = 192
    Top = 8
  end
  object consultaDirPai: TSQLQuery
    MaxBlobSize = 1
    Params = <>
    SQL.Strings = (
      
        'select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, ' +
        'atributos, caminho, nomeaba, nomepai, caminhopai'
      'from consultadirpai'
      'order by 1,2,3,4')
    SQLConnection = conexao
    Left = 104
    Top = 8
  end
  object consultaArquivo: TSQLQuery
    MaxBlobSize = 1
    Params = <>
    SQL.Strings = (
      
        'select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, ' +
        'atributos, caminho, nomeaba, nomepai, caminhopai'
      'from consultaarquivo'
      'order by tipo desc, ordem')
    SQLConnection = conexao
    Left = 280
    Top = 8
  end
  object tabelaAbas: TSQLTable
    MaxBlobSize = -1
    SQLConnection = conexao
    TableName = 'Abas'
    Left = 32
    Top = 64
    object tabelaAbascod: TLargeintField
      FieldName = 'cod'
      Required = True
    end
    object tabelaAbasnome: TWideStringField
      FieldName = 'nome'
      Required = True
      Size = 10
    end
  end
  object consultaAuxiliar: TSQLQuery
    MaxBlobSize = 1
    Params = <>
    SQLConnection = conexao
    Left = 104
    Top = 64
  end
  object tabelaExtensoes: TSQLTable
    MaxBlobSize = 1
    SQLConnection = conexao
    TableName = 'Extensoes'
    Left = 32
    Top = 120
  end
  object tabelaDiretorios: TSQLTable
    MaxBlobSize = 1
    SQLConnection = conexao
    TableName = 'Diretorios'
    Left = 32
    Top = 176
  end
  object cdsDiretorios: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'dspDiretorios'
    Left = 200
    Top = 176
  end
  object cdsExtensoes: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'dspExtensoes'
    BeforeRefresh = cdsExtensoesBeforeRefresh
    Left = 200
    Top = 120
  end
  object dspExtensoes: TDataSetProvider
    DataSet = tabelaExtensoes
    Constraints = False
    Left = 120
    Top = 120
  end
  object dspDiretorios: TDataSetProvider
    DataSet = tabelaDiretorios
    Constraints = False
    Left = 120
    Top = 176
  end
end
