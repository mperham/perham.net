
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXComment (
  DB_COLUMN_PREFIXid
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXcommenterId
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXhost
      VARCHAR2(
       128 
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXsubject
      VARCHAR2(
       128 
      )
    
      ,
    DB_COLUMN_PREFIXcomment
      VARCHAR2(4000)
    
      ,
    DB_COLUMN_PREFIXdate
      INTEGER
    
    NOT NULL
  
    );

  
    CREATE INDEX DB_TABLE_PREFIXComment_95610
    ON DB_TABLE_PREFIXComment
    (DB_COLUMN_PREFIXdate);
  
    ALTER TABLE DB_TABLE_PREFIXComment
      ADD PRIMARY KEY (DB_COLUMN_PREFIXid)
  ;
  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'Comment',
      1,
      0
      );

  