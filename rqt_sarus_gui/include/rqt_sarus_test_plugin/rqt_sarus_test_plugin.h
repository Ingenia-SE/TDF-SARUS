#ifndef RQT_SARUS_TEST_PLUGIN
#define RQT_SARUS_TEST_PLUGIN

#include <rqt_gui_cpp/plugin.h>
#include <std_msgs/String.h>

#include <rqt_sarus_test_plugin/rqt_sarus_test_plugin_widget.h>

namespace rqt_sarus_test_plugin {

class TestPlugin : public rqt_gui_cpp::Plugin
{
public:
    TestPlugin();

    void initPlugin(qt_gui_cpp::PluginContext& context) override;
    void shutdownPlugin() override;

    void saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const override;
    void restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings) override;

private:
    TestPluginWidget *widget = nullptr;
};

}

#endif // RQT_SARUS_TEST_PLUGIN

