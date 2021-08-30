SET @targetSchemaName = 'bunnies_db';	-- the line ALTER DATABASE... cannot use variables! :-(
-- change from latin1_swedish_ci to utf8_general_ci
SET @targetCollation = 'utf8_general_ci'; 		-- _ci: we would like to keep case insensitive

SET @setOnTbls = 0;
SET @setOnCols = 0;

-- 1. set DB collation
-- variables aren't supported here, eg. error 1295 'this command is not supported in the prepared statement protocol yet'
ALTER DATABASE bunnies_db COLLATE utf8_general_ci;

-- 2. set TABLE collations
DELIMITER //

DROP PROCEDURE IF EXISTS _proc_tables2utf8;

CREATE PROCEDURE _proc_tables2utf8()
BEGIN
	DECLARE c VARCHAR(1024) DEFAULT NULL;
	DECLARE done INT DEFAULT 0;
	
	DECLARE cs CURSOR FOR SELECT concat('ALTER TABLE `', TABLE_SCHEMA, '`.`', table_name, '` COLLATE ', @targetCollation)
		from information_schema.tables
		where TABLE_SCHEMA like @targetSchemaName;
		
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;

	OPEN cs;
	
	achange: LOOP
      FETCH cs INTO c;

      IF done = 1 THEN
      	LEAVE achange;
      END IF;
	  
      SET @setOnTbls := @setOnTbls + 1;
      
      PREPARE stmt FROM c;
      EXECUTE stmt;
      DEALLOCATE PREPARE stmt;
	END LOOP achange;
	
	CLOSE cs;

END; //

DELIMITER ;
CALL _proc_tables2utf8();

-- 3. set COLUMN collations
DELIMITER //

DROP PROCEDURE IF EXISTS _proc_cols2utf8;

CREATE PROCEDURE _proc_cols2utf8()
BEGIN
	DECLARE c VARCHAR(1024) DEFAULT NULL;
	DECLARE done INT DEFAULT 0;
	
	DECLARE cs CURSOR FOR SELECT concat('ALTER TABLE `', t1.TABLE_SCHEMA, '`.`', t1.table_name, '` MODIFY `', t1.column_name, '` ',
	-- (MEDIUM|LONG)TEXT has no CHARACTER_MAXIMUM_LENGTH, use better TEXT(CHARACTER_MAXIMUM_LENGTH)
	REPLACE(REPLACE(t1.data_type, 'longtext', 'text'), 'mediumtext', 'text'), 
	'(' , t1.CHARACTER_MAXIMUM_LENGTH, ')' , ' COLLATE ', @targetCollation,
	(CASE WHEN t1.IS_NULLABLE = 'NO' THEN
		CONCAT(' not null',
			CASE WHEN t1.COLUMN_DEFAULT is not null THEN
				concat(' default ', t1.COLUMN_DEFAULT)
			ELSE
				''
			END
		)
	ELSE -- = t1.IS_NULLABLE = 'YES'
		 -- if(COLUMN_DEFAULT is null) > convert to text 'null' (otherwise CONCAT fails)
		concat(' default ', ifnull(t1.COLUMN_DEFAULT, 'null'))
	END),
	';')
	from information_schema.columns t1
	where t1.TABLE_SCHEMA like @targetSchemaName AND t1.COLLATION_NAME IS NOT null;

	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;
	
	OPEN cs;
	
	achange: LOOP
      FETCH cs INTO c;
		
      IF done = 1 THEN
      	LEAVE achange;
      END IF;
	  
      SET @setOnCols := @setOnCols + 1;
      
      PREPARE stmt FROM c;
      EXECUTE stmt;
      DEALLOCATE PREPARE stmt;
	END LOOP achange;
	
	CLOSE cs;

END; //

DELIMITER ;

-- otherwise Error 1833 'cannot change column, used in a foreign key constraint'
-- doesn't prevent 1062 Duplicate entry <something with ss and the same with ß> for key 'my_mail_index' > fix 'wei%web.de' first manually!
--		SELECT * FROM my WHERE mail_column LIKE 'wei%web.de';
SET FOREIGN_KEY_CHECKS = 0;

-- will take several minutes!
-- ATTENTION: this command changes TEXT(65535) to MEDIUMTEXT: https://dev.mysql.com/doc/refman/5.6/en/alter-table.html | https://bugs.mysql.com/bug.php?id=31291
CALL _proc_cols2utf8();

SET FOREIGN_KEY_CHECKS = 1;

SELECT CONCAT('FINISHED setting COLLATION=', @targetCollation, ' for DB ', @targetSchemaName, ' ', @setOnTbls, ' tables, ', @setOnCols, ' columns') AS result;
