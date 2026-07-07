from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import Command
from launch.substitutions import LaunchConfiguration
from launch.substitutions import PathJoinSubstitution

from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.substitutions import FindExecutable


def generate_launch_description():

    prefix = LaunchConfiguration("prefix")
    use_fake_hardware = LaunchConfiguration("use_fake_hardware")

    declare_prefix = DeclareLaunchArgument("prefix", default_value="")

    declare_fake = DeclareLaunchArgument("use_fake_hardware", default_value="true")

    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name="xacro")]),
            " ",
            PathJoinSubstitution(
                [
                    FindPackageShare("diana_description"),
                    "robots",
                    "diana7",
                    "diana7.urdf.xacro",
                ]
            ),
            " ",
            "prefix:=",
            prefix,
            " ",
            "use_fake_hardware:=",
            use_fake_hardware,
        ]
    )

    robot_description = {"robot_description": robot_description_content}

    rsp = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="screen",
        parameters=[
            robot_description,
        ],
    )

    ros2_control = Node(
        package="controller_manager",
        executable="ros2_control_node",
        output="screen",
        parameters=[
            robot_description,
            PathJoinSubstitution(
                [
                    FindPackageShare("diana7_moveit_config"),
                    "config",
                    "ros2_controllers.yaml",
                ]
            ),
        ],
    )

    return LaunchDescription(
        [
            declare_prefix,
            declare_fake,
            rsp,
            ros2_control,
        ]
    )
