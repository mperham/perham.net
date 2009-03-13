
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXExifPropertiesMap (
  DB_COLUMN_PREFIXproperty
      VARCHAR2(
       128 
      )
    
      ,
    DB_COLUMN_PREFIXviewMode
      INTEGER
    
      ,
    DB_COLUMN_PREFIXsequence
      INTEGER
    
    );

  
    ALTER TABLE DB_TABLE_PREFIXExifPropertiesMap
      ADD UNIQUE (DB_COLUMN_PREFIXproperty
        ,
      DB_COLUMN_PREFIXviewMode)
  ;
  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'ExifPropertiesMap',
      1,
      0
      );

  