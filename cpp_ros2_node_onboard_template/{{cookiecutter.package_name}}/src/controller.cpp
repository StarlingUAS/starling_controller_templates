/*
 * Starling Template
 * Copyright (C) 2021 University of Bristol
 *
 * Author: Mickey Li <mickey.li@bristol.ac.uk> (University of Bristol)
 *
 * Distributed under MIT License (available at https://opensource.org/licenses/MIT).
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 */
#include "controller.hpp"
#include "main.hpp"

UserController::UserController(UAVController *node) {
    // Set node so this controller can refer back to it later
    this->node = node;

    // Initialise publishers
    this->notify_angle_pub = this->node->create_publisher<{{cookiecutter.custom_ros2_msgs_name}}::msg::TargetAngle>("/monitor/notify_angle", 1);

    // Initialise Subscribers
    this->sync_angle_sub =  this->node->create_subscription<{{cookiecutter.custom_ros2_msgs_name}}::msg::TargetAngle>(
        "sync_angle", 10,
        std::bind(&UserController::handleTargetAngle, this, std::placeholders::_1));

    this->notify_vehicles_sub = this->node->create_subscription<{{cookiecutter.custom_ros2_msgs_name}}::msg::NotifyVehicles>(
        "notify_vehicles", 10,
        std::bind(&UserController::handleNotifyVehicles, this, std::placeholders::_1));

    this->node->get_parameter_or("sync_angle_P", this->sync_angle_P, 0.001);

    // Variables
    this->origin = geometry_msgs::msg::Point();
}

void UserController::reset() {
    this->system_vehicle_id = 0;
    this->received_circle_id = false;
}

bool UserController::smReady(const rclcpp::Time& stamp) {
    if (!this->received_circle_id) {
        RCLCPP_INFO(this->get_logger(), "Waiting for Notify Vehicle message from central monitor");
        return false;
    }
    return true;
}

bool UserController::smExecute(const rclcpp::Time& stamp, const rclcpp::Duration& time_elapsed) {
    // Get Time Elapsed Since State Change
    double time_elapsed_sec = time_elapsed.seconds();

    // Current Vehicle Location
    geometry_msgs::msg::PoseStamped current_pos = this->node->vehicle_local_position;

    /*
     *
     * Implement Your Solution Here
     *
     */

    // State Machine never exists by giving false.
    return false;
}

void UserController::handleTargetAngle(const {{cookiecutter.custom_ros2_msgs_name}}::msg::TargetAngle::SharedPtr s) {
    if (!isnan(s->theta)) {
        double theta_diff = this->vehicle_setpoint_theta - s->theta;
        this->vehicle_velocity += this->sync_angle_P * theta_diff;
        RCLCPP_INFO(this->get_logger(), "Received target angle of %f with diff %f so velocity of %f", s->theta, theta_diff, this->vehicle_velocity);
    } else {
        RCLCPP_INFO(this->get_logger(), "Received target angle [%f] is nan", s->theta);
    }
}

void UserController::handleNotifyVehicles(const {{cookiecutter.custom_ros2_msgs_name}}::msg::NotifyVehicles::SharedPtr s) {

    if(!this->node->start_trajectory_location) {
        this->system_vehicle_id = s->vehicle_id;

        double start_target_theta = 2 * M_PI * s->vehicle_id / s->total_vehicles;
        double startx = this->circle_radius * cos(start_target_theta) + this->origin.x;
        double starty = this->circle_radius * sin(start_target_theta) + this->origin.y;
        double startz = this->height + this->origin.z;
        double startyaw = start_target_theta;

        auto loc = std::make_shared<trajectory_msgs::msg::JointTrajectoryPoint>();
        std::vector<double> pos = {startx, starty, startz, startyaw};
        loc->positions = pos;
        this->node->start_trajectory_location = loc;

        this->vehicle_setpoint_theta = start_target_theta;
        this->vehicle_start_theta = start_target_theta;
        this->received_circle_id = true;
    }

}

rclcpp::Logger UserController::get_logger() {return this->node->get_logger();}
rclcpp::Time UserController::now() {return this->node->now();}
