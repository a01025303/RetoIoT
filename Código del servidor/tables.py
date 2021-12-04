from sqlalchemy import Table, Column, engine
from sqlalchemy.sql.sqltypes import Integer, String
from config.db import meta, engine

#Tablas (se toman del engine las tablas ya creadas previamente en la terminal con autoload_with=engine)
measurement = Table('Measurement', meta, autoload_with=engine)
sensor = Table('Sensor', meta, autoload_with=engine)
device = Table('Device', meta, autoload_with=engine)
diagnostic = Table('Diagnostic', meta, autoload_with=engine)
room = Table('Room', meta, autoload_with=engine)

#Una vez conectado a sql se generan todas las tablas
meta.create_all(engine)
