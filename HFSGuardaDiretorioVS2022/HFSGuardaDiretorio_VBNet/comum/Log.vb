'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 03/07/2015
' * Time: 15:10
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 


Namespace comum
	''' <summary>
	''' Description of Log.
	''' </summary>
	Public MustInherit Class Log
		Public Enum MessageType
			Informational = 1
			Failure = 2
			Warning = 3
			[Error] = 4
		End Enum
		Public MustOverride Sub RecordMessage(Message As Exception, Severity As MessageType)
		Public MustOverride Sub RecordMessage(Message As String, Severity As MessageType)
	End Class
End Namespace
