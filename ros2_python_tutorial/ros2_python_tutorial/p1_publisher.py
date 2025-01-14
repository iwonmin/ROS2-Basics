import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class MinimalPublisher(Node):
    def __init__(self):
        super().__init__('minimal_publisher')
        self.publisher_fast = self.create_publisher(String, 'fast_topic', 10)
        self.timer_fast = self.create_timer(0.5, self.timer_callback_fast)
        self.publisher_slow = self.create_publisher(String, 'slow_topic', 10)
        self.timer_slow = self.create_timer(1.0, self.timer_callback_slow)
        self.fast_i = 0
        self.slow_i = 0
    def timer_callback_fast(self):
        msg = String()
        msg.data = 'Fast Timer : %d' % self.fast_i
        self.publisher_fast.publish(msg)
        self.get_logger().info('[Fast] Publishing "%s"' % msg.data)
        self.fast_i +=1
    def timer_callback_slow(self):
        msg = String()
        msg.data = 'Slow Timer : %d' % self.slow_i
        self.publisher_slow.publish(msg)
        self.get_logger().info('[Slow] Publishing "%s"' % msg.data)
        self.slow_i +=1
def main(args=None):
    rclpy.init(args=args)
    minimal_publisher = MinimalPublisher()
    rclpy.spin(minimal_publisher)
    minimal_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()