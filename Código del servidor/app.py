from fastapi import FastAPI
from routes.crud import measurementRouter, deviceRouter, diagnosticRouter, roomRouter, sensorRouter
#from config.openapi import tags_metadata

# Aplicacion / se el modulo de fast api para crear un servidor (se corre con uvicorn app:app --reload)
app = FastAPI()

# Se incluyen las rutas que vienen de user
app.include_router(measurementRouter)
app.include_router(deviceRouter)
app.include_router(diagnosticRouter)
app.include_router(roomRouter)
app.include_router(sensorRouter)
