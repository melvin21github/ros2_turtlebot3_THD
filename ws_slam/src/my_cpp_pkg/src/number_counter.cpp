#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

class NumberCounter : public rclcpp::Node
{
public:
  NumberCounter()
  : Node("number_counter"), sum_(0)
  {
    // Subscribe to the /number topic
    sub_ = this->create_subscription<std_msgs::msg::Int32>(
      "number", 10, std::bind(&NumberCounter::callback, this, std::placeholders::_1));

    // Publish the cumulative sum to /number_sum
    pub_ = this->create_publisher<std_msgs::msg::Int32>("number_sum", 10);

    RCLCPP_INFO(this->get_logger(), "Number Counter node started");
  }

private:
  void callback(const std_msgs::msg::Int32::SharedPtr msg)
  {
    sum_ += msg->data;  // Add received number to the sum

    auto sum_msg = std_msgs::msg::Int32();
    sum_msg.data = sum_;
    pub_->publish(sum_msg);

    RCLCPP_INFO(this->get_logger(), "Received: %d | Cumulative Sum: %d", msg->data, sum_);
  }

  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr sub_;
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pub_;
  int sum_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<NumberCounter>());
  rclcpp::shutdown();
  return 0;
}
