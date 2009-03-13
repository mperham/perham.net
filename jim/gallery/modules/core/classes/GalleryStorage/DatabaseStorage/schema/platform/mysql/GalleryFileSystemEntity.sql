
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXFileSystemEntity (
  DB_COLUMN_PREFIXid
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXpathComponent
      varchar(
      
	  128
	
      )
    
    ,
  
      PRIMARY KEY (DB_COLUMN_PREFIXid)
    
    ,
  
    INDEX DB_TABLE_PREFIXFileSystemEntity_3406 (DB_COLUMN_PREFIXpathComponent)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'FileSystemEntity',
      1,
      0
      );

  