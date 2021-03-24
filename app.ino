/*
PROGRAMA LAVADORA V.0.0.1

NOTAS:
    - NO HAY BOTON DE PAUSA O RESET, UNA VEZ QUE ARRANCA, YA NO SE PUEDE DETENER

TODO:

    - ASIGNAR "TIEMPO" AL MOTOR CUANDO SE LLAME A LA FUNCIÓN.
    - AGREGAR UN BOTON DE "PAUSA" O "RESET".
    - AGREGAR OPCIÓN 4: LAVADO - ENJUAGADO.
    - AGREGAR OPCIÓN 5: LAVADO - ENJUAGADO - CENTRIFUGADO.

*/

#include "Boton.h"
#include "Monitor.h"
#include "Presostato.h"
#include "Dispositivo.h"
#include "Motor.h"

///////////////////////////////// PINES /////////////////////////////////////

// PINES BOTONES
int PIN_BOTON_LAVADO = 13; // 8
int PIN_BOTON_ENJUAGAR = 11;
int PIN_BOTON_CENTRIFUGAR = A1;
int PIN_BOTON_INICIO = 8; //13
int PIN_PRESOSTATO = 9;

// PINES LEDS
int PIN_MONITOR_LAVADO = 12;
int PIN_MONITOR_ENJUAGAR = 10;
int PIN_MONITOR_CENTRIFUGAR = A2;
int PIN_MONITOR_INICIO = A0;
int PIN_MOTOR_DERECHO = 2;
int PIN_MOTOR_IZQUIERDO = 3;
int PIN_CLUTCH = 4;
int PIN_BOMBA = 5;
int PIN_ELECTROVALVULA = 6;

///////////////////////////////// PINES /////////////////////////////////////

// INSTANCIANDO BOTONES
Boton boton_inicio(PIN_BOTON_INICIO);
Boton boton_lavado(PIN_BOTON_LAVADO);
Boton boton_enjuagar(PIN_BOTON_ENJUAGAR);
Boton boton_centrifugar(PIN_BOTON_CENTRIFUGAR);

// INSTANCIANDO PRESOSTATO
Presostato presostato(PIN_PRESOSTATO);

// INSTANCIANDO MONITORES
Monitor monitor_lavado(PIN_MONITOR_LAVADO);
Monitor monitor_enjuagar(PIN_MONITOR_ENJUAGAR);
Monitor monitor_centrifugar(PIN_MONITOR_CENTRIFUGAR);
Monitor monitor_inicio(PIN_MONITOR_INICIO);

// INSTANCIANDO MOTOR
Motor motor(PIN_MOTOR_DERECHO, PIN_MOTOR_IZQUIERDO);

// INSTANCIANDO DISPOSITIVO
Dispositivo clutch(PIN_CLUTCH);
Dispositivo electrovalvula(PIN_ELECTROVALVULA);
Dispositivo bomba(PIN_BOMBA);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
inicio:
    Serial.println("Hola mundo");
    // OPCION DE LAVADO. //UN BOTON ES PULSADO Y LOS OTROS ESTÁN EN 0
    if (boton_lavado.es_pulsado() == true)
    {
        monitor_lavado.encendido();

        // DOS BOTONES APRETADOS PARA QUE INICIE EL CICLO DE LAVADO.
        if (boton_lavado.es_pulsado() == true && boton_inicio.es_pulsado() == true)
        {
            monitor_inicio.encendido();
            // AQUÍ INICIAN LAS INSTRUCCIONES PARA LAVAR.
            //Serial.println("Listo para lavar");
            delay(500); // delay para cuando entre ciclo de lavado

            ciclo_lavado();
            goto inicio; // TERMINA DE LAVAR Y REGRESA AL INICIO
        }
        else
        {
            monitor_inicio.apagado();
        }
    }
    else if (boton_lavado.es_pulsado() == false)
    {
        monitor_lavado.apagado();
        monitor_inicio.apagado();
        boton_inicio.estado = 0;
    }

    // OPCION DE ENJUAGAR.
    if (boton_enjuagar.es_pulsado() == true)
    {
        monitor_enjuagar.encendido();

        // DOS BOTONES APRETADOS PARA QUE INICIE EL CICLO DE ENJUAGADO.
        if (boton_enjuagar.es_pulsado() == true && boton_inicio.es_pulsado() == true)
        {
            monitor_inicio.encendido();
            // AQUÍ INICIAN LAS INSTRUCCIONES PARA LAVAR. // CICLO DE ENJUAGADO
            ciclo_enjuagado();
            goto inicio;
        }
        else
        {
            monitor_inicio.apagado();
        }
    }
    else if (boton_enjuagar.es_pulsado() == false)
    {
        monitor_enjuagar.apagado();
        monitor_inicio.apagado();
        boton_inicio.estado = 0;
    }

    // OPCION DE CENTRIFUGADO
    if (boton_centrifugar.es_pulsado() == true)
    {
        monitor_centrifugar.encendido();

        if (boton_centrifugar.es_pulsado() == true && boton_inicio.es_pulsado())
        {
            monitor_inicio.encendido();

            //Iniciará ciclo de centrifugado
            ciclo_centrifugado();
        }
        else
        {
            monitor_inicio.apagado();
        }
    }
    else if (boton_centrifugar.es_pulsado() == false)
    {
        monitor_centrifugar.apagado();
        monitor_inicio.apagado();
        boton_inicio.estado = 0;
    }

} // FIN DEL LOOP()

void ciclo_lavado()
{
    while (boton_lavado.es_pulsado() == true && boton_inicio.es_pulsado() == true)
    {
        // SI ESTÁ VACÍO LLENA
        while (presostato.abierto() == true)
        {
            electrovalvula.energizar();
            Serial.println("Cargando agua");
        }
        // SI ESTÁ LLENO, EMPIEZA A TRABAJAR.
        electrovalvula.apagar();
        clutch.energizar();
        motor.arrancar();
        clutch.apagar();
        while (presostato.cerrado() == true)
        {
            bomba.energizar();
            Serial.println("SACANDO AGUA!!!!!!!!!!");
        }
        bomba.apagar();

        boton_inicio.estado = 0;
        boton_lavado.estado = 0;
    }
}

void ciclo_enjuagado()
{
    while (boton_enjuagar.es_pulsado() == true && boton_inicio.es_pulsado() == true)
    {
        // SI ESTÁ VACÍO LLENA
        while (presostato.abierto() == true)
        {
            electrovalvula.energizar();
            Serial.println("Cargando agua");
        }
        // SI ESTÁ LLENO, EMPIEZA A TRABAJAR.
        electrovalvula.apagar();
        clutch.energizar();
        motor.arrancar();
        clutch.apagar();
        while (presostato.cerrado() == true)
        {
            bomba.energizar();
            Serial.println("SACANDO AGUA!!!!!!!!!!");
        }
        bomba.apagar();

        boton_inicio.estado = 0;
        boton_enjuagar.estado = 0;
    }
}

void ciclo_centrifugado()
{
inicio_centrifugar:
    while (boton_centrifugar.es_pulsado() == true && boton_inicio.es_pulsado())
    {
    evaluar_ciclo_centrifugado:
        Serial.println("Esperando instrucciones de centrifugado");

        //Primer if para revisar el primer estado de la lavadora al momento de centrifugar
        if (presostato.cerrado() == true)
        {
            Serial.println("hay agua");
            while (presostato.cerrado() == true) //Se activa la bomba mientras la tina tenga agua
            {
                bomba.energizar(); //Sacar agua
                Serial.println("Sacando agua");
            }
            bomba.apagar();
            goto evaluar_ciclo_centrifugado;
        }
        else if (presostato.abierto() == true) //LISTOS PARA CENTRIFUGAR
        {

            while (presostato.abierto() == true)
            {
                bomba.energizar();
                motor.arrancar();
                bomba.apagar();
                boton_inicio.estado = 0;
                boton_centrifugar.estado = 0;
                goto inicio_centrifugar;
            }
        }
    }
}