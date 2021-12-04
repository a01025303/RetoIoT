# Configuracion que nos va a permitir conectarnos a MySQL

from sqlalchemy import create_engine, MetaData

engine = create_engine("mysql+pymysql://root:123@localhost:3306/IOT_DB")

meta = MetaData()

# Objeto de conexion
con = engine.connect()
