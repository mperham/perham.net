
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXItemAttributesMap (
  DB_COLUMN_PREFIXitemId
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXviewCount
      int(11)
    
      ,
    DB_COLUMN_PREFIXorderWeight
      int(11)
    
      ,
    DB_COLUMN_PREFIXparentSequence
      varchar(
      
	  255
	
      )
    
    NOT NULL
  
    ,
  
      PRIMARY KEY (DB_COLUMN_PREFIXitemId)
    
    ,
  
    INDEX DB_TABLE_PREFIXItemAttributesMap_95270 (DB_COLUMN_PREFIXparentSequence)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'ItemAttributesMap',
      1,
      0
      );

  