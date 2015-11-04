/*
 ============================================================================
 Name        : c1.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void version() {
	printf("%s\n", sqlite3_libversion());
}

void dbtest() {
	sqlite3 *db;
	sqlite3_stmt *res;
	int rc = sqlite3_open(":memory:",&db);
	if (rc != SQLITE_OK) {

		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);

		return ;
	}

	rc = sqlite3_prepare_v2(db, "SELECT SQLITE_VERSION()", -1, &res, 0);

	if (rc != SQLITE_OK) {

		fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);

		return ;
	}

	rc = sqlite3_step(res);

	if (rc == SQLITE_ROW) {
		printf("%s\n", sqlite3_column_text(res, 0));
	}

	sqlite3_finalize(res);
	sqlite3_close(db);
}

void dbtest2() {
	sqlite3 *db;
	char *err_msg = 0;

	int rc = sqlite3_open("c:\\test.sqlite", &db);

	if (rc != SQLITE_OK) {

		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);

		return ;
	}

	char *sql = "DROP TABLE IF EXISTS Cars;"
			"CREATE TABLE Cars(Id INT, Name TEXT, Price INT);"
			"INSERT INTO Cars VALUES(1, 'Audi', 52642);"
			"INSERT INTO Cars VALUES(2, 'Mercedes', 57127);"
			"INSERT INTO Cars VALUES(3, 'Skoda', 9000);"
			"INSERT INTO Cars VALUES(4, 'Volvo', 29000);"
			"INSERT INTO Cars VALUES(5, 'Bentley', 350000);"
			"INSERT INTO Cars VALUES(6, 'Citroen', 21000);"
			"INSERT INTO Cars VALUES(7, 'Hummer', 41400);"
			"INSERT INTO Cars VALUES(8, 'Volkswagen', 21600);";

	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	if (rc != SQLITE_OK ) {

		fprintf(stderr, "SQL error: %s\n", err_msg);

		sqlite3_free(err_msg);
		sqlite3_close(db);

		return ;
	}

	sqlite3_close(db);

	return ;
}

//---------------------------------------------------------------------
int callback(void *, int, char **, char **);

void testSelect() {
	sqlite3 *db;
	char *err_msg = 0;

	int rc = sqlite3_open("c:\\test.sqlite", &db);

	if (rc != SQLITE_OK) {

		fprintf(stderr, "Cannot open database: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);

		return ;
	}

	char *sql = "SELECT * FROM Cars";

	rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

	if (rc != SQLITE_OK ) {

		fprintf(stderr, "Failed to select data\n");
		fprintf(stderr, "SQL error: %s\n", err_msg);

		sqlite3_free(err_msg);
		sqlite3_close(db);

		return ;
	}

	sqlite3_close(db);
}
int callback(void *NotUsed, int argc, char **argv,
                    char **azColName) {

    NotUsed = 0;

    for (int i = 0; i < argc; i++) {

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");

    return 0;
}
//---------------------------------------------------------------------
int main() {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	version();
	//dbtest2();
	testSelect();
	return EXIT_SUCCESS;
}
