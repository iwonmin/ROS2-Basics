#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/empty.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;
//argument 예외 처리 부분
int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    if (argc != 1) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "YOU ARE WRONG");
        return 18;
    } 
    //client 생성 부분
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("toggle_led");
    rclcpp::Client<std_srvs::srv::Empty>::SharedPtr client = node->create_client<std_srvs::srv::Empty>("toggle_led");
    auto request = std::make_shared<std_srvs::srv::Empty::Request>();
    //ㅇ
    while(!client->wait_for_service(1s)) {
        if(!rclcpp::ok()) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "PROCESS DIED");
            return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Waiting for Server..");
    }

    auto result = client->async_send_request(request);

    if(rclcpp::spin_until_future_complete(node, result) == rclcpp::FutureReturnCode::SUCCESS) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "[led_toggle_client]: Service call completed");
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "[led_toggle_client]: Service call failed!!");
    }
}