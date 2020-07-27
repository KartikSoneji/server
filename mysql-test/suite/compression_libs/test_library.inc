# ==== Usage ====
#
# --let $test_library = <library name>
# --source test_library.inc

--echo #
--echo # Test --use-compression=$test_library
--echo #

--source include/have_innodb.inc

--let $innodb_compression_algorithm_orig = `SELECT @@innodb_compression_algorithm`



--echo # Start server with default options ($test_library enabled)

--let $restart_parameters = --use-compression=lzma
--source include/restart_mysqld.inc

--eval SET GLOBAL innodb_compression_algorithm = $test_library
--let $test_table_name = innodb_compressed_$test_library

--disable_warnings
--eval DROP TABLE IF EXISTS $test_table_name
--enable_warnings

--eval CREATE TABLE $test_table_name (a int, b char(20)) engine = innodb page_compressed = 1
--eval INSERT INTO $test_table_name (a, b) VALUES (0, "abc")
--eval INSERT INTO $test_table_name (a, b) VALUES (1, "def")
--eval INSERT INTO $test_table_name (a, b) VALUES (2, "ghi")

--eval SELECT * FROM $test_table_name


--echo # Start server with no libraries

--let $restart_parameters = --use_compression=
--source include/restart_mysqld.inc

--echo # Table should not exist, as server does not know how to read compressed data
# 1932 ER_NO_SUCH_TABLE_IN_ENGINE
--disable_warnings
--error 1932
--eval SELECT * FROM $test_table_name
--enable_warnings

--eval DROP TABLE $test_table_name



# reset system
--let $restart_parameters =
--source include/restart_mysqld.inc

--disable_query_log
--eval SET GLOBAL innodb_compression_algorithm = $innodb_compression_algorithm_orig
--enable_query_log
