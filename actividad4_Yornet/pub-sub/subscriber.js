
const TOPIC = "Fecha y hora"

const zmq = require("zeromq")
const config = require("../config")

async function run() {
    const sock = new zmq.Subscriber

    sock.connect(`tcp://${config.server_host}:5555`)
    sock.subscribe(TOPIC)
    console.log(`Subscriber conectado (?) al server "${config.server_host}" al tópico "${TOPIC}"`)

    for await (const [topic, msg] of sock) {
        console.log(`Recibido del tópico "${topic.toString()}" el mensaje ${msg.toString()}`)
    }
}

run()
