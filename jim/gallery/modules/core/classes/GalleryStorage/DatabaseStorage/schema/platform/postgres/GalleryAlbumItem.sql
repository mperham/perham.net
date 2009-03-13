
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXAlbumItem (
  DB_COLUMN_PREFIXid
      INTEGER
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXtheme
      VARCHAR(
      
	  32
	
      )
    
      ,
    DB_COLUMN_PREFIXorderBy
      VARCHAR(
      
	  128
	
      )
    
      ,
    DB_COLUMN_PREFIXorderDirection
      VARCHAR(
      
	  32
	
      )
    
    );

  
    ALTER TABLE DB_TABLE_PREFIXAlbumItem
    ADD PRIMARY KEY (DB_COLUMN_PREFIXid);
    

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'AlbumItem',
      1,
      1
      );

  