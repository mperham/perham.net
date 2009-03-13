
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXDescendentCountsMap (
  DB_COLUMN_PREFIXuserId
      INTEGER
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXitemId
      INTEGER
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXdescendentCount
      INTEGER
    
      NOT NULL
    
    );

  
    ALTER TABLE DB_TABLE_PREFIXDescendentCountsMap
    ADD PRIMARY KEY (DB_COLUMN_PREFIXuserId
	,
      DB_COLUMN_PREFIXitemId);
    

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'DescendentCountsMap',
      1,
      0
      );

  