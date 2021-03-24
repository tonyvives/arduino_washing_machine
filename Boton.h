/*
CLASE BOTON 

ESTADO = 0; SIGNIFICA QUE EL BOTON ESTÁ APAGADO, NO HA SIDO PULSADO
*/

class Boton
{

    int _pinBoton;
    int _buttonOld = 1;
    int _buttonNew;
    int tiempoDelay = 100;

    int _currentState;
    int _previousState;

public:
    int estado = 0;
    Boton(int pinBoton)
    {
        _pinBoton = pinBoton;
        pinMode(_pinBoton, INPUT);
    }

    bool es_pulsado()
    {
        _buttonNew = digitalRead((_pinBoton));
        if (_buttonOld == 0 && _buttonNew == 1)
        {
            if (estado == 0)
            {
                estado = 1;
            }
            else
            {
                estado = 0;
            }
        }
        _buttonOld = _buttonNew;
        delay(tiempoDelay);
        return estado;
    }
};
