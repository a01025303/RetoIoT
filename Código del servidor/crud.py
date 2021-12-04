from fastapi import APIRouter
from sqlalchemy.sql.expression import select, update
from sqlalchemy.sql.sqltypes import DateTime #permite definir subrutas (rutas por separado)
from config.db import con
from models.tables import measurement, device, diagnostic, room, sensor
from schemas.schemas import Measurement, Device, Diagnostic, Room, Sensor

#Sub objeto -> funciona de forma similar a app
measurementRouter = APIRouter()
deviceRouter = APIRouter()
diagnosticRouter = APIRouter()
roomRouter = APIRouter()
sensorRouter = APIRouter()

#Rutas tipicas de los crud (create, read, update, delete)

# CRUD -> Measurement
@measurementRouter.get("/measurement")
async def get_measurement():
    return con.execute(measurement.select()).fetchall() #Se realiza un select all de la tabla users

@measurementRouter.post("/measurement")
def create_measurement(measurementTable: Measurement):
    new_measurement = {
        "idMeasurement": measurementTable.idMeasurement, 
        "Value":measurementTable.Value, 
        "DateTime": measurementTable.DateTime, 
        "idSensor": measurementTable.idSensor }

    print(new_measurement)
    result = con.execute(measurement.insert().values(new_measurement))
    print(result)
    return "New User!!!"


@measurementRouter.put("/measurement/{idMeasurement}")
def update_measurement(measurementTable: Measurement, idMeasurement: int):
    updated_data = {
        "idMeasurement": measurementTable.idMeasurement, 
        "Value":measurementTable.Value, 
        "DateTime": measurementTable.DateTime, 
        "idSensor": measurementTable.idSensor }

    con.execute(measurement.update().values(updated_data).where(measurement.c.idMeasurement == idMeasurement))
    return con.execute(measurement.select().where(measurement.c.idMeasurement == idMeasurement)).first()


@measurementRouter.delete("/measurement/{idMeasurement}")
async def delete_measurement(idMeasurement: int):
    con.execute(measurement.delete().where(measurement.c.idMeasurement == idMeasurement))
    return con.execute(measurement.select()).fetchall()


# CRUD -> Device
@deviceRouter.get("/device")
async def get_device():
    return con.execute(device.select()).fetchall() #Se realiza un select all de la tabla users

@deviceRouter.post("/device")
def create_device(deviceTable: Device):
    new_device = {
        "idDevice": deviceTable.idDevice, 
        "MAC":deviceTable.MAC, 
        "idRoom": deviceTable.idRoom, 
        "idSensor": deviceTable.idSensor }

    print(new_device)
    result = con.execute(device.insert().values(new_device))
    print(result)
    return "New Device!!!"


@deviceRouter.put("/device/{idDevice}")
def update_device(deviceTable: Device, idDevice: int):
    updated_data = {
        "idDevice": deviceTable.idDevice, 
        "MAC":deviceTable.MAC, 
        "idRoom": deviceTable.idRoom, 
        "idSensor": deviceTable.idSensor }

    con.execute(device.update().values(updated_data).where(device.c.idDevice == idDevice))
    return con.execute(device.select().where(device.c.idDevice == idDevice)).first()


@deviceRouter.delete("/device/{idDevice}")
async def delete_device(idDevice: int):
    con.execute(device.delete().where(device.c.idDevice == idDevice))
    return con.execute(device.select()).fetchall()

# CRUD -> Diagnostic
@diagnosticRouter.get("/diagnostic")
async def get_diagnostic():
    return con.execute(diagnostic.select()).fetchall() #Se realiza un select all de la tabla users

@diagnosticRouter.post("/diagnostic")
def create_diagnostic(diagnosticTable: Diagnostic):
    new_diagnostic = {
        "idDiagnostic": diagnosticTable.idDevice, 
        "HighAlert":diagnosticTable.HighAlert, 
        "LowAlert": diagnosticTable.LowAlert,
        "NormalLevel": diagnosticTable.NormalLevel, 
        "idMeasurement": diagnosticTable.idMeasurement }

    print(new_diagnostic)
    result = con.execute(diagnostic.insert().values(new_diagnostic))
    print(result)
    return "New Diagnostic!!!"


@diagnosticRouter.put("/diagnostic/{idDiagnostic}")
def update_diagnostic(diagnosticTable: Diagnostic, idDiagnostic: int):
    updated_data = {
        "idDiagnostic": diagnosticTable.idDevice, 
        "HighAlert":diagnosticTable.HighAlert, 
        "LowAlert": diagnosticTable.LowAlert,
        "NormalLevel": diagnosticTable.NormalLevel, 
        "idMeasurement": diagnosticTable.idMeasurement }

    con.execute(diagnostic.update().values(updated_data).where(diagnostic.c.idDiagnostic == idDiagnostic))
    return con.execute(device.select().where(device.c.idDiagnostic == idDiagnostic)).first()


@diagnosticRouter.delete("/diagnostic/{idDiagnostic}")
async def delete_diagnostic(idDiagnostic: int):
    con.execute(diagnostic.delete().where(diagnostic.c.idDiagnostic == idDiagnostic))
    return con.execute(diagnostic.select()).fetchall()


# CRUD -> Room
@roomRouter.get("/room")
async def get_room():
    return con.execute(room.select()).fetchall() #Se realiza un select all de la tabla users

@roomRouter.post("/room")
def create_room(roomTable: Room):
    new_room = {
        "idRoom": roomTable.idRoom, 
        "RoomLabel":roomTable.RoomLabel, 
        "mts2": roomTable.mts2 }

    print(new_room)
    result = con.execute(room.insert().values(new_room))
    print(result)
    return "New Room!!!"


@roomRouter.put("/room/{idRoom}")
def update_room(roomTable: Room, idRoom: int):
    updated_data = {
        "idRoom": roomTable.idRoom, 
        "RoomLabel":roomTable.RoomLabel, 
        "mts2": roomTable.mts2 }

    con.execute(room.update().values(updated_data).where(room.c.idRoom == idRoom))
    return con.execute(room.select().where(room.c.idRoom == idRoom)).first()


@roomRouter.delete("/room/{idRoom}")
async def delete_room(idRoom: int):
    con.execute(room.delete().where(room.c.idRoom == idRoom))
    return con.execute(room.select()).fetchall()

# CRUD -> Sensor
@roomRouter.get("/sensor")
async def get_sensor():
    return con.execute(sensor.select()).fetchall() 

@roomRouter.post("/sensor")
def create_sensor(sensorTable: Sensor):
    new_sensor = {
        "idSensor": sensorTable.idSensor, 
        "Brand": sensorTable.Brand, 
        "Model": sensorTable.Model,
        "MGas": sensorTable.MGas,
        "Units": sensorTable.Units }

    print(new_sensor)
    result = con.execute(sensor.insert().values(new_sensor))
    print(result)
    return "New Sensor!!!"


@roomRouter.put("/sensor/{idSensor}")
def update_sensor(sensorTable: Sensor, idSensor: int):
    updated_data = {
        "idSensor": sensorTable.idSensor, 
        "Brand": sensorTable.Brand, 
        "Model": sensorTable.Model,
        "MGas": sensorTable.MGas,
        "Units": sensorTable.Units }

    con.execute(sensor.update().values(updated_data).where(sensor.c.idSensor == idSensor))
    return con.execute(sensor.select().where(sensor.c.idSensor == idSensor)).first()


@roomRouter.delete("/sensor/{idSensor}")
async def delete_sensor(idSensor: int):
    con.execute(sensor.delete().where(sensor.c.idSensor == idSensor))
    return con.execute(sensor.select()).fetchall()
