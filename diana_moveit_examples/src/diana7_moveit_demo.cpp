#include <memory>
#include <thread>

#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <moveit_visual_tools/moveit_visual_tools.h>

int main(int argc, char *argv[])
{
	// Initialize ROS and create the Node
	rclcpp::init(argc, argv);
	auto const node = std::make_shared<rclcpp::Node>(
		"diana7_moeit_demo",
		rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));

	// Create a ROS logger
	auto const logger = rclcpp::get_logger("diana7_moveit_demo");

	// Create the MoveIt MoveGroup Interface
	using moveit::planning_interface::MoveGroupInterface;
	auto move_group_interface = MoveGroupInterface(node, "diana7_arm");

	// Set a target Pose
	auto const target_pose = []
	{
		geometry_msgs::msg::Pose msg;
		msg.orientation.w = 1.0;
		msg.position.x = 0.58;
		msg.position.y = -0.4;
		msg.position.z = 0.5;
		return msg;
	}();
	move_group_interface.setPoseTarget(target_pose);

	auto const [success, plan] = [&move_group_interface]
	{
		moveit::planning_interface::MoveGroupInterface::Plan msg;
		auto const ok = static_cast<bool>(move_group_interface.plan(msg));
		return std::make_pair(ok, msg);
	}();

	// Execute the plan
	if (success)
	{
		move_group_interface.execute(plan);
	}
	else
	{
		RCLCPP_ERROR(logger, "Planning failed!");
	}

	// // Construct and initialize MoveItVisualTools
	// auto moveit_visual_tools = moveit_visual_tools::MoveItVisualTools{
	// node, "base_link", rviz_visual_tools::RVIZ_MARKER_TOPIC,
	// move_group_interface.getRobotModel()};
	// moveit_visual_tools.deleteAllMarkers();
	// moveit_visual_tools.loadRemoteControl();

	// // Create closures for visualization
	// auto const draw_title = [&moveit_visual_tools](auto text)
	// {
	// auto const text_pose = []
	// {
	// auto msg = Eigen::Isometry3d::Identity();
	// msg.translation().z() = 1.0; // Place text 1m above the base link
	// return msg;
	// }();
	// moveit_visual_tools.publishText(text_pose, text, rviz_visual_tools::WHITE,
	// rviz_visual_tools::XLARGE);
	// };
	// auto const prompt = [&moveit_visual_tools](auto text)
	// {
	// moveit_visual_tools.prompt(text);
	// };
	// auto const draw_trajectory_tool_path =
	// [&moveit_visual_tools,
	//  jmg = move_group_interface.getRobotModel()->getJointModelGroup(
	//  "diana7_arm")](auto const trajectory)
	// {
	// moveit_visual_tools.publishTrajectoryLine(trajectory, jmg);
	// };

	// // Create a plan to that target pose
	// prompt("Press 'Next' in the RvizVisualToolsGui window to plan");
	// draw_title("Planning");
	// moveit_visual_tools.trigger();

	// // Execute the plan
	// if (success)
	// {
	// draw_trajectory_tool_path(plan.trajectory);
	// moveit_visual_tools.trigger();
	// prompt("Press 'Next' in the RvizVisualToolsGui window to execute");
	// draw_title("Executing");
	// moveit_visual_tools.trigger();
	// move_group_interface.execute(plan);
	// }
	// else
	// {
	// draw_title("Planning Failed!");
	// moveit_visual_tools.trigger();
	// RCLCPP_ERROR(logger, "Planning failed!");
	// }

	// // Spin up a SingleThreadedExecutor for MoveItVisualTools to interact with ROS
	// rclcpp::executors::SingleThreadedExecutor executor;
	// executor.add_node(node);
	// auto spinner = std::thread([&executor]()
	// 						   { executor.spin(); });

	// spinner.join();

	// Shutdown ROS
	rclcpp::shutdown();
	return 0;
}
