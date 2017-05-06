#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "libretro.h"
#include "palmosemulibretro.h"

static struct retro_log_callback logging;

static retro_video_refresh_t video_cb;
static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;
retro_environment_t environ_cb;
static retro_input_poll_t input_poll_cb;
retro_input_state_t input_state_cb;
static retro_log_printf_t log_cb;

unsigned game_width  = 160;
unsigned game_height = 160;

#define getbutton(x) input_state_cb(0/*port*/, RETRO_DEVICE_JOYPAD, 0, (x)/*current button*/)
#define getaxis(x) input_state_cb(0/*port*/, RETRO_DEVICE_ANALOG, 0, (x)/*current axis*/)

static void fallback_log(enum retro_log_level level, const char* fmt, ...) {
	(void)level;
	va_list va;
	va_start(va, fmt);
	vfprintf(stderr, fmt, va);
	va_end(va);
}

void retro_init(void) {
	libretro_palm_init();
}

void retro_deinit(void) {
	libretro_palm_deinit();
}

unsigned retro_api_version(void) {
	return RETRO_API_VERSION;
}

void retro_set_controller_port_device(unsigned port, unsigned device) {
}

void retro_get_system_info(struct retro_system_info* info) {
	memset(info, 0, sizeof(*info));
	info->library_name     = "PersianTree";
	info->library_version = "-Infinity";
	info->need_fullpath    = true;
	/*.dev Describes a palm os device(The loaded prc/pdb files,which to execute,avalible flash/ram memory),screen size*/
	info->valid_extensions = "dev";
}


void retro_get_system_av_info(struct retro_system_av_info* info) {
	info->geometry.base_width  = game_width;
	info->geometry.base_height = game_height;
	info->geometry.max_width   = game_width;
	info->geometry.max_height  = game_height;
	//info->geometry.aspect_ratio = 16.0 / 9.0;
	info->geometry.aspect_ratio = 1.0 / 1.0;
	info->timing.fps            = 60.0;
	info->timing.sample_rate    = 48000.0;
}

static struct retro_rumble_interface rumble;

void retro_set_environment(retro_environment_t cb) {
	bool no_content = true;
	environ_cb = cb;
	/*
		static const struct retro_variable vars[] = {
		{ "craft_resolution",
		  "Resolution (restart); 640x480|320x200|640x400|960x600|1280x800|1600x1000|1920x1200|2240x1400|2560x1600|2880x1800|3200x2000|3520x2200|3840x2400|320x240|320x480|360x200|360x240|360x400|360x480|400x224|480x272|512x224|512x240|512x384|512x512|640x224|640x240|640x448|720x576|800x480|800x600|960x720|1024x768|1280x720|1366x768|1600x900|1920x1080|2048x2048|4096x4096" },
		{ "craft_show_info_text",
		  "Show info text; disabled|enabled" },
		{ "craft_jumping_flash_mode",
		  "Jumping Flash mode; disabled|enabled" },
		{ "craft_field_of_view",
		  "Field of view; 65|70|75|80|85|90|95|100|105|110|115|120|125|130|135|140|145|150" },
		{ "craft_draw_distance",
		  "Draw distance; 10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|27|28|29|30|31|32|9|8|7|6|5|4|3|2|1" },
		{ "craft_inverted_aim",
		  "Inverted aim; disabled|enabled" },
		{ "craft_analog_sensitivity",
		  "Right analog sensitivity; 0.0150|0.0175|0.0200|0.0225|0.0250|0.0275|0.0300|0.0325|0.0350|0.0375|0.0400|0.0425|0.0450|0.0475|0.0500" },
		{ "craft_deadzone_radius",
		  "Analog deadzone size; 0.010|0.015|0.020|0.025|0.030|0.035|0.040|0.045|0.050|0.055|0.060|0.065|0.070|0.075|0.080|0.085|0.090|0.095|0.100|0.110|0.115|0.120|0.125|0.130|0.135|0.140|0.145|0.150|0.155|0.160|0.165|0.170|0.175|0.180|0.185|0.190|0.195|0.200" },
		{ NULL, NULL },
		};
	*/
	static const struct retro_variable vars[] = {
	    { "displaysize", "Display Size; 320x480|320x320|160x160" },
	    { "palmname", "Device Name; MilkedFlea|CuteSqurrel" },
	    { NULL, NULL }
    };
	cb(RETRO_ENVIRONMENT_SET_VARIABLES, (void*)vars);
	cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_content);

	if(cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &logging)) {
		log_cb = logging.log;
	}
	else {
		log_cb = fallback_log;
	}
}

void retro_set_audio_sample(retro_audio_sample_t cb) {
	audio_cb = cb;
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) {
	audio_batch_cb = cb;
}

void retro_set_input_poll(retro_input_poll_t cb) {
	input_poll_cb = cb;
}

void retro_set_input_state(retro_input_state_t cb) {
	input_state_cb = cb;
}

void retro_set_video_refresh(retro_video_refresh_t cb) {
	video_cb = cb;
}

void retro_reset(void) {
}

extern unsigned SHOW_INFO_TEXT;

static void check_variables(bool first_time_startup) {
#if 0
	struct retro_variable var = {0};
	var.key = "craft_resolution";

	if(environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value &&
	        first_time_startup) {
		char* pch;
		char str[100];
		snprintf(str, sizeof(str), "%s", var.value);
		pch = strtok(str, "x");

		if(pch) {
			game_width = strtoul(pch, NULL, 0);
		}

		pch = strtok(NULL, "x");

		if(pch) {
			game_height = strtoul(pch, NULL, 0);
		}

		if(log_cb) {
			log_cb(RETRO_LOG_INFO, "Got size: %u x %u.\n", game_width, game_height);
		}
	}

	var.key = "craft_show_info_text";

	if(environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		if(!strcmp(var.value, "disabled")) {
			SHOW_INFO_TEXT = 0;
		}
		else
			if(!strcmp(var.value, "enabled")) {
				SHOW_INFO_TEXT = 1;
			}
	}

	var.key = "craft_jumping_flash_mode";

	if(environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		if(!strcmp(var.value, "disabled")) {
			JUMPING_FLASH_MODE = 0;
		}
		else
			if(!strcmp(var.value, "enabled")) {
				JUMPING_FLASH_MODE  = 1;
			}
	}

	var.key = "craft_field_of_view";

	if(environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		FIELD_OF_VIEW = atoi(var.value);
	}

	var.key = "craft_draw_distance";

	if(environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		RENDER_CHUNK_RADIUS = atoi(var.value);
	}

	var.key = "craft_inverted_aim";

	if(environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		if(!strcmp(var.value, "disabled")) {
			INVERTED_AIM = 0;
		}
		else
			if(!strcmp(var.value, "enabled")) {
				INVERTED_AIM = 1;
			}
	}

	var.key = "craft_analog_sensitivity";

	if(environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		ANALOG_SENSITIVITY = atof(var.value);
	}

	var.key = "craft_deadzone_radius";

	if(environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		DEADZONE_RADIUS = atof(var.value);
	}

#endif
}

void update_variables() {
	struct retro_variable var;
	var.key = "displaysize";
	var.value = NULL;

	if(environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var)) {
		if(strcmp(var.value, "320x480") == 0) {
			//set resolution
			//libretro_palm_setresolution(320,480);
		}

		if(strcmp(var.value, "320x320") == 0) {
			//set resolution
			//libretro_palm_setresolution(320,320);
		}

		if(strcmp(var.value, "160x160") == 0) {
			//set resolution
			//libretro_palm_setresolution(160,160);
		}
	}
}

void retro_run(void) {
	bool updated = false;

	if(environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE, &updated) && updated) {
		update_variables();
	}

	//HACK remove this and switch to "palmwrapper.h"
	enum {
		BTN_Power,
		BTN_Up,
		BTN_Down,
		BTN_Calender,
		BTN_Contacts,
		BTN_Todo,
		BTN_Notes
	};
	input_poll_cb();//refresh buttons
	libretro_palm_setbutton(BTN_Up, getbutton(RETRO_DEVICE_ID_JOYPAD_UP));
	libretro_palm_setbutton(BTN_Down, getbutton(RETRO_DEVICE_ID_JOYPAD_DOWN));
	libretro_palm_setbutton(BTN_Calender/*used as left in games*/, getbutton(RETRO_DEVICE_ID_JOYPAD_LEFT));
	libretro_palm_setbutton(BTN_Contacts/*used as right in games*/, getbutton(RETRO_DEVICE_ID_JOYPAD_RIGHT));
	libretro_palm_setbutton(BTN_Todo, getbutton(RETRO_DEVICE_ID_JOYPAD_B));
	libretro_palm_setbutton(BTN_Notes, getbutton(RETRO_DEVICE_ID_JOYPAD_A));
	video_cb(libretro_palm_getframebuffer(), game_width, game_height, game_width * 2);
}

static void keyboard_cb(bool down, unsigned keycode,
                        uint32_t character, uint16_t mod) {
	log_cb(RETRO_LOG_INFO, "Down: %s, Code: %d, Char: %u, Mod: %u.\n",
	       down ? "yes" : "no", keycode, character, mod);
}

bool retro_load_game(const struct retro_game_info* info) {
	//HACK remove preset file paths for testing
	enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_RGB565;//framebuffer format of palm tx
	struct retro_keyboard_callback cb = { keyboard_cb };

	if(!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt)) {
		log_cb(RETRO_LOG_INFO, "RGB565 is not supported.\n");
		return false;
	}

	environ_cb(RETRO_ENVIRONMENT_SET_KEYBOARD_CALLBACK, &cb);

	if(environ_cb(RETRO_ENVIRONMENT_GET_RUMBLE_INTERFACE, &rumble)) {
		log_cb(RETRO_LOG_INFO, "Rumble environment supported.\n");
	}
	else {
		log_cb(RETRO_LOG_INFO, "Rumble environment not supported.\n");
	}

	//check_variables(true);
	(void)info;//ignores game info
	return true;
}

void retro_unload_game(void) {
	//HACK this may be important
	//main_unload_game();
}

unsigned retro_get_region(void) {
	return RETRO_REGION_NTSC;
}

bool retro_load_game_special(unsigned type, const struct retro_game_info* info, size_t num) {
	return false;
}

size_t retro_serialize_size(void) {
	return 0;
}

bool retro_serialize(void* data_, size_t size) {
	return false;
}

bool retro_unserialize(const void* data_, size_t size) {
	return false;
}

void* retro_get_memory_data(unsigned id) {
	return NULL;
}

size_t retro_get_memory_size(unsigned id) {
	return 0;
}

void retro_cheat_reset(void) {}

void retro_cheat_set(unsigned index, bool enabled, const char* code) {
	(void)index;
	(void)enabled;
	(void)code;
}

void handle_mouse_input() {}
