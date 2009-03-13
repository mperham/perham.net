
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXExternalIdMap (
  DB_COLUMN_PREFIXexternalId
      VARCHAR(
      
	  128
	
      )
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXentityType
      VARCHAR(
      
	  32
	
      )
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXentityId
      INTEGER
    
      NOT NULL
    
    );

  
    ALTER TABLE DB_TABLE_PREFIXExternalIdMap
    ADD PRIMARY KEY (DB_COLUMN_PREFIXexternalId
	,
      DB_COLUMN_PREFIXentityType);
    

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'ExternalIdMap',
      1,
      0
      );

  