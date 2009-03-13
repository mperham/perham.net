
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXTkPropertyMimeTypeMap (
  DB_COLUMN_PREFIXpropertyName
      varchar(
      
	  128
	
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXtoolkitId
      varchar(
      
	  128
	
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXmimeType
      varchar(
      
	  128
	
      )
    
    NOT NULL
  
    ,
  
    INDEX DB_TABLE_PREFIXTkPropertyMimeTypeMap_52881 (DB_COLUMN_PREFIXpropertyName)
    
      ,
    
    INDEX DB_TABLE_PREFIXTkPropertyMimeTypeMap_79463 (DB_COLUMN_PREFIXmimeType)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'TkPropertyMimeTypeMap',
      1,
      0
      );

  