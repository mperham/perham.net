
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXRewriteMap (
  DB_COLUMN_PREFIXpattern
      VARCHAR(
      
          255
        
      )
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXmodule
      VARCHAR(
      
          32
        
      )
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXruleId
      INTEGER
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXmatch
      VARCHAR(
      
          128
        
      )
    
    );

  
    ALTER TABLE DB_TABLE_PREFIXRewriteMap
    ADD PRIMARY KEY (DB_COLUMN_PREFIXpattern);
    

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'RewriteMap',
      1,
      0
      );

  