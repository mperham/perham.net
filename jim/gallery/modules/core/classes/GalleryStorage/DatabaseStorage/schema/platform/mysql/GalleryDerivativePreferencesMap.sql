
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXDerivativePrefsMap (
  DB_COLUMN_PREFIXitemId
      int(11)
    
      ,
    DB_COLUMN_PREFIXorder
      int(11)
    
      ,
    DB_COLUMN_PREFIXderivativeType
      int(11)
    
      ,
    DB_COLUMN_PREFIXderivativeOperations
      varchar(
      
	  255
	
      )
    
    ,
  
    INDEX DB_TABLE_PREFIXDerivativePrefsMap_75985 (DB_COLUMN_PREFIXitemId)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'DerivativePrefsMap',
      1,
      0
      );

  