
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGroup (
  DB_COLUMN_PREFIXid
      INTEGER
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXgroupType
      INTEGER
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXgroupName
      VARCHAR(
      
	  128
	
      )
    
    );

  
    ALTER TABLE DB_TABLE_PREFIXGroup
    ADD PRIMARY KEY (DB_COLUMN_PREFIXid);
    
    CREATE UNIQUE INDEX DB_TABLE_PREFIXGroup_19099
    ON DB_TABLE_PREFIXGroup
    (DB_COLUMN_PREFIXgroupName);
    

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'Group',
      1,
      1
      );

  