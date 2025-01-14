import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class FastAgent(Node):
    def __init__(self):
        super().__init__('fast_agent')
        self.FastPublisher = self.create_publisher(String, 'fast_topic', 10)
        self.FastTimer = self.create_timer(0.5, self.timer_callback)
        self.i = 0
        self.FastSubscription = self.create_subscription(String, 'slow_topic', self.listener_callback, 10)
    def timer_callback(self):
        msg = String()
        msg.data = 'Fast Timer %d' % self.i
        self.FastPublisher.publish(msg)
        self.get_logger().info('[Fast] Publishing: "%s"' % msg.data)
        self.i += 1
    def listener_callback(self, msg):
        self.get_logger().info('[Fast] I heard: "%s"' % msg.data)

def main(args=None):
    rclpy.init(args=args)
    fast_agent = FastAgent()
    rclpy.spin(fast_agent)
    fast_agent.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()