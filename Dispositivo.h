/*
Clase Dispositivo.
----- Clase generica para valvulas, bomba y clutch ----

USO:
----- Encenderá y apagará ciertos dispositivos electricos ----

Métodos:
energizar() --> Energiza el dispositivo
apagar() --> Apaga el dispositivo
*/

class Dispositivo
{
    int _ledPin;

public:
    Dispositivo(int ledPin)
    {
        _ledPin = ledPin;
        pinMode(_ledPin, OUTPUT);
    }

    void energizar()
    {
        digitalWrite(_ledPin, HIGH);
    }

    void apagar()
    {
        digitalWrite(_ledPin, LOW);
    }
};