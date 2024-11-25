// ---------------------------------------------------------------------------

#ifndef SQLite3LibH
#define SQLite3LibH
// ---------------------------------------------------------------------------
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

/*
#if defined(_MSC_VER) || defined(__BORLANDC__)
  typedef __int64 sqlite_int64;
  typedef unsigned __int64 sqlite_uint64;
#else
  typedef long long int sqlite_int64;
  typedef unsigned long long int sqlite_uint64;
#endif
*/

typedef void(*sqlite3_destructor_type)(void*);
#define SQLITE_STATIC      ((sqlite3_destructor_type)0)
#define SQLITE_TRANSIENT   ((sqlite3_destructor_type)-1)

typedef struct sqlite3 sqlite3;
typedef struct sqlite3_stmt sqlite3_stmt;
typedef struct sqlite3_backup sqlite3_backup;

typedef int TSQLiteBusyHandlerCallback(void *UserData, int P2);

typedef int TCollateXCompare(void *UserData, int Buf1Len, const void *Buf1,
	int Buf2Len, const void *Buf2);
// ---------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

	__declspec(dllimport) int __stdcall sqlite3_open(const char *filename,
		sqlite3 **db);
	__declspec(dllimport) int __stdcall sqlite3_close(sqlite3 *db);
	__declspec(dllimport) int __stdcall sqlite3_exec(sqlite3 *db,
		const char *SQLStatement, int(*callback)(void*, int, char**, char**),
		void *UserData, const char **ErrMsg);
	__declspec(dllimport) const char* __stdcall sqlite3_libversion();
	__declspec(dllimport) const char* __stdcall sqlite3_errmsg(sqlite3 *db);
	__declspec(dllimport) int __stdcall sqlite3_errcode(sqlite3 *db);
	__declspec(dllimport) void __stdcall sqlite3_free(void* P);
	__declspec(dllimport) int __stdcall sqlite3_prepare_v2(sqlite3 *db,
		const char *SQLStatement, int nBytes, sqlite3_stmt **hStmt,
		const char **pzTail);
	__declspec(dllimport) int __stdcall sqlite3_step(sqlite3_stmt *hStmt);

	__declspec(dllimport) int __stdcall sqlite3_bind_blob(sqlite3_stmt *hStmt,
		int ParamNum, const void *ptrData, int numBytes, void(*)(void*));
	__declspec(dllimport) int __stdcall sqlite3_bind_text(sqlite3_stmt *hStmt,
		int ParamNum, const char *Text, int numBytes, void(*)(void*));
	__declspec(dllimport) int __stdcall sqlite3_bind_double(sqlite3_stmt *hStmt,
		int ParamNum, double Data);
	__declspec(dllimport) int __stdcall sqlite3_bind_int(sqlite3_stmt *hStmt,
		int ParamNum, int Data);
	__declspec(dllimport) int __stdcall sqlite3_bind_int64(sqlite3_stmt *hStmt,
		int ParamNum, __int64 Data);
	__declspec(dllimport) int __stdcall sqlite3_bind_null(sqlite3_stmt *hStmt,
		int ParamNum);
	__declspec(dllimport) int __stdcall sqlite3_bind_parameter_index
		(sqlite3_stmt *hStmt, const char *zName);
	__declspec(dllimport) int __stdcall sqlite3_finalize(sqlite3_stmt *hStmt);
	__declspec(dllimport) int __stdcall sqlite3_reset(sqlite3_stmt *hStmt);
	__declspec(dllimport) int __stdcall sqlite3_changes(sqlite3 *db);
	__declspec(dllimport) int __stdcall sqlite3_column_count
		(sqlite3_stmt *hStmt);
	__declspec(dllimport) const char* __stdcall sqlite3_column_name
		(sqlite3_stmt *hStmt, int ColNum);
	__declspec(dllimport) const char* __stdcall sqlite3_column_decltype
		(sqlite3_stmt *hStmt, int ColNum);
	__declspec(dllimport) const void* __stdcall sqlite3_column_blob
		(sqlite3_stmt *hStmt, int ColNum);
	__declspec(dllimport) int __stdcall sqlite3_column_bytes
		(sqlite3_stmt *hStmt, int ColNum);
	__declspec(dllimport) double __stdcall sqlite3_column_double
		(sqlite3_stmt *hStmt, int ColNum);
	__declspec(dllimport) int __stdcall sqlite3_column_int(sqlite3_stmt *hStmt,
		int ColNum);
	__declspec(dllimport) const unsigned char* __stdcall sqlite3_column_text
		(sqlite3_stmt *hStmt, int ColNum);
	__declspec(dllimport) int __stdcall sqlite3_column_type(sqlite3_stmt *hStmt,
		int ColNum);
	__declspec(dllimport) __int64 __stdcall sqlite3_column_int64
		(sqlite3_stmt *hStmt, int ColNum);

	__declspec(dllimport) int __stdcall sqlite3_get_table(sqlite3 *db,
		const char *SQLStatement, char ***ResultPtr, int *RowCount,
		int *ColCount, char **ErrMsg);
	__declspec(dllimport) void __stdcall sqlite3_free_table(char **Table);
	__declspec(dllimport) int __stdcall sqlite3_complete(const char *sql);
	__declspec(dllimport) __int64 __stdcall sqlite3_last_insert_rowid
		(sqlite3 *db);
	__declspec(dllimport) void __stdcall sqlite3_interrupt(sqlite3 *db);
	__declspec(dllimport) void __stdcall sqlite3_busy_handler(sqlite3 *db,
		TSQLiteBusyHandlerCallback CallbackPtr, void *UserData);
	__declspec(dllimport) void __stdcall sqlite3_busy_timeout(sqlite3 *db,
		int TimeOut);

	__declspec(dllimport) int __stdcall sqlite3_total_changes(sqlite3 *db);
	__declspec(dllimport) int __stdcall sqlite3_prepare(sqlite3 *db,
		const char *SQLStatement, int nBytes, sqlite3_stmt **hStmt,
		const char **pzTail);

	__declspec(dllimport) int __stdcall sqlite3_data_count(sqlite3_stmt *hStmt);

	__declspec(dllimport) sqlite3_backup* __stdcall sqlite3_backup_init
		(sqlite3 *DestDb, const char *DestDbName, sqlite3 *SourceDb,
		const char *SourceDbName);
	__declspec(dllimport) int __stdcall sqlite3_backup_step
		(sqlite3_backup *hBackup, int nPage);
	__declspec(dllimport) int __stdcall sqlite3_backup_finish
		(sqlite3_backup *hBackup);
	__declspec(dllimport) int __stdcall sqlite3_backup_remaining
		(sqlite3_backup *hBackup);
	__declspec(dllimport) int __stdcall sqlite3_backup_pagecount
		(sqlite3_backup *hBackup);

	__declspec(dllimport) int __stdcall sqlite3_enable_shared_cache(int Value);

	// user collate definiton
	__declspec(dllimport) int __stdcall sqlite3_create_collation(sqlite3 *db,
		const char *Name, int eTextRep, void *UserData,
		TCollateXCompare xCompare);

#ifdef __cplusplus
}
#endif
// ---------------------------------------------------------------------------
// std::string SQLiteFieldType(int SQLiteFieldTypeCode);
// std::string ColValueToStr(const char *Value);
// ---------------------------------------------------------------------------
#endif
