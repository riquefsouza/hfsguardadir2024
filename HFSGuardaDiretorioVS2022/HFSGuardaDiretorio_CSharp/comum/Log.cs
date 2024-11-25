/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 03/07/2015
 * Time: 15:10
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;

namespace HFSGuardaDiretorio.comum
{
	/// <summary>
	/// Description of Log.
	/// </summary>
	public abstract class Log  {   
		public enum MessageType {     
			Informational = 1,     
			Failure = 2,     
			Warning = 3,
			Error = 4   
		}     
		public abstract void RecordMessage(Exception Message, MessageType Severity);     
		public abstract void RecordMessage(string Message, MessageType Severity);  
	}
}
