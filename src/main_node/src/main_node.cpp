//
// Created by ryuzo on 2023/09/09.
//
#include <rclcpp/rclcpp.hpp>

#include "rclcpp_components/register_node_macro.hpp"
#include "main_node/main_node.hpp"

#include "std_msgs/msg/string.hpp"
#include "nlohmann/json.hpp"
#include "utilities/can_utils.hpp"
#include "tcp_interface/srv/tcp_socket_i_ctrl.hpp"
#include "std_msgs/msg/float32.hpp"

using namespace nlohmann;

namespace main_node {

    MainNode::MainNode(const rclcpp::NodeOptions &options) : Node("main_node", options) {
        using namespace std::chrono_literals;
        tcp8011_flag = false;

        declare_parameter("interval_ms", 10);
        interval_ms = this->get_parameter("interval_ms").as_int();
        client_ = this->create_client<tcp_interface::srv::TcpSocketICtrl>("/tcp_interface/tcp_register");
        _publisher = this->create_publisher<socketcan_interface::msg::SocketcanIF>("/can_tx", _qos);
        while (!client_->wait_for_service(1s)){
            if(!rclcpp::ok()){
                RCLCPP_ERROR(this->get_logger(), "Manual Node Client interrupted while waiting for TCP service");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "waiting for TCP service");
        }

        manual_instruction["action"] = 0;
        manual_instruction["dir"] = 1;
        manual_instruction["speed"] = 0;

        auto request_tcp_8011 = std::make_shared<tcp_interface::srv::TcpSocketICtrl::Request>();
        request_tcp_8011->port = 8011;
        auto future_response_tcp_8011 = client_->async_send_request(request_tcp_8011, std::bind(&MainNode::_callback_response_tcp8011,
                                                                                                this, std::placeholders::_1));
        _subscription_tcp_8011 = this->create_subscription<std_msgs::msg::String>("/tcp_8011",
                                                                                  _qos,
                                                                                  std::bind(&MainNode::_subscriber_callback_tcp_8011, this, std::placeholders::_1)
        );
        _pub_timer = this->create_wall_timer(
                std::chrono::milliseconds(interval_ms),
                [this] { _publisher_callback(); }
        );
    }
    void MainNode::_subscriber_callback_tcp_8011(std_msgs::msg::String msg) {
        std::string content = msg.data;
        RCLCPP_INFO(this->get_logger(), "content:%s", content.c_str());
        try
        {
            manual_instruction = json::parse(content);
        }
        catch (std::exception &e)
        {
            RCLCPP_INFO(this->get_logger(), "ERROR AT ManualNode::_subscriber_callback_tcp_8011, IGNORING");
        }
    }

    void MainNode::_publisher_callback() {
        uint8_t action = manual_instruction["action"];
        uint8_t dir = manual_instruction["dir"];
        uint8_t speed = manual_instruction["speed"];

        auto msg = std::make_shared<socketcan_interface::msg::SocketcanIF>();
        msg->canid = 0x001;
        msg->candlc = 3;
        msg->candata[0] = action;
        if (dir == 1){
            msg->candata[1] = 0;
        } else {
            msg->candata[1] = 1;
        }
        msg->candata[2] = speed;
        _publisher->publish(*msg);
        RCLCPP_INFO(this->get_logger(), "action:%d, dir:%d, speed:%d", action, dir, speed);
    }

    void MainNode::_callback_response_tcp8011(rclcpp::Client<tcp_interface::srv::TcpSocketICtrl>::SharedFuture future) {
        if (future.get()->ack){
            this->tcp8011_flag = true;
        } else{
            RCLCPP_ERROR(this->get_logger(), "TCP service could not earn 8011 port");
        }
    }

}


RCLCPP_COMPONENTS_REGISTER_NODE(main_node::MainNode)