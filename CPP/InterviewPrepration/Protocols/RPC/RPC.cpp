RPC (Remote Procedure Call)
👉 What is RPC?

RPC (Remote Procedure Call) is a communication method where a program can call a function/procedure on another machine or process as if it were local.

It is an abstraction layer over IPC or network protocols.

Example:
result = user_service.get_user(101);
This appears like a local function call but is happening over the network.

👉 Why do we use RPC?

To build distributed systems

Hide networking complexity

Enable microservices → services communicate over RPC

Provide clean API boundaries

👉 Where do we use RPC?

Microservices (Kubernetes, cloud platforms)

Client-server architecture

Distributed databases

Mobile backend communication

Embedded/automotive ECU-to-ECU over CAN or Ethernet

👉 Types of RPC Protocols

gRPC (Google RPC)

HTTP/2 based

Uses Protocol Buffers

Very fast

Used by Google, Netflix, etc.

Thrift (Apache)
A multi-language RPC framework (FB originally).

XML-RPC / JSON-RPC
Older & simpler.

D-Bus (Desktop Bus)
IPC/RPC hybrid used in Linux desktop systems.

CORBA (Deprecated)
Old enterprise RPC framework.

👉 Pros & Cons of RPC
✔ PROS

Clean API, hides complexity

Structured data exchange

Works across machines and languages

Excellent for microservices

❌ CONS

More network overhead than local IPC

Complex debugging (latency, serialization issues)

Reliability concerns (network failures)

Requires strict contract management (IDL, protobuf)

🟦 IPC vs RPC — Difference Table
| Feature     | IPC                        | RPC                                |
| ----------- | -------------------------- | ---------------------------------- |
| Scope       | Mostly local machine       | Local or network/distributed       |
| Speed       | Very fast (shared memory)  | Slower (network/serialization)     |
| API Style   | Low-level primitives       | Function/Method calls              |
| Data Format | Raw bytes, OS-level        | Structured (protobuf, JSON, XML)   |
| Use Cases   | Browser processes, DBs, OS | Microservices, distributed systems |




C++ RPC examples, covering:
✔ gRPC (most widely used RPC)
✔ JSON-RPC (simple, HTTP-based)
✔ Custom lightweight RPC over sockets (for interviews)
Everything is explained step-by-step, with code you can compile and run.

✅ 1. gRPC C++ Example (Modern, Production-Grade)
gRPC uses:
HTTP/2
Protocol Buffers
Strongly typed APIs
Auto-generated C++ client/server code

📌 Step 1 — Write the .proto file
hello.proto
syntax = "proto3";

package demo;
service HelloService {
  rpc SayHello (HelloRequest) returns (HelloReply);
}
message HelloRequest {
  string name = 1;
}
message HelloReply {
  string message = 1;
}


📌 Step 2 — Generate C++ gRPC code
Run:
protoc --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` hello.proto
protoc --cpp_out=. hello.proto



This produces:
hello.pb.cc
hello.pb.h
hello.grpc.pb.cc
hello.grpc.pb.h




//📌 Step 3 — Implement the server
//server.cpp

#include <iostream>
#include <grpcpp/grpcpp.h>
#include "hello.grpc.pb.h"
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
class HelloServiceImpl : public demo::HelloService::Service {
  public:
    Status SayHello(ServerContext* context,
                    const demo::HelloRequest* request,
                    demo::HelloReply* reply) override
    {
        reply->set_message("Hello " + request->name());
        return Status::OK;
    }
};
int main() {
    std::string address("0.0.0.0:50051");
    HelloServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server running at " << address << "\n";
    server->Wait();

    return 0;
}





//📌 Step 4 — Implement the client

//client.cpp
#include <iostream>
#include <grpcpp/grpcpp.h>
#include "hello.grpc.pb.h"
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
class HelloClient {
    std::unique_ptr<demo::HelloService::Stub> stub;
  public:
    HelloClient(std::shared_ptr<Channel> channel): stub(demo::HelloService::NewStub(channel)) {}

    std::string SayHello(const std::string& name) {
        demo::HelloRequest req;
        req.set_name(name);

        demo::HelloReply reply;
        ClientContext context;

        Status status = stub->SayHello(&context, req, &reply);
        return status.ok() ? reply.message() : "RPC Failed";
    }
};
int main() {
    HelloClient client(
        grpc::CreateChannel("localhost:50051",
                            grpc::InsecureChannelCredentials())
    );

    std::cout << client.SayHello("Aghaz") << "\n";
    return 0;
}





🚀 2. JSON-RPC Example in C++ (Very Simple, Lightweight)
JSON-RPC uses JSON over HTTP or raw TCP.
Here is a minimal JSON-RPC server & client using cpp-httplib and nlohmann::json.



//📌 Server
// json_rpc_server.cpp
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <iostream>
using json = nlohmann::json;
int main() {
    httplib::Server server;

    server.Post("/rpc", [](const httplib::Request& req, httplib::Response& res) {
        json request = json::parse(req.body);
        std::string method = request["method"];
        json params = request["params"];

        json response;
        response["jsonrpc"] = "2.0";
        response["id"] = request["id"];

        if (method == "add") {
            int a = params[0];
            int b = params[1];
            response["result"] = a + b;
        } else {
            response["error"] = "Unknown method";
        }

        res.set_content(response.dump(), "application/json");
    });

    std::cout << "JSON-RPC server running on port 8080\n";
    server.listen("0.0.0.0", 8080);
}




//📌 Client
// json_rpc_client.cpp
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <iostream>
using json = nlohmann::json;
int main() {
    httplib::Client client("localhost", 8080);

    json request = {
        {"jsonrpc", "2.0"},
        {"method", "add"},
        {"params", {10, 20}},
        {"id", 1}
    };

    auto res = client.Post("/rpc", request.dump(), "application/json");

    if (res) {
        json reply = json::parse(res->body);
        std::cout << "Result from RPC: " << reply["result"] << "\n";
    }
}






🟦 3. Custom Lightweight C++ RPC Over TCP Sockets
A self-made "RPC" protocol where client sends:
add 10 20

Server returns:
30




//📌 Server
// custom_rpc_server.cpp
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sstream>
int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(9000);

    bind(server_fd, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);

    std::cout << "RPC server running...\n";

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        char buf[128] = {0};
        read(client_fd, buf, sizeof(buf));

        std::string method;
        int a, b;
        std::stringstream ss(buf);
        ss >> method >> a >> b;

        int result = 0;
        if (method == "add") result = a + b;

        std::string response = std::to_string(result);
        send(client_fd, response.c_str(), response.size(), 0);
        close(client_fd);
    }
}




//📌 Client
// custom_rpc_client.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serv{};
    serv.sin_family = AF_INET;
    serv.sin_port = htons(9000);
    inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr);

    connect(sock, (sockaddr*)&serv, sizeof(serv));

    const char* cmd = "add 10 20";
    send(sock, cmd, strlen(cmd), 0);

    char buffer[128] = {0};
    read(sock, buffer, sizeof(buffer));
    std::cout << "Result = " << buffer << "\n";

    close(sock);
}

📌 Summary — When To Use Which?
| RPC Type       | When to Use              | Pros                   | Cons               |
| -------------- | ------------------------ | ---------------------- | ------------------ |
| **gRPC**       | Production microservices | Fast, typed, streaming | Setup is heavier   |
| **JSON-RPC**   | Simple tools, GUIs       | Human readable         | Slower             |
| **Custom RPC** | Learning, embedded       | Full control           | No standardization |









2️⃣ Remote Procedure Call (RPC) Protocols
Used for distributed communication / microservices.

| Protocol / Framework | Description                        | C++ Use Case                     |
| -------------------- | ---------------------------------- | -------------------------------- |
| **gRPC**             | HTTP/2 + Protocol Buffers          | Microservices, client-server     |
| **Thrift (Apache)**  | Cross-language RPC + serialization | Multi-language systems           |
| **JSON-RPC**         | Lightweight JSON over TCP/HTTP     | Lightweight RPC, GUI tools       |
| **XML-RPC**          | XML-based RPC                      | Legacy systems                   |
| **CORBA**            | Enterprise RPC (deprecated)        | Older distributed apps           |
| **D-Bus**            | IPC + RPC for Linux desktop        | Desktop services, system daemons |
