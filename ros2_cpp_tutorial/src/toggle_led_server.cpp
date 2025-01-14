#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/empty.hpp"
#include <memory>

bool led = 0;
void toggle_led(const std::shared_ptr<std_srvs::srv::Empty::Request> request, const std::shared_ptr<std_srvs::srv::Empty::Response> response) {
    led = !led;
    if(led) RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "[led_toggle_service]: LED is now ON");
    else RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "[led_toggle_service]: LED is now OFF");
}

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("toggle_led");
    rclcpp::Service<std_srvs::srv::Empty>::SharedPtr service = node->create_service<std_srvs::srv::Empty>("toggle_led", &toggle_led);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "[led_toggle_service]: Led toggle Service Ready");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}