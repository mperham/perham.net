
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXTkOperatnParameterMap (
  DB_COLUMN_PREFIXoperationName
      varchar(
      
	  128
	
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXposition
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXtype
      varchar(
      
	  128
	
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXdescription
      varchar(
      
	  255
	
      )
    
    ,
  
    INDEX DB_TABLE_PREFIXTkOperatnParameterMap_2014 (DB_COLUMN_PREFIXoperationName)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'TkOperatnParameterMap',
      1,
      0
      );

  