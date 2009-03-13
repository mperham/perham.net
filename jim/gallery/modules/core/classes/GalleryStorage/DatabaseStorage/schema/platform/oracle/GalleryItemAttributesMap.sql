
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXItemAttributesMap (
  DB_COLUMN_PREFIXitemId
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXviewCount
      INTEGER
    
      ,
    DB_COLUMN_PREFIXorderWeight
      INTEGER
    
      ,
    DB_COLUMN_PREFIXparentSequence
      VARCHAR2(
       255 
      )
    
    );

  
    CREATE INDEX DB_TABLE_PREFIXItemAttributesMap_95270
    ON DB_TABLE_PREFIXItemAttributesMap
    (DB_COLUMN_PREFIXparentSequence);
  
    ALTER TABLE DB_TABLE_PREFIXItemAttributesMap
      ADD PRIMARY KEY (DB_COLUMN_PREFIXitemId)
  ;
  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'ItemAttributesMap',
      1,
      0
      );

  