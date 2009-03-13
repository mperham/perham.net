
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXUnknownItem (
  DB_COLUMN_PREFIXid
      INTEGER
    
    NOT NULL
  
    );

  
    ALTER TABLE DB_TABLE_PREFIXUnknownItem
      ADD PRIMARY KEY (DB_COLUMN_PREFIXid)
  ;
  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'UnknownItem',
      1,
      0
      );

  