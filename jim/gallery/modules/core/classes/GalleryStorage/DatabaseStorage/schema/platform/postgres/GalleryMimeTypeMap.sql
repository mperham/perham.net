
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXMimeTypeMap (
  DB_COLUMN_PREFIXextension
      VARCHAR(
      
	  32
	
      )
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXmimeType
      VARCHAR(
      
	  32
	
      )
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXviewable
      SMALLINT
    
    );

  
    ALTER TABLE DB_TABLE_PREFIXMimeTypeMap
    ADD PRIMARY KEY (DB_COLUMN_PREFIXextension);
    

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'MimeTypeMap',
      1,
      0
      );

  