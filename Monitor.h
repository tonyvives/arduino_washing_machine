/*
CLASE MONITOR

MONITOR = LEDS PARA "MONITOREAR":
    - BOTONES
    - BOMBA
    - VALVULA
    - CLUTCH
    - MOTORES

*/

class Monitor
{

    int _ledPin;

public:
    int estado = 0;
    Monitor(int ledPin)
    {
        _ledPin = ledPin;
        pinMode(_ledPin, OUTPUT);
    }

    void encendido()
    {
        digitalWrite(_ledPin, HIGH);
        estado = 1;
    }

    void apagado()
    {
        digitalWrite(_ledPin, LOW);
        estado = 0;
    }
};