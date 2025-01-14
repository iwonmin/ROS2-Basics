#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node {
    public:
        MinimalPublisher() : Node("minimal_publisher"), count_fast_(0),count_slow_(0) {
            publisher_fast_ = this->create_publisher<std_msgs::msg::String>("fast_topic", 10);
            timer_fast_ = this-> create_wall_timer(500ms, std::bind(&MinimalPublisher::timer_callback_fast, this));
            publisher_slow_ = this->create_publisher<std_msgs::msg::String>("slow_topic", 10);
            timer_slow_ = this-> create_wall_timer(1000ms, std::bind(&MinimalPublisher::timer_callback_slow, this));

        }
    private:
        void timer_callback_fast() {
            auto message = std_msgs::msg::String();
            message.data = "Fast Timer " + std::to_string(count_fast_++);
            RCLCPP_INFO(this->get_logger(), "[Fast] Publishing: '%s'", message.data.c_str());
            publisher_fast_->publish(message);
        }
        void timer_callback_slow() {
            auto message = std_msgs::msg::String();
            message.data = "Slow Timer " + std::to_string(count_slow_++);
            RCLCPP_INFO(this->get_logger(), "[Slow] Publishing: '%s'", message.data.c_str());
            publisher_slow_->publish(message);        
        }
        rclcpp::TimerBase::SharedPtr timer_fast_;
        rclcpp::TimerBase::SharedPtr timer_slow_;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_fast_;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_slow_;
        size_t count_fast_;
        size_t count_slow_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalPublisher>());
    rclcpp::shutdown();
    return 0;
}