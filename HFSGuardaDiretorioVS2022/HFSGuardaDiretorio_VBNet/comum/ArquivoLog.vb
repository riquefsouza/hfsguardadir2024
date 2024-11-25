Imports System.IO
Imports System.Text

Namespace comum
	Public Class ArquivoLog
		Inherits Log

		Private _FileName As String = ""

		Public Property FileName() As String
			Get
				Return Me._FileName
			End Get
			Set
				Me._FileName = value
			End Set
		End Property

		Private _FileLocation As String = ""

		Public Property FileLocation() As String
			Get
				Return Me._FileLocation
			End Get
			Set
				Me._FileLocation = value
				If Me._FileLocation.LastIndexOf("\") <> (Me._FileLocation.Length - 1) Then
					Me._FileLocation += "\"
				End If
			End Set
		End Property

		Public Sub New()
			Me.FileLocation = "C:\"
			Me.FileName = "mylog.txt"
		End Sub

		Public Overrides Sub RecordMessage(Message As Exception, Severity As Log.MessageType)
			Me.RecordMessage(Message.Message, Severity)
		End Sub

		Public Overrides Sub RecordMessage(Message__1 As String, Severity As Log.MessageType)
			Dim fileStream As FileStream = Nothing
			Dim writer As StreamWriter = Nothing
			Dim message__2 As New StringBuilder()
			Try
				fileStream = New FileStream(Me._FileLocation & Me._FileName, FileMode.OpenOrCreate, FileAccess.Write)
				writer = New StreamWriter(fileStream)
				writer.BaseStream.Seek(0, SeekOrigin.[End])
				message__2.Append(System.DateTime.Now.ToString()).Append(",").Append(Message__1)
				writer.WriteLine(message__2.ToString())
				writer.Flush()
			Finally
				If writer IsNot Nothing Then
					writer.Close()
				End If
			End Try
		End Sub
	End Class
End Namespace
