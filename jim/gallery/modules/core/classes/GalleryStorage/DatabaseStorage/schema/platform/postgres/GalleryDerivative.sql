
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXDerivative (
  DB_COLUMN_PREFIXid
      INTEGER
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXderivativeSourceId
      INTEGER
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXderivativeOperations
      VARCHAR(
      
	  255
	
      )
    
      ,
    DB_COLUMN_PREFIXderivativeOrder
      INTEGER
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXderivativeSize
      INTEGER
    
      ,
    DB_COLUMN_PREFIXderivativeType
      INTEGER
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXmimeType
      VARCHAR(
      
	  128
	
      )
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXpostFilterOperations
      VARCHAR(
      
	  255
	
      )
    
      ,
    DB_COLUMN_PREFIXisBroken
      SMALLINT
    
    );

  
    CREATE INDEX DB_TABLE_PREFIXDerivative_85338
    ON DB_TABLE_PREFIXDerivative
    (DB_COLUMN_PREFIXderivativeSourceId);

  
    CREATE INDEX DB_TABLE_PREFIXDerivative_25243
    ON DB_TABLE_PREFIXDerivative
    (DB_COLUMN_PREFIXderivativeOrder);

  
    CREATE INDEX DB_TABLE_PREFIXDerivative_97216
    ON DB_TABLE_PREFIXDerivative
    (DB_COLUMN_PREFIXderivativeType);

  
    ALTER TABLE DB_TABLE_PREFIXDerivative
    ADD PRIMARY KEY (DB_COLUMN_PREFIXid);
    

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'Derivative',
      1,
      1
      );

  