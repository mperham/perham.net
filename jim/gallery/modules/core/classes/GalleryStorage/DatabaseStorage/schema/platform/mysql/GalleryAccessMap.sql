
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXAccessMap (
  DB_COLUMN_PREFIXaccessListId
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXuserId
      int(11)
    
      ,
    DB_COLUMN_PREFIXgroupId
      int(11)
    
      ,
    DB_COLUMN_PREFIXpermission
      int(11)
    
    NOT NULL
  
    ,
  
      UNIQUE KEY (DB_COLUMN_PREFIXaccessListId
	,
      DB_COLUMN_PREFIXuserId
	,
      DB_COLUMN_PREFIXgroupId)
    
    ,
  
    INDEX DB_TABLE_PREFIXAccessMap_83732 (DB_COLUMN_PREFIXaccessListId)
    
      ,
    
    INDEX DB_TABLE_PREFIXAccessMap_69068 (DB_COLUMN_PREFIXuserId)
    
      ,
    
    INDEX DB_TABLE_PREFIXAccessMap_89328 (DB_COLUMN_PREFIXgroupId)
    
      ,
    
    INDEX DB_TABLE_PREFIXAccessMap_18058 (DB_COLUMN_PREFIXpermission)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'AccessMap',
      1,
      0
      );

  