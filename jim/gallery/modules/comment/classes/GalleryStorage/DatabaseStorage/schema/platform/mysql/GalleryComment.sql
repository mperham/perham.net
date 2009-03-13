
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXComment (
  DB_COLUMN_PREFIXid
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXcommenterId
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXhost
      varchar(
      
          128
        
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXsubject
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXcomment
      text
    
      ,
    DB_COLUMN_PREFIXdate
      int(11)
    
    NOT NULL
  
    , 
  
      PRIMARY KEY (DB_COLUMN_PREFIXid)
    
    , 
  
    INDEX (DB_COLUMN_PREFIXdate)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'Comment',
      1,
      0
      );

  