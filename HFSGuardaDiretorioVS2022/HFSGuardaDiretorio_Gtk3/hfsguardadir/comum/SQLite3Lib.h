// ---------------------------------------------------------------------------

#ifndef SQLite3LibH
#define SQLite3LibH

#include <inttypes.h>

#define SQLITE_OPEN_READONLY         0x00000001  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_READWRITE        0x00000002  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_CREATE           0x00000004  /* Ok for sqlite3_open_v2() */

// ---------------------------------------------------------------------------
extern const int SQLITE_OK; // Successful result
/* beginning-of-error-codes */
extern const int SQLITE_ERROR; // SQL error or missing database
extern const int SQLITE_INTERNAL; // An internal logic error in SQLite
extern const int SQLITE_PERM; // Access permission denied
extern const int SQLITE_ABORT; // Callback routine requested an abort
extern const int SQLITE_BUSY; // The database file is locked
extern const int SQLITE_LOCKED; // A table in the database is locked
extern const int SQLITE_NOMEM; // A malloc() failed
extern const int SQLITE_READONLY; // Attempt to write a readonly database
extern const int SQLITE_INTERRUPT; // Operation terminated by sqlite3_interrupt()
extern const int SQLITE_IOERR; // Some kind of disk I/O error occurred
extern const int SQLITE_CORRUPT; // The database disk image is malformed
extern const int SQLITE_NOTFOUND; // (Internal Only) Table or record not found
extern const int SQLITE_FULL; // Insertion failed because database is full
extern const int SQLITE_CANTOPEN; // Unable to open the database file
extern const int SQLITE_PROTOCOL; // Database lock protocol error
extern const int SQLITE_EMPTY; // Database is empty
extern const int SQLITE_SCHEMA; // The database schema changed
extern const int SQLITE_TOOBIG; // Too much data for one row of a table
extern const int SQLITE_CONSTRAINT; // Abort due to contraint violation
extern const int SQLITE_MISMATCH; // Data type mismatch
extern const int SQLITE_MISUSE; // Library used incorrectly
extern const int SQLITE_NOLFS; // Uses OS features not supported on host
extern const int SQLITE_AUTH; // Authorization denied
extern const int SQLITE_FORMAT; // Auxiliary database format error
extern const int SQLITE_RANGE; // 2nd parameter to sqlite3_bind out of range
extern const int SQLITE_NOTADB; // File opened that is not a database file
extern const int SQLITE_ROW; // sqlite3_step() has another row ready
extern const int SQLITE_DONE; // sqlite3_step() has finished executing

enum TTipoColuna {
	SQLITE_INTEGER = 1, SQLITE_FLOAT = 2, SQLITE_TEXT = 3, SQLITE_BLOB = 4,
		SQLITE_NULL = 5
};

extern const int SQLITE_UTF8;
extern const int SQLITE_UTF16;
extern const int SQLITE_UTF16BE;
extern const int SQLITE_UTF16LE;
extern const int SQLITE_ANY;

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
