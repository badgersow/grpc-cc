#include "iostream"
#include "string"
#include "memory"

#include "grpcpp/grpcpp.h"

#include "proto/message.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class OumaClient {
 private:
  std::unique_ptr<OumaService::Stub> stub_;
 public:
  OumaClient(std::shared_ptr<Channel> channel) :
      stub_(OumaService::NewStub(channel)) {}

  std::string call_ouma(const std::string &input) {
    OumaRequest request;
    request.set_message(input);

    OumaReply reply;
    ClientContext context;
    Status status = stub_->prophesize(&context, request, &reply);

    if (status.ok()) {
      return reply.message();
    } else {
      throw std::runtime_error("Failed to contact server");
    }
  }
};

int main() {
  const std::string host{"localhost"};
  const std::string port{"8888"};
  const std::string address = host + ":" + port;
  const std::string message = "itya";

  std::cout << "Sending the message " << message << " to " << address << std::endl;

  OumaClient client(grpc::CreateChannel(address,
                                        grpc::InsecureChannelCredentials()));
  const std::string reply = client.call_ouma(message);

  std::cout << "Received a reply " << reply << std::endl;
  return 0;
}