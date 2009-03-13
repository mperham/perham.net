
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXEntity (
  DB_COLUMN_PREFIXid
      INTEGER
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXcreationTimestamp
      INTEGER
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXisLinkable
      SMALLINT
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXlinkId
      INTEGER
    
      ,
    DB_COLUMN_PREFIXmodificationTimestamp
      INTEGER
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXserialNumber
      INTEGER
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXentityType
      VARCHAR(
      
	  32
	
      )
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXonLoadHandlers
      VARCHAR(
      
	  128
	
      )
    
    );

  
    CREATE INDEX DB_TABLE_PREFIXEntity_76255
    ON DB_TABLE_PREFIXEntity
    (DB_COLUMN_PREFIXcreationTimestamp);

  
    CREATE INDEX DB_TABLE_PREFIXEntity_35978
    ON DB_TABLE_PREFIXEntity
    (DB_COLUMN_PREFIXisLinkable);

  
    CREATE INDEX DB_TABLE_PREFIXEntity_63025
    ON DB_TABLE_PREFIXEntity
    (DB_COLUMN_PREFIXmodificationTimestamp);

  
    CREATE INDEX DB_TABLE_PREFIXEntity_60702
    ON DB_TABLE_PREFIXEntity
    (DB_COLUMN_PREFIXserialNumber);

  
    ALTER TABLE DB_TABLE_PREFIXEntity
    ADD PRIMARY KEY (DB_COLUMN_PREFIXid);
    

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'Entity',
      1,
      1
      );

  