#include "iostream"
#include "memory"
#include "string"
#include "grpcpp/grpcpp.h"
#include "proto/message.grpc.pb.h"

using grpc::Server;
using grpc::ServerContext;
using grpc::ServerBuilder;
using grpc::Status;

class OumaServiceImpl : public OumaService::Service {
  Status prophesize(ServerContext *context, const OumaRequest *request, OumaReply *reply) {
    const std::string input = request->message();
    const std::string reply_string = "Hello, " + input;
    reply->set_message(reply_string);
    return Status::OK;
  }
};

int main() {
  const std::string host{"localhost"};
  const std::string port{"8888"};
  const std::string address = host + ":" + port;

  OumaServiceImpl service;
  ServerBuilder builder;
  builder.AddListeningPort(address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<Server> server{builder.BuildAndStart()};
  std::cout << "Shoopuf is waiting on " << address << std::endl;

  server->Wait();
  return 0;
}