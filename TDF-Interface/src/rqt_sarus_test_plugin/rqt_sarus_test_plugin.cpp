#include <rqt_sarus_test_plugin/rqt_sarus_test_plugin.h>
#include <pluginlib/class_list_macros.h>
#include <ros/master.h>
#include <ros/ros.h>
#include <std_msgs/String.h>

namespace rqt_sarus_test_plugin {

TestPlugin::TestPlugin() :
    rqt_gui_cpp::Plugin()
{
    setObjectName("TestPlugin");
}

void TestPlugin::initPlugin(qt_gui_cpp::PluginContext &context)
{
    widget = new TestPluginWidget();
    context.addWidget(widget);

    widget->init_ROS_Node();
}

void TestPlugin::shutdownPlugin()
{

}

void TestPlugin::saveSettings(qt_gui_cpp::Settings &plugin_settings, qt_gui_cpp::Settings &instance_settings) const
{

}

void TestPlugin::restoreSettings(const qt_gui_cpp::Settings &plugin_settings, const qt_gui_cpp::Settings &instance_settings)
{

}

} // end namespace rqt_sarus_test_plugin

PLUGINLIB_EXPORT_CLASS(rqt_sarus_test_plugin::TestPlugin, rqt_gui_cpp::Plugin)
