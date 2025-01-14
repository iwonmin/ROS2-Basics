import sys

from std_srvs.srv import Empty
import rclpy
from rclpy.node import Node

class ToggleClient(Node):
    def __init__(self):
        super().__init__('toggle_led_async')
        self.cli = self.create_client(Empty, 'toggle_led')
        while not self.cli.wait_for_service(timeout_sec = 1.0):
            self.get_logger().info('service not availabla!!, wait!')
        self.req = Empty.Request()
    def send_request(self):
        return self.cli.call_async(self.req)

def main():
    rclpy.init()

    led_cli = ToggleClient()
    future = led_cli.send_request()
    rclpy.spin_until_future_complete(led_cli, future)
    response = future.result()
    led_cli.get_logger().info('[led_toggle_service]: service call completedd~!')
    led_cli.destroy_node()
    rclpy.shutdown()
if __name__ == '__main__':
    main()
 
        
