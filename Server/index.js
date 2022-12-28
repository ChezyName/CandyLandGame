import { Server } from "socket.io";

const io = new Server(7777);

io.on("connection",(socket) => {
    console.log(socket);
});