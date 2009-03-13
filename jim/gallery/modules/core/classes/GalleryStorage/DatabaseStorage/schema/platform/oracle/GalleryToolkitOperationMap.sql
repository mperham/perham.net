
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXTkOperatnMap (
  DB_COLUMN_PREFIXname
      VARCHAR2(
       128 
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXparametersCrc
      VARCHAR2(
       32 
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXoutputMimeType
      VARCHAR2(
       128 
      )
    
      ,
    DB_COLUMN_PREFIXdescription
      VARCHAR2(
       255 
      )
    
    );

  
    ALTER TABLE DB_TABLE_PREFIXTkOperatnMap
      ADD PRIMARY KEY (DB_COLUMN_PREFIXname)
  ;
  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'TkOperatnMap',
      1,
      0
      );

  