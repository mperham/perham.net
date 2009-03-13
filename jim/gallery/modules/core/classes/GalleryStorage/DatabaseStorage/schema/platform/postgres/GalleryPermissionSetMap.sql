
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXPermissionSetMap (
  DB_COLUMN_PREFIXmodule
      VARCHAR(
      
	  128
	
      )
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXpermission
      VARCHAR(
      
	  128
	
      )
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXdescription
      VARCHAR(
      
	  255
	
      )
    
      ,
    DB_COLUMN_PREFIXbits
      BIT(32)
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXflags
      INTEGER
    
      NOT NULL
    
    );

  
    CREATE UNIQUE INDEX DB_TABLE_PREFIXPermissionSetMap_18058
    ON DB_TABLE_PREFIXPermissionSetMap
    (DB_COLUMN_PREFIXpermission);
    

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'PermissionSetMap',
      1,
      0
      );

  