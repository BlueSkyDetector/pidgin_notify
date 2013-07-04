#define PURPLE_PLUGINS

#include <glib.h>
#include <libpurple/notify.h>
#include <libpurple/plugin.h>
#include <libpurple/version.h>
#include <libnotify/notify.h>

static void
notify_msg(PurpleAccount *account, char *sender,char *message,
		PurpleConversation *conv, PurpleMessageFlags flags) {
        NotifyNotification *n;

        if (!sender)
                return;

        n = notify_notification_new (sender, message, NULL, NULL);
        notify_notification_set_timeout(n, 3000);
        if (!notify_notification_show (n, NULL)) {
            g_error("Failed to send notification.\n");
            return;
        }
        g_object_unref(G_OBJECT(n));
}



static gboolean
plugin_load(PurplePlugin *plugin) {
	void *conv_handle;

	conv_handle = purple_conversations_get_handle();
        notify_init("custom_notify");
	purple_signal_connect(conv_handle, "received-im-msg", plugin,
			PURPLE_CALLBACK(notify_msg), NULL);
	return TRUE;
}

static gboolean
plugin_unload (PurplePlugin *plugin)
{
	void *conv_handle;

	conv_handle = purple_conversations_get_handle();
	purple_signal_disconnect (conv_handle, "received-im-msg", plugin,
			PURPLE_CALLBACK(notify_msg));
	notify_uninit();
	return TRUE;
}

static PurplePluginInfo info = {
	PURPLE_PLUGIN_MAGIC,
	PURPLE_MAJOR_VERSION,
	PURPLE_MINOR_VERSION,
	PURPLE_PLUGIN_STANDARD,
	NULL,
	0,
	NULL,
	PURPLE_PRIORITY_DEFAULT,
	"core-custom_notify",
	"custom notify",
	"1.0",
	"custom notify",
	"custom notify",
	"Takanori Suzuki <mail.tks@gmail.com>",
	NULL,
	plugin_load,
	plugin_unload,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

static void						
init_plugin(PurplePlugin *plugin)
{
}

PURPLE_INIT_PLUGIN(custom_notify, init_plugin, info)
