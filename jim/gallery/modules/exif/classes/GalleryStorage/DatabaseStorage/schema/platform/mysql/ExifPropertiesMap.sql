
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXExifPropertiesMap (
  DB_COLUMN_PREFIXproperty
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXviewMode
      int(11)
    
      ,
    DB_COLUMN_PREFIXsequence
      int(11)
    
    , 
  
      UNIQUE KEY (DB_COLUMN_PREFIXproperty
        ,
      DB_COLUMN_PREFIXviewMode)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'ExifPropertiesMap',
      1,
      0
      );

  