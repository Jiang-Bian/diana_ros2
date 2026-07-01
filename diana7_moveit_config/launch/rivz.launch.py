from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution

from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

from moveit_configs_utils import MoveItConfigsBuilder

def generate_launch_description():

    moveit_config = MoveItConfigsBuilder(
        "diana7",
        package_name="diana7_moveit_config",
    ).to_moveit_configs()

    rviz_config = PathJoinSubstitution(
        [
            FindPackageShare("diana7_moveit_config"),
            "rviz",
            "moveit.rviz",
        ]
    )

    rviz = Node(
        package="rviz2",
        executable="rviz2",
        output="screen",
        arguments=[
            "-d",
            rviz_config,
        ],
        parameters=[
            moveit_config.robot_description,
            moveit_config.robot_description_semantic,
            moveit_config.robot_description_kinematics,
            moveit_config.planning_pipelines,
            moveit_config.joint_limits,
        ],
    )

    return LaunchDescription(
        [
            rviz,
        ]
    )
