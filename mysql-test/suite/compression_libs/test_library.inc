# ==== Usage ====
#
# --let $test_engine  = <engine name>
# --let $test_library = <library name>
# --source test_library.inc

--echo #
--echo # Test --use-compression=$test_library on storage engine "$test_engine"
--echo #


--echo # Start server with default options ($test_library enabled)

--let $restart_parameters = --use-compression=$test_library
--source include/restart_mysqld.inc

#--eval SELECT Variable_value as "" from information_schema.global_status WHERE Variable_name = "Compression_loaded_$test_library"

--let $test_table_name = $test_enginecompressed_$test_library

--disable_warnings
--eval DROP TABLE IF EXISTS $test_table_name
--enable_warnings

# Create compressed table according to engine
if($test_engine == "connect"){
    exit;
}

--source include/have_innodb.inc
if($test_engine == "innodb"){
    --let $innodb_compression_algorithm_orig = `SELECT @@Innodb_compression_algorithm`
    
    --eval SET GLOBAL innodb_compression_algorithm = $test_library
    --let $table_create_parameters = page_compressed = 1
}
if($test_engine == "mroonga"){
    --let $column_flags = COMMENT 'flags "COLUMN_SCALAR|COMPRESS_$test_library"'
}
if($test_engine == "rocksdb"){
    exit;
}
if($table_create_parameters == ""){
    echo Error: unrecogized value for \$test_engine: "$test_engine"
    exit;
}

eval CREATE TABLE $test_table_name (
        a int,
        b char(20) $column_flags
    )
    engine = $test_engine
    $table_create_parameters
;

--eval INSERT INTO $test_table_name (a, b) VALUES (0, "abc")
--eval INSERT INTO $test_table_name (a, b) VALUES (1, "def")
--eval INSERT INTO $test_table_name (a, b) VALUES (2, "ghi")

--eval SELECT * FROM $test_table_name


--echo # Start server with no libraries

--let $restart_parameters = --use_compression=
--source include/restart_mysqld.inc

--echo # Table should not exist, as server does not know how to read compressed data
# Anticipate errors
--disable_query_log
CALL mtr.add_suppression("InnoDB: Background Page read failed to read or decrypt \\[page id: space=\\d+, page number=[123]\\]");
--eval CALL mtr.add_suppression("InnoDB: Table `test`.`$test_table_name` is corrupted. Please drop the table and recreate.");
--enable_query_log
--error ER_NO_SUCH_TABLE_IN_ENGINE
--eval SELECT * FROM $test_table_name

--eval DROP TABLE $test_table_name



# reset system
--let $restart_parameters =
--source include/restart_mysqld.inc

--disable_query_log
if($test_engine == "innodb"){
    eval SET GLOBAL innodb_compression_algorithm = $innodb_compression_algorithm_orig;
}
--enable_query_log
