import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchContext, LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration

from launch_ros.actions import Node
import xacro


def robot_state_publisher_spawner(context: LaunchContext, arm_id, load_gripper, ee_id):
    arm_id_str = context.perform_substitution(arm_id)
    load_gripper_str = context.perform_substitution(load_gripper)
    ee_id_str = context.perform_substitution(ee_id)
    diana7_xacro_filepath = os.path.join(
        get_package_share_directory('diana7_description'),
        'urdf',
        arm_id_str + '_robot.urdf.xacro',
    )
    robot_description = xacro.process_file(
        diana7_xacro_filepath, mappings={'hand': load_gripper_str, 'ee_id': ee_id_str}
    ).toprettyxml(indent='  ')

    return [
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            output='screen',
            parameters=[{'robot_description': robot_description}],
        )
    ]


def generate_launch_description():
    load_gripper_parameter_name = 'load_gripper'
    load_gripper = LaunchConfiguration(load_gripper_parameter_name)

    ee_id_parameter_name = 'ee_id'
    ee_id = LaunchConfiguration(ee_id_parameter_name)

    arm_id_parameter_name = 'arm_id'
    arm_id = LaunchConfiguration(arm_id_parameter_name)

    rviz_file = os.path.join(
        get_package_share_directory('diana7_description'),
        'rviz',
        'visualize_diana7.rviz',
    )

    robot_state_publisher_spawner_opaque_function = OpaqueFunction(
        function=robot_state_publisher_spawner, args=[arm_id, load_gripper, ee_id]
    )

    return LaunchDescription(
        [
            DeclareLaunchArgument(
                load_gripper_parameter_name,
                default_value='false',
                description='Use end-effector if true. Default value is diana7 hand. '
                'Robot is loaded without end-effector otherwise',
            ),
            DeclareLaunchArgument(
                ee_id_parameter_name,
                default_value='none',
                description='ID of the type of end-effector used. Supporter values: '
                'none, diana7_hand, cobot_pump',
            ),
            DeclareLaunchArgument(
                arm_id_parameter_name,
                default_value='diana7',
                description='ID of the type of arm used. Supporter values: diana7',
            ),
            robot_state_publisher_spawner_opaque_function,
            Node(
                package='joint_state_publisher_gui',
                executable='joint_state_publisher_gui',
                name='joint_state_publisher_gui',
            ),
            Node(
                package='rviz2',
                executable='rviz2',
                name='rviz2',
                arguments=['--display-config', rviz_file],
            ),
        ]
    )
