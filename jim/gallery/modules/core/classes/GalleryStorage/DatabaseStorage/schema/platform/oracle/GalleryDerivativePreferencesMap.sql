
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXDerivativePrefsMap (
  DB_COLUMN_PREFIXitemId
      INTEGER
    
      ,
    DB_COLUMN_PREFIXorder
      INTEGER
    
      ,
    DB_COLUMN_PREFIXderivativeType
      INTEGER
    
      ,
    DB_COLUMN_PREFIXderivativeOperations
      VARCHAR2(
       255 
      )
    
    );

  
    CREATE INDEX DB_TABLE_PREFIXDerivativePrefsMap_75985
    ON DB_TABLE_PREFIXDerivativePrefsMap
    (DB_COLUMN_PREFIXitemId);
  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'DerivativePrefsMap',
      1,
      0
      );

  