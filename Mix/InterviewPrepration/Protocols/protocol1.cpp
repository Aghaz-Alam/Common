// protocols_demo.cpp
#include <iostream>
#include <unistd.h>    // pipes, fork
#include <sys/ipc.h>   // shared memory
#include <sys/shm.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <cstring>
#include <chrono>
#include <vector>

void demo_pipe() {
    std::cout << "\n=== PIPE Demo ===\n";
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if(pid==0) {
        close(fd[1]);
        char buffer[64];
        read(fd[0], buffer, sizeof(buffer));
        std::cout << "Child received via pipe: " << buffer << "\n";
        _exit(0);
    } else {
        close(fd[0]);
        const char* msg = "Hello Pipe!";
        write(fd[1], msg, strlen(msg)+1);
        wait(nullptr);
    }
}

void demo_shared_memory() {
    std::cout << "\n=== SHARED MEMORY Demo ===\n";
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    char* shm = (char*)shmat(shmid, nullptr, 0);
    pid_t pid = fork();
    if(pid==0) {
        strcpy(shm, "Hello Shared Memory!");
        shmdt(shm);
        _exit(0);
    } else {
        sleep(1);
        std::cout << "Parent read: " << shm << "\n";
        shmdt(shm);
        shmctl(shmid, IPC_RMID, nullptr);
    }
}

void demo_socket() {
    std::cout << "\n=== TCP SOCKET Demo ===\n";
    std::thread server([](){
        int server_fd = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(9000);
        addr.sin_addr.s_addr = INADDR_ANY;
        bind(server_fd, (sockaddr*)&addr, sizeof(addr));
        listen(server_fd,1);
        int client_fd = accept(server_fd,nullptr,nullptr);
        char buffer[128];
        read(client_fd, buffer,sizeof(buffer));
        std::cout << "Server received: " << buffer << "\n";
        const char* reply = "Reply from server";
        send(client_fd, reply, strlen(reply), 0);
        close(client_fd); close(server_fd);
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serv{};
    serv.sin_family = AF_INET;
    serv.sin_port = htons(9000);
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);
    connect(sock,(sockaddr*)&serv,sizeof(serv));
    const char* msg="Hello Socket!";
    send(sock,msg,strlen(msg),0);
    char buffer[128];
    read(sock,buffer,sizeof(buffer));
    std::cout << "Client received: " << buffer << "\n";
    close(sock);

    server.join();
}

void demo_json_rpc() {
    std::cout << "\n=== JSON-RPC Demo (simulated) ===\n";
    std::string request = R"({"method":"add","params":[10,20]})";
    std::cout << "Client sends: " << request << "\n";
    int result = 10+20; // simulate server processing
    std::cout << "Server replies: {\"result\":" << result << "}\n";
}

void demo_custom_rpc() {
    std::cout << "\n=== Custom RPC Demo ===\n";
    auto rpc_call = [](const std::string& method,int a,int b){
        if(method=="add") return a+b;
        return 0;
    };
    int sum = rpc_call("add",5,7);
    std::cout << "RPC add(5,7) = " << sum << "\n";
}

int main() {
    std::cout << "=== C++ Protocols Demo ===\n";

    demo_pipe();
    demo_shared_memory();
    demo_socket();
    demo_json_rpc();
    demo_custom_rpc();

    std::cout << "\n=== Simulated protocols ===\n";
    std::cout << "gRPC, Thrift, MQTT, CAN, DDS, HTTP/REST would require external setup.\n";
    std::cout << "In real projects, you link gRPC/Thrift libraries and implement client/server as needed.\n";

    return 0;
}
/* 
//Compile & Run
g++ protocols_demo.cpp -o protocols_demo -pthread
./protocols_demo



Sample Output:
=== C++ Protocols Demo ===

=== PIPE Demo ===
Child received via pipe: Hello Pipe!

=== SHARED MEMORY Demo ===
Parent read: Hello Shared Memory!

=== TCP SOCKET Demo ===
Server received: Hello Socket!
Client received: Reply from server

=== JSON-RPC Demo (simulated) ===
Client sends: {"method":"add","params":[10,20]}
Server replies: {"result":30}

=== Custom RPC Demo ===
RPC add(5,7) = 12

=== Simulated protocols ===
gRPC, Thrift, MQTT, CAN, DDS, HTTP/REST would require external setup.
In real projects, you link gRPC/Thrift libraries and implement client/server as needed.
*/