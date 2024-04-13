#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define TOPIC "Fecha y hora"

int main() {
    void *context = zmq_ctx_new();
    void *publisher = zmq_socket(context, ZMQ_PUB);
    zmq_bind(publisher, "tcp://*:5555");

    int message_num = 0;

    while (1) {
        // Obtener la hora actual
        time_t rawtime;
        struct tm *timeinfo;
        char time_str[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);

        // Construir el mensaje
        char message[256];
        sprintf(message, "%s - Mensaje #%d", time_str, message_num);

        // Envía el tópico y el mensaje
        zmq_send(publisher, TOPIC, strlen(TOPIC), ZMQ_SNDMORE);
        zmq_send(publisher, message, strlen(message), 0);
        
        message_num += 1;
        printf("Enviado hora actal - Mensaje #%d\n", message_num);
        
        sleep(1); // Espera un segundo antes de enviar el siguiente mensaje
    }

    zmq_close(publisher);
    zmq_ctx_destroy(context);

    return 0;
}
