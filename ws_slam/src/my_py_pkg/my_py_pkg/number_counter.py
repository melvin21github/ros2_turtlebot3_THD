#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32

class NumberCounter(Node):
    def __init__(self):
        super().__init__('number_counter')
        self.sum = 0
        self.subscriber = self.create_subscription(
            Int32,
            'number',
            self.callback,
            10)
        self.publisher = self.create_publisher(Int32, 'number_sum', 10)
        self.get_logger().info('Number Counter started')

    def callback(self, msg):
        self.sum += msg.data
        sum_msg = Int32()
        sum_msg.data = self.sum
        self.publisher.publish(sum_msg)
        self.get_logger().info(f'Received: {msg.data} | Cumulative Sum: {self.sum}')

def main(args=None):
    rclpy.init(args=args)
    node = NumberCounter()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
