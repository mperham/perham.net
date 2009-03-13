
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXAccessSubscriberMap (
  DB_COLUMN_PREFIXitemId
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXaccessListId
      INTEGER
    
    NOT NULL
  
    );

  
    CREATE INDEX DB_TABLE_PREFIXAccessSubscriberMap_83732
    ON DB_TABLE_PREFIXAccessSubscriberMap
    (DB_COLUMN_PREFIXaccessListId);
  
    ALTER TABLE DB_TABLE_PREFIXAccessSubscriberMap
      ADD PRIMARY KEY (DB_COLUMN_PREFIXitemId)
  ;
  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'AccessSubscriberMap',
      1,
      0
      );

  