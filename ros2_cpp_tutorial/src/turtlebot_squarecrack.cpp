#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <turtlesim/msg/pose.hpp>

using namespace std::chrono_literals;
using std::placeholders::_1;

struct State {
    double x = 0;
    double y = 0;
    double theta = 0;
};

class TurtlebotController : public rclcpp::Node {
public:
  TurtlebotController() : Node("turtlebot_controller") {
  publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
  subscription_ = this->create_subscription<turtlesim::msg::Pose>(
    "turtle1/pose", 10, std::bind(&TurtlebotController::topic_callback, this, _1));
  timer_ = this->create_wall_timer(
    100ms, std::bind(&TurtlebotController::timer_callback, this));
  counter_ = this ->create_wall_timer(
    1s, std::bind(&TurtlebotController::counter_callback, this));

}

private:
  void counter_callback() {
    RCLCPP_INFO(this->get_logger(), "This turtle worked for %d sec.", counter);
    counter++;
  }
  void timer_callback() {
    geometry_msgs::msg::Twist cmd;
    switch(motion) {
      case Motion::FORWARD:
        if(init_toggle) {
          initial_state = turtlebot_state;
          init_toggle = false;
          setPID(0.1f, 0.02f, 0.01f);
        }
        error = linear_goal - hypot(turtlebot_state.x - initial_state.x, turtlebot_state.y - initial_state.y);
        integral += error;
        derivative = error - prev_error;
        cmd.linear.x = Kp * error + Ki * integral + Kd * derivative;
        // RCLCPP_INFO(this->get_logger(), "%f %f %f", error, integral, derivative);
        prev_error = error;
        if (error < 0.0005f) {
          motion = Motion::TURN;
          cmd.linear.x = 0.f;
          error_initializtion();
          RCLCPP_INFO(this->get_logger(), "Translation Complete, Now Rotating...");
          init_toggle = true;
        }
        break;
      case Motion::TURN:
        if(init_toggle) {
          initial_state = turtlebot_state;
          init_toggle = false;
          setPID(0.09f, 0.001f, 0.02f);
        }
        error = angular_goal - abs(turtlebot_state.theta - initial_state.theta);
        // error = atan2(sin(error), cos(error)); //normalize theta
        integral += error;
        derivative = error - prev_error;
        cmd.angular.z = Kp * error + Ki * integral + Kd * derivative;
        // RCLCPP_INFO(this->get_logger(), "%f %f %f", error, integral, derivative);
        prev_error = error;
        if (abs(error) < 0.005f || abs(error) > 3.12f) {
          motion = Motion::FORWARD;
          cmd.angular.z = 0.f;
          error_initializtion();
          RCLCPP_INFO(this->get_logger(), "Rotation Complete, Now Translating...");
          init_toggle = true;
        }
        break;
    };
    publisher_->publish(cmd);
  }

  void topic_callback(const turtlesim::msg::Pose &msg) {
    turtlebot_state.x = msg.x;
    turtlebot_state.y = msg.y;
    turtlebot_state.theta = msg.theta;
    // turtlebot_state.theta = atan2(sin(turtlebot_state.theta), cos(turtlebot_state.theta)); //normalize theta
  }

  void error_initializtion() {
    error = 0.f;
    prev_error = 0.f;
    integral = 0.f;
    derivative = 0.f;
  }

  void setPID(float Kp_, float Ki_, float Kd_) {
    Kp = Kp_;
    Ki = Ki_;
    Kd = Kd_;
  }
  enum class Motion {
    FORWARD,
    TURN
  } motion = Motion::TURN;
  
  rclcpp::TimerBase::SharedPtr counter_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
  State turtlebot_state;
  State initial_state;
  bool init_toggle = true;
  float Kp = 0.1f;
  float Ki = 0.04f;
  float Kd = 0.01f;
  float linear_goal = 2.0f;
  float angular_goal = M_PI_2;

  double reference;
  double error;
  double prev_error;
  double derivative;
  double integral;
  
  int counter = 1;
};


int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TurtlebotController>());
  rclcpp::shutdown();
  return 0;
}
