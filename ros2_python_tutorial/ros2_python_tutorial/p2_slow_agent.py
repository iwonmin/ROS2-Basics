import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class SlowAgent(Node):
    def __init__(self):
        super().__init__('slow_agent')
        self.SlowPublisher = self.create_publisher(String, 'slow_topic', 10)
        self.SlowTimer = self.create_timer(1.0, self.timer_callback)
        self.i = 0
        self.SlowSubscription = self.create_subscription(String, 'fast_topic', self.listener_callback, 10)
    def timer_callback(self):
        msg = String()
        msg.data = 'Slow Timer %d' % self.i
        self.SlowPublisher.publish(msg)
        self.get_logger().info('[Slow] Publishing: "%s"' % msg.data)
        self.i += 1
    def listener_callback(self, msg):
        self.get_logger().info('[Slow] I heard: "%s"' % msg.data)

def main(args=None):
    rclpy.init(args=args)
    slow_agent = SlowAgent()
    rclpy.spin(slow_agent)
    slow_agent.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()