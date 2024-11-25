// ---------------------------------------------------------------------------

#ifndef SQLite3LibH
#define SQLite3LibH

#include <inttypes.h>

#define SQLITE_OPEN_READONLY         0x00000001  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_READWRITE        0x00000002  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_CREATE           0x00000004  /* Ok for sqlite3_open_v2() */

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

enum TTipoColuna {
	SQLITE_INTEGER = 1, SQLITE_FLOAT = 2, SQLITE_TEXT = 3, SQLITE_BLOB = 4,
		SQLITE_NULL = 5
};

const int SQLITE_UTF8 = 1;
const int SQLITE_UTF16 = 2;
const int SQLITE_UTF16BE = 3;
const int SQLITE_UTF16LE = 4;
const int SQLITE_ANY = 5;

typedef void(*sqlite3_destructor_type)(void*);
#define SQLITE_STATIC      ((sqlite3_destructor_type)0)
#define SQLITE_TRANSIENT   ((sqlite3_destructor_type)-1)

typedef struct sqlite3 sqlite3;
typedef struct sqlite3_stmt sqlite3_stmt;
typedef struct sqlite3_backup sqlite3_backup;
// ---------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

	int sqlite3_open(const char *filename,
		sqlite3 **db);
	int sqlite3_open_v2(
		const char *filename,   /* Database filename (UTF-8) */
		sqlite3 **ppDb,         /* OUT: SQLite db handle */
		int flags,              /* Flags */
		const char *zVfs        /* Name of VFS module to use */
	);
	int sqlite3_close(sqlite3 *db);
	int sqlite3_exec(sqlite3 *db,
		const char *SQLStatement, int(*callback)(void*, int, char**, char**),
		void *UserData, const char **ErrMsg);
	const char* sqlite3_libversion();
	const char* sqlite3_errmsg(sqlite3 *db);
	int sqlite3_errcode(sqlite3 *db);
	void sqlite3_free(void* P);
	int sqlite3_prepare_v2(sqlite3 *db,
		const char *SQLStatement, int nBytes, sqlite3_stmt **hStmt,
		const char **pzTail);
	int sqlite3_step(sqlite3_stmt *hStmt);

	int sqlite3_bind_blob(sqlite3_stmt *hStmt,
		int ParamNum, const void *ptrData, int numBytes, void(*)(void*));
	int sqlite3_bind_text(sqlite3_stmt *hStmt,
		int ParamNum, const char *Text, int numBytes, void(*)(void*));
	int sqlite3_bind_double(sqlite3_stmt *hStmt,
		int ParamNum, double Data);
	int sqlite3_bind_int(sqlite3_stmt *hStmt,
		int ParamNum, int Data);
	int sqlite3_bind_int64(sqlite3_stmt *hStmt,
		int ParamNum, __int64 Data);
	int sqlite3_bind_null(sqlite3_stmt *hStmt,
		int ParamNum);
	int sqlite3_bind_parameter_index
		(sqlite3_stmt *hStmt, const char *zName);
	int sqlite3_finalize(sqlite3_stmt *hStmt);
	int sqlite3_reset(sqlite3_stmt *hStmt);
	int sqlite3_changes(sqlite3 *db);
	int sqlite3_column_count
		(sqlite3_stmt *hStmt);
	const char* sqlite3_column_name
		(sqlite3_stmt *hStmt, int ColNum);
	const char* sqlite3_column_decltype
		(sqlite3_stmt *hStmt, int ColNum);
	const void* sqlite3_column_blob
		(sqlite3_stmt *hStmt, int ColNum);
	int sqlite3_column_bytes
		(sqlite3_stmt *hStmt, int ColNum);
	double sqlite3_column_double
		(sqlite3_stmt *hStmt, int ColNum);
	int sqlite3_column_int(sqlite3_stmt *hStmt,
		int ColNum);
	const unsigned char* sqlite3_column_text
		(sqlite3_stmt *hStmt, int ColNum);
	int sqlite3_column_type(sqlite3_stmt *hStmt,
		int ColNum);
	__int64 sqlite3_column_int64
		(sqlite3_stmt *hStmt, int ColNum);

	int sqlite3_get_table(sqlite3 *db,
		const char *SQLStatement, char ***ResultPtr, int *RowCount,
		int *ColCount, char **ErrMsg);
	void sqlite3_free_table(char **Table);
	int sqlite3_complete(const char *sql);
	__int64 sqlite3_last_insert_rowid
		(sqlite3 *db);
	void sqlite3_interrupt(sqlite3 *db);
	void sqlite3_busy_handler(sqlite3 *db,
		int(*)(void*,int), void *UserData);
	void sqlite3_busy_timeout(sqlite3 *db,
		int TimeOut);

	int sqlite3_total_changes(sqlite3 *db);
	int sqlite3_prepare(sqlite3 *db,
		const char *SQLStatement, int nBytes, sqlite3_stmt **hStmt,
		const char **pzTail);

	int sqlite3_data_count(sqlite3_stmt *hStmt);

	sqlite3_backup* sqlite3_backup_init
		(sqlite3 *DestDb, const char *DestDbName, sqlite3 *SourceDb,
		const char *SourceDbName);
	int sqlite3_backup_step
		(sqlite3_backup *hBackup, int nPage);
	int sqlite3_backup_finish
		(sqlite3_backup *hBackup);
	int sqlite3_backup_remaining
		(sqlite3_backup *hBackup);
	int sqlite3_backup_pagecount
		(sqlite3_backup *hBackup);

	int sqlite3_enable_shared_cache(int Value);

	// user collate definiton
	int sqlite3_create_collation(sqlite3 *db,
		const char *Name, int eTextRep, void *UserData,
		int(*xCompare)(void*,int,const void*,int,const void*));

#ifdef __cplusplus
}
#endif
// ---------------------------------------------------------------------------
#endif
