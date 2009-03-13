
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXMaintenanceMap (
  DB_COLUMN_PREFIXrunId
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXtaskId
      varchar(
      
	  128
	
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXtimestamp
      int(11)
    
      ,
    DB_COLUMN_PREFIXsuccess
      int(1)
    
      ,
    DB_COLUMN_PREFIXdetails
      text
    
    ,
  
      PRIMARY KEY (DB_COLUMN_PREFIXrunId)
    
    ,
  
    INDEX DB_TABLE_PREFIXMaintenanceMap_21687 (DB_COLUMN_PREFIXtaskId)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'MaintenanceMap',
      1,
      0
      );

  