
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXDataItem (
  DB_COLUMN_PREFIXid
      INTEGER
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXmimeType
      VARCHAR(
      
	  128
	
      )
    
      ,
    DB_COLUMN_PREFIXsize
      INTEGER
    
    );

  
    ALTER TABLE DB_TABLE_PREFIXDataItem
    ADD PRIMARY KEY (DB_COLUMN_PREFIXid);
    

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'DataItem',
      1,
      0
      );

  