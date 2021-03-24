/*
CLASE MOTOR


Métodos: 
arranca() --> Arranca el motor
*/

class Motor
{

    int _ledDer;
    int _ledIzq;
    int _num_repeticiones = 5;
    int _tiempo_lavado = 100;   //2 seg gira el Motor
    int _tiempo_descanso = 400; //4 seg descansa

    int _minutos_motor = 1;

public:
    Motor(int ledIzq, int ledDer)
    {
        _ledIzq = ledIzq;
        _ledDer = ledDer;
        pinMode(_ledIzq, OUTPUT);
        pinMode(_ledDer, OUTPUT);
    }

    void arrancar()
    {
        delay(1000); // Retardo para inicio del motor
        for (int _contador2 = 1; _contador2 <= _minutos_motor; _contador2++)
        {
            //El sig CICLO FOR = 1 min
            for (int _contador = 1; _contador <= _num_repeticiones; _contador++)
            {
                digitalWrite(_ledDer, HIGH); // Gira Motor a la DERECHA x 2 seg
                delay(_tiempo_lavado);
                digitalWrite(_ledDer, LOW); //DESCONECTA MOTOR x 4 seg
                delay(_tiempo_descanso);

                digitalWrite(_ledIzq, HIGH); //Gira Motor a la IZQUIERDA x 2 seg
                delay(_tiempo_lavado);
                digitalWrite(_ledIzq, LOW); //DESCONECTA MOTOR x 4 seg
                delay(_tiempo_descanso);
            }
        }
    }
};