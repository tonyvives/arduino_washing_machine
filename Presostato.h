/*
Clase presostato.

USO:
----- EL PRESOSTATO SIRVE PARA SABER SI HAY AGUA O NO ----

Propiedades:
estado -> 0 - presostato abierto // 1 - presostato cerrado
estado_agua -> 0 no hay agua, 1 hay agua.

Métodos:
abierto() -> revisa si el presostato está abierto
cerrado() -> Revisa si el presostato está cerrado
*/

class Presostato
{

    int _ledPin;

public:
    int estado = 0;
    int estado_agua = 0;
    Presostato(int ledPin)
    {
        _ledPin = ledPin;
        pinMode(_ledPin, INPUT);
    }

    bool abierto()
    {
        estado = 0;
        estado_agua = 0;
        return !digitalRead(_ledPin);
    }

    bool cerrado()
    {

        estado = 1;
        estado_agua = 1;
        return digitalRead(_ledPin);
    }
};