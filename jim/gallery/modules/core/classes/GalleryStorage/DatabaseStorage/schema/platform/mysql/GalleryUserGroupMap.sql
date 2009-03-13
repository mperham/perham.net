
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXUserGroupMap (
  DB_COLUMN_PREFIXuserId
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXgroupId
      int(11)
    
    NOT NULL
  
    ,
  
    INDEX DB_TABLE_PREFIXUserGroupMap_69068 (DB_COLUMN_PREFIXuserId)
    
      ,
    
    INDEX DB_TABLE_PREFIXUserGroupMap_89328 (DB_COLUMN_PREFIXgroupId)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'UserGroupMap',
      1,
      0
      );

  