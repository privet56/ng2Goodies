SET @targetSchemaName = 'prod';
SET @targetCollation = 'utf8_general_ci';
SET @oldCollation = 'latin1_swedish_ci';

-- 1. set DB collation
-- variables aren't supported here, eg. error 1295 'this command is not supported in the prepared statement protocol yet'
ALTER DATABASE personal_portal_prod COLLATE utf8_general_ci;

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
	
	DECLARE cs CURSOR FOR SELECT concat('ALTER TABLE `', t1.TABLE_SCHEMA, '`.`', t1.table_name, '` MODIFY `', t1.column_name, '` ', t1.data_type, '(' , t1.CHARACTER_MAXIMUM_LENGTH, ')' , ' COLLATE ', @targetCollation, ';')
	from information_schema.columns t1
	where t1.TABLE_SCHEMA like @targetSchemaName and t1.COLLATION_NAME = @oldCollation;
		
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;
	
	OPEN cs;
	
	achange: LOOP
		FETCH cs INTO c;
		
      IF done = 1 THEN
      	LEAVE achange;
      END IF;
      
      PREPARE stmt FROM c;
      EXECUTE stmt;
      DEALLOCATE PREPARE stmt;
	END LOOP achange;
	
	CLOSE cs;

END; //

DELIMITER ;

-- otherwise Error 1833 'cannot change column, used in a foreign key constraint'
-- doesn't prevent 1062 Duplicate entry <something with ss and the same with ß> for key 'security_login_mail_index' > fix first manually!
SET FOREIGN_KEY_CHECKS = 0;

-- can take several minutes!
CALL _proc_cols2utf8();

SET FOREIGN_KEY_CHECKS = 1;

SELECT CONCAT('FINISHED setting COLLATION=', @targetCollation, ' for DB ', @targetSchemaName) AS result;
