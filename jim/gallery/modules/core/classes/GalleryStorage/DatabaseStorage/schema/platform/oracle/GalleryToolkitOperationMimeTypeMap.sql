
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXTkOperatnMimeTypeMap (
  DB_COLUMN_PREFIXoperationName
      VARCHAR2(
       128 
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXtoolkitId
      VARCHAR2(
       128 
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXmimeType
      VARCHAR2(
       128 
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXpriority
      INTEGER
    
    NOT NULL
  
    );

  
    CREATE INDEX DB_TABLE_PREFIXTkOperatnMimeTypeMap_2014
    ON DB_TABLE_PREFIXTkOperatnMimeTypeMap
    (DB_COLUMN_PREFIXoperationName);
  
    CREATE INDEX DB_TABLE_PREFIXTkOperatnMimeTypeMap_79463
    ON DB_TABLE_PREFIXTkOperatnMimeTypeMap
    (DB_COLUMN_PREFIXmimeType);
  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'TkOperatnMimeTypeMap',
      1,
      0
      );

  