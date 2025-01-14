#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node {
    public:
        MinimalSubscriber() : Node("minimal_subscriber") {
            subscription_fast = this->create_subscription<std_msgs::msg::String>("fast_topic",10,std::bind(&MinimalSubscriber::topic_callback_fast, this, _1));
            subscription_slow = this->create_subscription<std_msgs::msg::String>("slow_topic",10,std::bind(&MinimalSubscriber::topic_callback_slow, this, _1));
        }
    private:
        void topic_callback_fast(const std_msgs::msg::String & msg) const {
            RCLCPP_INFO(this->get_logger(), "[Fast] I heard : '%s'",msg.data.c_str());
        }
        void topic_callback_slow(const std_msgs::msg::String & msg) const {
            RCLCPP_INFO(this->get_logger(), "[Slow] I heard : '%s'",msg.data.c_str());
        }
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_fast;
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_slow;
};
int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalSubscriber>());
    rclcpp::shutdown();
    return 0;
}