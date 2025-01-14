from std_srvs.srv import Empty

import rclpy
from rclpy.node import Node



class ToggleService(Node):
    def __init__(self):
        super().__init__('toggle_led')
        self.led_ = False
        self.srv = self.create_service(Empty, 'toggle_led', self.toggle_led_callback)
    
    def toggle_led_callback(self, request, response):
        if(self.led_):
            self.led_ = False
        else:
            self.led_ = True 
        self.get_logger().info('[led_toggle_service] : LED is now %s' % ("ON" if(self.led_) else "OFF"))
        return response
def main():
    rclpy.init()

    toggle_led = ToggleService()
    toggle_led.get_logger().info('[led_toggle_service]: Led Servce Acitated')
    rclpy.spin(toggle_led)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
        
