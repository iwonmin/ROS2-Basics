import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class MinimalSubscriber(Node):
    def __init__(self):
        super().__init__('minimal_subscriber')
        self.subscription_fast = self.create_subscription(String, 'fast_topic', self.listener_callback_fast, 10)
        self.subscription_fast
        self.subscription_slow = self.create_subscription(String, 'slow_topic', self.listener_callback_slow, 10)
        self.subscription_slow
    def listener_callback_fast(self, msg):
        self.get_logger().info('[Fast] I heard : "%s"' % msg.data)
    def listener_callback_slow(self, msg):
        self.get_logger().info('[Slow] I heard : "%s"' % msg.data)

def main(args=None):
    rclpy.init(args=args)
    minimal_subscriber = MinimalSubscriber()
    rclpy.spin(minimal_subscriber)
    minimal_subscriber.destroy_node()
    rclpy.shutdown()
if __name__ == '__main__':
    main()
