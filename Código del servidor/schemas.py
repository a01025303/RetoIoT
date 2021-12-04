from datetime import datetime
from pydantic import BaseModel
from typing import Optional
from sqlalchemy.sql.sqltypes import DateTime, String

class Measurement(BaseModel):
    idMeasurement: int
    Value: float
    DateTime: datetime #revisar como poner timestamp
    idSensor: int

class Sensor(BaseModel):
    idSensor: int
    Brand: str
    Model: str 
    MGas: str
    Units: str

class Device(BaseModel):
    idDevice: int
    MAC: str
    idRoom: int 
    idSensor: int

class Room(BaseModel):
    idRoom: int
    RoomLabel: str
    mts2: float 

class Diagnostic(BaseModel):
    idDiagnostic: int
    HighAlert: bool
    LowAlert: bool 
    NormalLevel: bool
    idMeasurement: int
