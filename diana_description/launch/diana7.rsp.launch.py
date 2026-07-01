from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import Command
from launch.substitutions import LaunchConfiguration
from launch.substitutions import PathJoinSubstitution
from launch.substitutions import FindExecutable

from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():

    #
    # Launch Arguments
    #

    declared_arguments = [
        DeclareLaunchArgument(
            "prefix",
            default_value="",
            description="Prefix for all joint and link names",
        ),
        DeclareLaunchArgument(
            "use_fake_hardware",
            default_value="true",
            description="Use mock_components/GenericSystem",
        ),
        DeclareLaunchArgument(
            "fake_sensor_commands",
            default_value="false",
            description="Enable fake sensor commands",
        ),
        DeclareLaunchArgument(
            "use_gazebo",
            default_value="false",
            description="Load Gazebo plugins",
        ),
    ]

    #
    # robot_description
    #

    robot_description = {
        "robot_description": Command(
            [
                FindExecutable(name="xacro"),
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
                LaunchConfiguration("prefix"),
                " ",
                "use_fake_hardware:=",
                LaunchConfiguration("use_fake_hardware"),
                " ",
                "fake_sensor_commands:=",
                LaunchConfiguration("fake_sensor_commands"),
                " ",
                "use_gazebo:=",
                LaunchConfiguration("use_gazebo"),
            ]
        )
    }

    #
    # robot_state_publisher
    #

    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        parameters=[
            robot_description,
            {
                "publish_frequency": 100.0,
            },
        ],
        output="screen",
    )

    return LaunchDescription(
        declared_arguments
        + [
            robot_state_publisher,
        ]
    )
