#include "SQLite3Lib.h"

const int SQLITE_OK = 0; // Successful result
/* beginning-of-error-codes */
const int SQLITE_ERROR = 1; // SQL error or missing database
const int SQLITE_INTERNAL = 2; // An internal logic error in SQLite
const int SQLITE_PERM = 3; // Access permission denied
const int SQLITE_ABORT = 4; // Callback routine requested an abort
const int SQLITE_BUSY = 5; // The database file is locked
const int SQLITE_LOCKED = 6; // A table in the database is locked
const int SQLITE_NOMEM = 7; // A malloc() failed
const int SQLITE_READONLY = 8; // Attempt to write a readonly database
const int SQLITE_INTERRUPT = 9; // Operation terminated by sqlite3_interrupt()
const int SQLITE_IOERR = 10; // Some kind of disk I/O error occurred
const int SQLITE_CORRUPT = 11; // The database disk image is malformed
const int SQLITE_NOTFOUND = 12; // (Internal Only) Table or record not found
const int SQLITE_FULL = 13; // Insertion failed because database is full
const int SQLITE_CANTOPEN = 14; // Unable to open the database file
const int SQLITE_PROTOCOL = 15; // Database lock protocol error
const int SQLITE_EMPTY = 16; // Database is empty
const int SQLITE_SCHEMA = 17; // The database schema changed
const int SQLITE_TOOBIG = 18; // Too much data for one row of a table
const int SQLITE_CONSTRAINT = 19; // Abort due to contraint violation
const int SQLITE_MISMATCH = 20; // Data type mismatch
const int SQLITE_MISUSE = 21; // Library used incorrectly
const int SQLITE_NOLFS = 22; // Uses OS features not supported on host
const int SQLITE_AUTH = 23; // Authorization denied
const int SQLITE_FORMAT = 24; // Auxiliary database format error
const int SQLITE_RANGE = 25; // 2nd parameter to sqlite3_bind out of range
const int SQLITE_NOTADB = 26; // File opened that is not a database file
const int SQLITE_ROW = 100; // sqlite3_step() has another row ready
const int SQLITE_DONE = 101; // sqlite3_step() has finished executing

const int SQLITE_UTF8 = 1;
const int SQLITE_UTF16 = 2;
const int SQLITE_UTF16BE = 3;
const int SQLITE_UTF16LE = 4;
const int SQLITE_ANY = 5;

// ---------------------------------------------------------------------------
/*
AnsiString SQLiteFieldType(int SQLiteFieldTypeCode) {
	switch (SQLiteFieldTypeCode) {
	case SQLITE_INTEGER:
		return "Integer";
	case SQLITE_FLOAT:
		return "Float";
	case SQLITE_TEXT:
		return "Text";
	case SQLITE_BLOB:
		return "Blob";
	case SQLITE_NULL:
		return "Null";
	default:
		return "Unknown SQLite Field Type Code '" +
			IntToStr(SQLiteFieldTypeCode) + "'";
	}
}

// ---------------------------------------------------------------------------
AnsiString ColValueToStr(PAnsiChar Value) {
	if (Value == NULL)
		return "NULL";
	else
		return Value;
}
*/
// ---------------------------------------------------------------------------
