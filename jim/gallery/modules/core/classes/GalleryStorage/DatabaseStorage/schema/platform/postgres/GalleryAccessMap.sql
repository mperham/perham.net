
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXAccessMap (
  DB_COLUMN_PREFIXaccessListId
      INTEGER
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXuserId
      INTEGER
    
      ,
    DB_COLUMN_PREFIXgroupId
      INTEGER
    
      ,
    DB_COLUMN_PREFIXpermission
      BIT(32)
    
      NOT NULL
    
    );

  
    CREATE INDEX DB_TABLE_PREFIXAccessMap_83732
    ON DB_TABLE_PREFIXAccessMap
    (DB_COLUMN_PREFIXaccessListId);

  
    CREATE INDEX DB_TABLE_PREFIXAccessMap_69068
    ON DB_TABLE_PREFIXAccessMap
    (DB_COLUMN_PREFIXuserId);

  
    CREATE INDEX DB_TABLE_PREFIXAccessMap_89328
    ON DB_TABLE_PREFIXAccessMap
    (DB_COLUMN_PREFIXgroupId);

  
    CREATE INDEX DB_TABLE_PREFIXAccessMap_18058
    ON DB_TABLE_PREFIXAccessMap
    (DB_COLUMN_PREFIXpermission);

  
    CREATE UNIQUE INDEX DB_TABLE_PREFIXAccessMap_33666
    ON DB_TABLE_PREFIXAccessMap
    (DB_COLUMN_PREFIXaccessListId
	,
      DB_COLUMN_PREFIXuserId
	,
      DB_COLUMN_PREFIXgroupId);
    

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'AccessMap',
      1,
      0
      );

  